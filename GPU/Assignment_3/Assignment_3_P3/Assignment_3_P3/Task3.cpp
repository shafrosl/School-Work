#define CL_USE_DEPRECATED_OPENCL_2_0_APIS    // using OpenCL 1.2, some functions deprecated in OpenCL 2.0
#define __CL_ENABLE_EXCEPTIONS                // enable OpenCL exemptions

// C++ standard library and STL headers
#include <iostream>
#include <vector>
#include <fstream>
#include <locale>

// OpenCL header, depending on OS
#ifdef __APPLE__
#include <OpenCL/cl.hpp>
#else
#include <CL/cl.hpp>
#endif

#include "common.h"
#include "bmpfuncs.h"

int userIn() {
	string input;

	std::cout << "Please enter window choice (3/5/7): ";
	std::cin >> input;
	std::cin.ignore();
	std::cout << "--------------------" << std::endl;

	try {
		int choice = std::stoi(input);
		return choice;
	}
	catch (const std::invalid_argument& e) {
		std::cout << "Input is not a valid number.\n" << std::endl;
	}

	return 0;
}

int main(void)
{
    cl::Platform platform;													// device's platform
    cl::Device device;														// device used
    cl::Context context;													// context for the device
    cl::Program program;													// OpenCL program object
    cl::Kernel kernel, kernelReduction, kernelComplete, kernelLuminance;    // kernel objects
    cl::CommandQueue queue;													// commandqueue for a context and device

    // declare data and memory objects
    unsigned char* inputImage;
    unsigned char* inputImage1;
    unsigned char* inputImage2;
    unsigned char* outputImage;
    int imgWidth, imgHeight, imageSize;

    cl::ImageFormat imgFormat;
    cl::Image2D inputImgBuffer, inputImgBuffer1, inputImgBuffer2, outputImgBuffer, outputImgBuffer2;
    cl::Buffer outputRGBBuffer;
	cl::Buffer outputBuffer, dataBuffer, totalBuffer;
    const char bmpfile[15] = "bunnycity1.bmp";

    try {
		// select an OpenCL device
		if (!select_one_device(&platform, &device))
		{
			// if no device selected
			quit_program("Device not selected.");
		}

		std::cout << "--------------------" << std::endl;

		// create a context from device
		context = cl::Context(device);

		// build the program
		if (!build_program(&program, &context, "reduction_complete.cl"))
		{
			// if OpenCL program build error
			quit_program("OpenCL program build error.");
		}

		// create a kernel
		kernel = cl::Kernel(program, "luminance");

		// create command queue
		queue = cl::CommandQueue(context, device);

		// read input image
		inputImage = read_BMP_RGB_to_RGBA(bmpfile, &imgWidth, &imgHeight);

		// allocate memory for output image
		imageSize = imgWidth * imgHeight * 4;
		outputImage = new unsigned char[imageSize];

		// image format
		imgFormat = cl::ImageFormat(CL_RGBA, CL_UNORM_INT8);

		// create image objects
		inputImgBuffer = cl::Image2D(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, imgFormat, imgWidth, imgHeight, 0, (void*)inputImage);

        //////////////////////////////////////////////////// CALCULATIONS ////////////////////////////////////////////////////

		// declare data and memory objects
		std::vector<cl_float> data(imgHeight * imgWidth);
		cl::LocalSpaceArg localSpace;			// to create local space for the kernel
		size_t workgroupSize;					// work group size
		size_t kernelWorkgroupSize;				// allowed work group size for the kernel
		cl_ulong localMemorySize;				// device's local memory size
		float total = 0.0;
		float * outputLuminance = new float[imgHeight * imgWidth];

		outputBuffer = cl::Buffer(context, CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR, sizeof(float) * (imgHeight * imgWidth), &outputLuminance[0]);

		kernelLuminance = cl::Kernel(program, "luminance");

		// set kernel arguments
		kernelLuminance.setArg(0, inputImgBuffer);
		kernelLuminance.setArg(1, outputBuffer);

		cl::NDRange offset(0, 0);
		cl::NDRange globalSize(imgWidth, imgHeight);
		queue.enqueueNDRangeKernel(kernelLuminance, offset, globalSize);
		queue.enqueueReadBuffer(outputBuffer, CL_TRUE, 0, sizeof(float) * (imgWidth * imgHeight), &outputLuminance[0]);

		// create command queue
		kernelReduction = cl::Kernel(program, "reduction_vector");
		kernelComplete = cl::Kernel(program, "reduction_complete");

		queue = cl::CommandQueue(context, device, CL_QUEUE_PROFILING_ENABLE);


		// get device information and allowed kernel work group size
		workgroupSize = device.getInfo<CL_DEVICE_MAX_WORK_GROUP_SIZE>();
		localMemorySize = device.getInfo<CL_DEVICE_LOCAL_MEM_SIZE>();
		kernelWorkgroupSize = kernelReduction.getWorkGroupInfo<CL_KERNEL_WORK_GROUP_SIZE>(device);

		// if kernel only allows one work-item per work-group, abort
		if (kernelWorkgroupSize == 1)
			quit_program("Abort: Cannot run reduction kernel, because kernel workgroup size is 1.");

		// if allowed kernel work group size smaller than device's max workgroup size
		if (workgroupSize > kernelWorkgroupSize)
			workgroupSize = kernelWorkgroupSize;

		workgroupSize = kernelWorkgroupSize;

		// ensure sufficient local memory is available
		while (localMemorySize < sizeof(float) * workgroupSize * 4)
		{
			workgroupSize /= 4;
		}

		// create buffers
		dataBuffer = cl::Buffer(context, CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR, sizeof(cl_float) * imgHeight * imgWidth, &outputLuminance[0]);
		totalBuffer = cl::Buffer(context, CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR, sizeof(cl_float), &total);

		// set local space size
		localSpace = cl::Local(sizeof(float) * workgroupSize * 4);

		// set kernel arguments
		kernelReduction.setArg(0, dataBuffer);
		kernelReduction.setArg(1, localSpace);

		kernelComplete.setArg(0, dataBuffer);
		kernelComplete.setArg(1, localSpace);
		kernelComplete.setArg(2, totalBuffer);

		// enqueue kernel for execution
		size_t global = imgHeight * imgWidth / 4;


		cl::NDRange globalSize1(global);
		cl::NDRange localSize(workgroupSize);

		queue.enqueueNDRangeKernel(kernelReduction, offset, globalSize1, localSize);

		// run reduction kernel until work-items can fit within one work-group
		while (global / workgroupSize > workgroupSize)
		{
			global /= workgroupSize;
			globalSize1 = global;
			queue.enqueueNDRangeKernel(kernelReduction, offset, globalSize1, localSize);
		}

		// run reduction kernel one last time
		global /= workgroupSize;
		globalSize1 = global;
		queue.enqueueNDRangeKernel(kernelComplete, offset, globalSize1);

		// read and check results
		queue.enqueueReadBuffer(totalBuffer, CL_TRUE, 0, sizeof(cl_float), &total);

		float avg = total / (imgHeight*imgWidth);

		std::cout << "Calculating average done." << std::endl;
		std::cout << "--------------------" << std::endl;

		char ans;
		std::string in;

		std::cout << "Would you like to use " << avg << " as threshold values? (Y/N): ";
		std::cin >> ans;
		cin.ignore();

		if (ans == 'Y' || ans == 'y') {
			std::cout << "Your current threshold value is: " << avg << std::endl;
		}

		else if (ans == 'N' || ans == 'n') {
			std::cout << "Please enter a value between 0 - 255: ";
			std::cin >> in;

			try {
				avg = std::stoi(in);
			}
			catch (const std::invalid_argument& e) {
				quit_program("Input is not a valid number.");
			}

			if (avg < 0 || 255 < avg) {
				quit_program("Input is not a valid number.");
			}

			std::cout << "Your current threshold value is: " << avg << std::endl;
		}

		else {
			quit_program("Invalid input.");
		}

		std::cout << "--------------------" << std::endl;

		//////////////////////////////////////////////////// BLACKENING ////////////////////////////////////////////////////

        // build the program
        if(!build_program(&program, &context, "simple_conv.cl"))
        {
            // if OpenCL program build error
            quit_program("OpenCL program build error.");
        }

        // create a kernel
        kernel = cl::Kernel(program, "black");

        // create command queue
        queue = cl::CommandQueue(context, device);

        // read input image
        inputImage = read_BMP_RGB_to_RGBA(bmpfile, &imgWidth, &imgHeight);

        // allocate memory for output image
        imageSize = imgWidth * imgHeight * 4;
        outputImage = new unsigned char[imageSize];

        // image format
        imgFormat = cl::ImageFormat(CL_RGBA, CL_UNORM_INT8);

        // create image objects
        inputImgBuffer = cl::Image2D(context, CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR, imgFormat, imgWidth, imgHeight, 0, (void*)inputImage);
        outputImgBuffer = cl::Image2D(context, CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR, imgFormat, imgWidth, imgHeight, 0, (void*)outputImage);

        // set kernel arguments
        kernel.setArg(0, inputImgBuffer);
        kernel.setArg(1, outputImgBuffer);
        kernel.setArg(2, avg);

        // enqueue kernel
        queue.enqueueNDRangeKernel(kernel, offset, globalSize);

        std::cout << "Kernel enqueued." << std::endl;
        std::cout << "--------------------" << std::endl;

        // enqueue command to read image from device to host memory
        cl::size_t<3> origin, region;
        origin[0] = origin[1] = origin[2] = 0;
        region[0] = imgWidth;
        region[1] = imgHeight;
        region[2] = 1;

        queue.enqueueReadImage(outputImgBuffer, CL_TRUE, origin, region, 0, 0, outputImage);

        // output results to image file
        write_BMP_RGBA_to_RGB("darkened.bmp", outputImage, imgWidth, imgHeight);

        std::cout << "Removing luminance below threshold done." << std::endl;
		std::cout << "--------------------" << std::endl;

        // deallocate memory
        free(inputImage);
        free(outputImage);

        //////////////////////////////////////////////////// DOUBLE PASS ////////////////////////////////////////////////////

		int choice = userIn();

		if (choice != 3 && choice != 5 && choice != 7) {
			quit_program("Invalid input.");
		}

		// build the program
		if (!build_program(&program, &context, "simple_conv.cl")) {
			// if OpenCL program build error
			quit_program("OpenCL program build error.");
		}

		// create a kernel
		kernel = cl::Kernel(program, "passing");

		// create command queue
		queue = cl::CommandQueue(context, device);

		// read input image
		inputImage = read_BMP_RGB_to_RGBA("darkened.bmp", &imgWidth, &imgHeight);

		// allocate memory for output image
		imageSize = imgWidth * imgHeight * 4;
		outputImage = new unsigned char[imageSize];

		// image format
		imgFormat = cl::ImageFormat(CL_RGBA, CL_UNORM_INT8);

		// create image objects
		inputImgBuffer = cl::Image2D(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, imgFormat, imgWidth, imgHeight, 0, (void*)inputImage);
		outputImgBuffer = cl::Image2D(context, CL_MEM_WRITE_ONLY | CL_MEM_COPY_HOST_PTR, imgFormat, imgWidth, imgHeight, 0, (void*)outputImage);

		// set kernel arguments
		kernel.setArg(0, inputImgBuffer);
		kernel.setArg(1, outputImgBuffer);
		kernel.setArg(2, choice);
		kernel.setArg(3, 1);

		queue.enqueueNDRangeKernel(kernel, offset, globalSize);

		std::cout << "Kernel enqueued." << std::endl;
		std::cout << "--------------------" << std::endl;

		// enqueue command to read image from device to host memory
		origin[0] = origin[1] = origin[2] = 0;
		region[0] = imgWidth;
		region[1] = imgHeight;
		region[2] = 1;

		queue.enqueueReadImage(outputImgBuffer, CL_TRUE, origin, region, 0, 0, outputImage);

		// output results to image file
		write_BMP_RGBA_to_RGB("pass1.bmp", outputImage, imgWidth, imgHeight);

		std::cout << "First pass done." << std::endl;
		std::cout << "--------------------" << std::endl;

		// deallocate memory
		free(inputImage);
		free(outputImage);

		// read input image
		inputImage = read_BMP_RGB_to_RGBA("pass1.bmp", &imgWidth, &imgHeight);

		// allocate memory for output image
		imageSize = imgWidth * imgHeight * 4;
		outputImage = new unsigned char[imageSize];

		// image format
		imgFormat = cl::ImageFormat(CL_RGBA, CL_UNORM_INT8);

		// create image objects
		inputImgBuffer = cl::Image2D(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, imgFormat, imgWidth, imgHeight, 0, (void*)inputImage);
		outputImgBuffer = cl::Image2D(context, CL_MEM_WRITE_ONLY | CL_MEM_COPY_HOST_PTR, imgFormat, imgWidth, imgHeight, 0, (void*)outputImage);

		// set kernel arguments
		kernel.setArg(0, inputImgBuffer);
		kernel.setArg(1, outputImgBuffer);
		kernel.setArg(2, choice);
		kernel.setArg(3, 1);

		queue.enqueueNDRangeKernel(kernel, offset, globalSize);

		std::cout << "Kernel enqueued." << std::endl;
		std::cout << "--------------------" << std::endl;

		// enqueue command to read image from device to host memory
		//cl::size_t<3> origin, region;
		origin[0] = origin[1] = origin[2] = 0;
		region[0] = imgWidth;
		region[1] = imgHeight;
		region[2] = 1;

		queue.enqueueReadImage(outputImgBuffer, CL_TRUE, origin, region, 0, 0, outputImage);

		// output results to image file
		write_BMP_RGBA_to_RGB("pass2.bmp", outputImage, imgWidth, imgHeight);

		std::cout << "Second pass done." << std::endl;
		std::cout << "--------------------" << std::endl;

		// deallocate memory
		free(inputImage);
		free(outputImage);

        //////////////////////////////////////////////////// MERGE ////////////////////////////////////////////////////
        // create a kernel
        kernel = cl::Kernel(program, "merge");

        // create command queue
        queue = cl::CommandQueue(context, device);

        // read input image
        inputImage1 = read_BMP_RGB_to_RGBA(bmpfile, &imgWidth, &imgHeight);
        inputImage2 = read_BMP_RGB_to_RGBA("pass2.bmp", &imgWidth, &imgHeight);

        // allocate memory for output image
        imageSize = imgWidth * imgHeight * 4;
        outputImage = new unsigned char[imageSize];

        // image format
        imgFormat = cl::ImageFormat(CL_RGBA, CL_UNORM_INT8);

        // create image objects
        inputImgBuffer1 = cl::Image2D(context, CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR, imgFormat, imgWidth, imgHeight, 0, (void*)inputImage1);
        inputImgBuffer2 = cl::Image2D(context, CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR, imgFormat, imgWidth, imgHeight, 0, (void*)inputImage2);
        outputImgBuffer = cl::Image2D(context, CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR, imgFormat, imgWidth, imgHeight, 0, (void*)outputImage);

        // set kernel arguments
        kernel.setArg(0, inputImgBuffer1);
		kernel.setArg(1, inputImgBuffer2);
        kernel.setArg(2, outputImgBuffer);

        queue.enqueueNDRangeKernel(kernel, offset, globalSize);

        std::cout << "Kernel enqueued." << std::endl;
        std::cout << "--------------------" << std::endl;

        // enqueue command to read image from device to host memory
        //cl::size_t<3> origin, region;
        origin[0] = origin[1] = origin[2] = 0;
        region[0] = imgWidth;
        region[1] = imgHeight;
        region[2] = 1;

        queue.enqueueReadImage(outputImgBuffer, CL_TRUE, origin, region, 0, 0, outputImage);

        // output results to image file
        write_BMP_RGBA_to_RGB("output.bmp", outputImage, imgWidth, imgHeight);

        std::cout << "We done." << std::endl;
        std::cout << "--------------------" << std::endl;

        // deallocate memory
        free(inputImage1);
        free(inputImage2);
        free(outputImage);
    }

    // catch any OpenCL function errors
    catch (cl::Error e) {
        // call function to handle errors
        handle_error(e);
    }

#ifdef _WIN32
    // wait for a keypress on Windows OS before exiting
    std::cout << "\nPress enter to quit...";
    std::cin.ignore();
#endif

    return 0;
}
