#define CL_USE_DEPRECATED_OPENCL_2_0_APIS	// using OpenCL 1.2, some functions deprecated in OpenCL 2.0
#define __CL_ENABLE_EXCEPTIONS				// enable OpenCL exemptions

// C++ standard library and STL headers
#include <iostream>
#include <vector>
#include <fstream>

// OpenCL header, depending on OS
#ifdef __APPLE__
#include <OpenCL/cl.hpp>
#else
#include <CL/cl.hpp>
#endif

#include "common.h"
#include "bmpfuncs.h"

int main(void)
{
	cl::Platform platform;															// device's platform
	cl::Device device;																// device used
	cl::Context context;															// context for the device
	cl::Program program;															// OpenCL program object
	cl::Kernel kernel, kernelLuminance, kernelReduction, kernelComplete;			// a single kernel object
	cl::CommandQueue queue;															// commandqueue for a context and device
	cl::LocalSpaceArg localSpace;													// to create local space for the kernel
	cl::Buffer outputBuffer, dataBuffer, totalBuffer;

	// declare data and memory objects
	unsigned char* inputImage;
	unsigned char* outputImage;
	int imgWidth, imgHeight, imageSize;
	const char bmpfile[15] = "bunnycity2.bmp";

	cl::ImageFormat imgFormat;
	cl::Image2D inputImgBuffer, outputImgBuffer;

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
		if(!build_program(&program, &context, "simple_conv.cl"))
		{
			// if OpenCL program build error
			quit_program("OpenCL program build error.");
		}

		////////////////////////////////////// PART A //////////////////////////////////////

		// create a kernel
		kernel = cl::Kernel(program, "Grayscale");

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
		outputImgBuffer = cl::Image2D(context, CL_MEM_WRITE_ONLY | CL_MEM_COPY_HOST_PTR, imgFormat, imgWidth, imgHeight, 0, (void*)outputImage);

		// set kernel arguments
		kernel.setArg(0, inputImgBuffer);
		kernel.setArg(1, outputImgBuffer);

		// enqueue kernel
		cl::NDRange offset(0, 0);
		cl::NDRange globalSize(imgWidth, imgHeight);

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
		write_BMP_RGBA_to_RGB("output.bmp", outputImage, imgWidth, imgHeight);

		std::cout << "Greyscale image printed. \nAverage calculations done." << std::endl;
		std::cout << "--------------------" << std::endl;

		// deallocate memory
		free(outputImage);

		////////////////////////////////////// PART B //////////////////////////////////////

		float total = 0.0;
		float *lumOutput = new float[imgHeight * imgWidth];

		// read each RGB pixel colour
		for (int i = 0; i < imgWidth * imgHeight * 4; i += 4) {
			float luminance = 0.299f * inputImage[i] + 0.587f * inputImage[i + 1] + 0.114f * inputImage[i + 2];
			inputImage[i] = static_cast<int>(luminance);		// R
			inputImage[i + 1] = static_cast<int>(luminance);	// G
			inputImage[i + 2] = static_cast<int>(luminance);	// B
			inputImage[i + 3] = 255;							// A
			total += luminance;
		}

		float avg = total / (imgHeight*imgWidth);

		std::cout << "Total: " << total << std::endl;
		std::cout << "Average: " << avg << std::endl;
		std::cout << "--------------------" << std::endl;

		// deallocate memory
		free(inputImage);

		////////////////////////////////////// PART C //////////////////////////////////////
		// declare data and memory objects
		std::vector<cl_float> data(imgHeight * imgWidth);
		cl::LocalSpaceArg localSpace;			// to create local space for the kernel
		size_t workgroupSize;					// work group size
		size_t kernelWorkgroupSize;				// allowed work group size for the kernel
		cl_ulong localMemorySize;				// device's local memory size
		total = 0.0;

		// build the program
		if (!build_program(&program, &context, "reduction_complete.cl")) {
			// if OpenCL program build error
			quit_program("OpenCL program build error.");
		}

		float * outputLuminance = new float[imgHeight * imgWidth];

		outputBuffer = cl::Buffer(context, CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR, sizeof(float) * (imgHeight * imgWidth), &outputLuminance[0]);

		kernelLuminance = cl::Kernel(program, "luminance");

		// set kernel arguments
		kernelLuminance.setArg(0, inputImgBuffer);
		kernelLuminance.setArg(1, outputBuffer);

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

		std::cout << "Calculations using reduction done." << std::endl;
		std::cout << "--------------------" << std::endl;

		cout << "Average: " << total/(imgHeight*imgWidth) << endl;
		std::cout << "--------------------" << std::endl;

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
