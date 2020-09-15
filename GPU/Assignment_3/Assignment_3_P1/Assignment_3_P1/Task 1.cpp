#define CL_USE_DEPRECATED_OPENCL_2_0_APIS	// using OpenCL 1.2, some functions deprecated in OpenCL 2.0
#define __CL_ENABLE_EXCEPTIONS				// enable OpenCL exemptions

// C++ standard library and STL headers
#include <iostream>
#include <vector>
#include <fstream>
#include <stdlib.h>
#include <ctime>

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

    std::cout << "Please enter choice (3/5/7): ";
    std::cin >> input;
    std::cin.ignore();

    try {
        int choice = std::stoi(input);
        return choice;
    }
    catch (const std::invalid_argument& e){
		quit_program("Input is not a valid number.");
    }
    return 0;
}

int main(void)
{
	cl::Platform platform;					// device's platform
	cl::Device device;						// device used
	cl::Context context;					// context for the device
	cl::Program program;					// OpenCL program object
	cl::Kernel kernel;						// a single kernel object
	cl::CommandQueue queue;					// commandqueue for a context and device
	cl_ulong timeStart, timeEnd, timeTotal;
	cl::Event startEvent, endEvent;			// for profiling

	// declare data and memory objects
	unsigned char* inputImage;
	unsigned char* outputImage;
	unsigned char*	outputImage2;
	int imgWidth, imgHeight, imageSize;
	int choice;
	const char bmpfile[15] = "bunnycity2.bmp";

	cl::ImageFormat imgFormat;
	cl::Image2D inputImgBuffer, outputImgBuffer, outputImgBuffer2;

	try {
		// select an OpenCL device
		if (!select_one_device(&platform, &device)) {
			// if no device selected
			quit_program("Device not selected.");
		}

		// create a context from device
		context = cl::Context(device);

		//////////////////////////////////////// PART A /////////////////////////////////////////////

		// build the program
		if (!build_program(&program, &context, "simple_conv.cl")) {
			// if OpenCL program build error
			quit_program("OpenCL program build error.");
		}

		int choice = userIn();

		if (choice != 3 && choice != 5 && choice != 7) {
			quit_program("Invalid choice.");
		}

		std::cout << "--------------------" << std::endl;

		// create a kernel
		kernel = cl::Kernel(program, "part_a");

		// create command queue
		queue = cl::CommandQueue(context, device, CL_QUEUE_PROFILING_ENABLE);

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
		kernel.setArg(2, choice);

		// enqueue kernel
		cl::NDRange offset(0, 0);
		cl::NDRange globalSize(imgWidth, imgHeight);

		queue.enqueueNDRangeKernel(kernel, offset, globalSize, cl::NullRange, NULL, &startEvent);

		for (int i = 0; i < 999; i++) {
			queue.enqueueNDRangeKernel(kernel, offset, globalSize);
		}
		queue.finish();

		std::cout << "Kernel enqueued." << std::endl;
		std::cout << "--------------------" << std::endl;

		// enqueue command to read image from device to host memory
		cl::size_t<3> origin, region;
		origin[0] = origin[1] = origin[2] = 0;
		region[0] = imgWidth;
		region[1] = imgHeight;
		region[2] = 1;

		queue.enqueueReadImage(outputImgBuffer, CL_TRUE, origin, region, 0, 0, outputImage, NULL, &endEvent);

		// output results to image file
		write_BMP_RGBA_to_RGB("outputA.bmp", outputImage, imgWidth, imgHeight);

		// check timing
		timeStart = startEvent.getProfilingInfo<CL_PROFILING_COMMAND_START>();
		timeEnd = endEvent.getProfilingInfo<CL_PROFILING_COMMAND_END>();

		timeTotal = timeEnd - timeStart;

		std::cout << "Done." << std::endl;
		std::cout << "--------------------" << std::endl;

		cout << "Total Time: " << (int)(timeTotal / 1000) << endl;
		std::cout << "--------------------" << std::endl;

		// deallocate memory
		free(inputImage);
		free(outputImage);

		//////////////////////////////////////// PART B /////////////////////////////////////////////

		// build the program
		if (!build_program(&program, &context, "simple_conv.cl"))
		{
			// if OpenCL program build error
			quit_program("OpenCL program build error.");
		}

		// create a kernel
		kernel = cl::Kernel(program, "part_b");

		// create command queue
		queue = cl::CommandQueue(context, device, CL_QUEUE_PROFILING_ENABLE);

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

		int pass = 1;

		// set kernel arguments
		kernel.setArg(0, inputImgBuffer);
		kernel.setArg(1, outputImgBuffer);
		kernel.setArg(2, choice);
		kernel.setArg(3, pass);

		queue.enqueueNDRangeKernel(kernel, offset, globalSize, cl::NullRange, NULL, &startEvent);

		for (int i = 0; i < 999; i++) {
			queue.enqueueNDRangeKernel(kernel, offset, globalSize);
		}

		queue.enqueueNDRangeKernel(kernel, cl::NullRange, globalSize, cl::NullRange);

		std::cout << "Kernel enqueued." << std::endl;
		std::cout << "--------------------" << std::endl;

		// enqueue command to read image from device to host memory
		origin[0] = origin[1] = origin[2] = 0;
		region[0] = imgWidth;
		region[1] = imgHeight;
		region[2] = 1;

		std::cout << "First pass done." << std::endl;
		std::cout << "--------------------" << std::endl;

		queue.enqueueReadImage(outputImgBuffer, CL_TRUE, origin, region, 0, 0, outputImage);

		// deallocate memory
		free(inputImage);

		// allocate memory for output image
		imageSize = imgWidth * imgHeight * 4;
		outputImage2 = new unsigned char[imageSize];

		// image format
		imgFormat = cl::ImageFormat(CL_RGBA, CL_UNORM_INT8);

		// create image objects
		inputImgBuffer = cl::Image2D(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, imgFormat, imgWidth, imgHeight, 0, (void*)outputImage);
		outputImgBuffer2 = cl::Image2D(context, CL_MEM_WRITE_ONLY | CL_MEM_COPY_HOST_PTR, imgFormat, imgWidth, imgHeight, 0, (void*)outputImage2);

		pass = 2;
		// set kernel arguments
		kernel.setArg(0, inputImgBuffer);
		kernel.setArg(1, outputImgBuffer2);
		kernel.setArg(2, choice);
		kernel.setArg(3, pass);

		for (int i = 0; i < 1000; i++) {
			queue.enqueueNDRangeKernel(kernel, offset, globalSize);
		}

		std::cout << "Kernel enqueued." << std::endl;
		std::cout << "--------------------" << std::endl;

		// enqueue command to read image from device to host memory
		//cl::size_t<3> origin, region;
		origin[0] = origin[1] = origin[2] = 0;
		region[0] = imgWidth;
		region[1] = imgHeight;
		region[2] = 1;

		queue.enqueueReadImage(outputImgBuffer2, CL_TRUE, origin, region, 0, 0, outputImage2, NULL, &endEvent);
		//queue.finish();

		// check timing
		timeStart = startEvent.getProfilingInfo<CL_PROFILING_COMMAND_START>();
		timeEnd = endEvent.getProfilingInfo<CL_PROFILING_COMMAND_END>();

		timeTotal = timeEnd - timeStart;

		// output results to image file
		write_BMP_RGBA_to_RGB("outputB.bmp", outputImage2, imgWidth, imgHeight);

		std::cout << "Second pass done." << std::endl;
		std::cout << "--------------------" << std::endl;

		cout << "Total Time: " << (int)(timeTotal / 1000) << endl;
		std::cout << "--------------------" << std::endl;

		// deallocate memory
		free(outputImage);
		free(outputImage2);
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
