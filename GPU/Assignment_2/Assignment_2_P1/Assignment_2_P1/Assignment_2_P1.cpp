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

// source files
#include "common.h"

int main(void)
{
	cl::Platform platform;			// device's platform
	cl::Device device;				// device used
	cl::Context context;			// context for the device
	cl::Program program;			// OpenCL program object
	cl::Kernel kernel;				// a single kernel object
	cl::CommandQueue queue;			// commandqueue for a context and device

	// declare data and memory objects
	cl_int array1[8];
	cl_int array2[16];
	cl_int output[32];

	cl::Buffer arrayBuffer1;
	cl::Buffer arrayBuffer2;
	cl::Buffer outputBuffer;

	srand(time(NULL));

	// creates a random array of 0 to 9
	for (int i = 0; i < 8; i++) {
		array1[i] = (rand() % 10);
	}

	// creates an array of 1 to 8
	int count = 1;
	for (int i = 0; i < 8; i++) {
		array2[i] = count;
		count += 1;
	}

	// creates an array of -8 to -1
	count = -8;
	for (int i = 8; i < 16; i++) {
		array2[i] = count;
		count += 1;
	}

	try {
		// select an OpenCL device
		if (!select_one_device(&platform, &device))
		{
			// if no device selected
			quit_program("Device not selected.");
		}

		// create a context from device
		context = cl::Context(device);

		// build the program
		if (!build_program(&program, &context, "source.cl"))
		{
			// if OpenCL program build error
			quit_program("OpenCL program build error.");
		}

		// create a kernel
		kernel = cl::Kernel(program, "A2_P1");

		// create command queue
		queue = cl::CommandQueue(context, device);

		// create buffers
		arrayBuffer1 = cl::Buffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, sizeof(cl_int) * 8, &array1[0]);
		arrayBuffer2 = cl::Buffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, sizeof(cl_int) * 16, &array2[0]);
		outputBuffer = cl::Buffer(context, CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR, sizeof(cl_int) * 32, &output[0]);

		// set kernel arguments
		kernel.setArg(0, arrayBuffer1);
		kernel.setArg(1, arrayBuffer2);
		kernel.setArg(2, outputBuffer);

		// enqueue kernel for execution
		queue.enqueueTask(kernel);

		std::cout << "Kernel enqueued." << std::endl;
		std::cout << "--------------------" << std::endl;

		// enqueue command to read from device to host memory
		queue.enqueueReadBuffer(outputBuffer, CL_TRUE, 0, sizeof(cl_int) * 32, &output[0]);

		// output result
		int x = 0;
		while (x < 32) {
			if (-1 < x && x < 8) {
				if (x == 0) {
					std::cout << "The random generated numbers are:" << std::endl;
				}
				std::cout << output[x] << "\t";
				x++;
			}

			if (7 < x && x < 16) {
				if (x == 8) {
					std::cout << "\n\nThe first set of eight numbers are:" << std::endl;
				}
				std::cout << output[x] << "\t";
				x++;
			}

			if (15 < x && x < 24) {
				if (x == 16) {
					std::cout << "\n\nThe second set of eight numbers are:" << std::endl;
				}
				std::cout << output[x] << "\t";
				x++;
			}

			if (23 < x && x < 32) {
				if (x == 24) {
					std::cout << "\n\nThe result is:" << std::endl;
				}
				std::cout << output[x] << "\t";
				x++;
			}
		}
		std::cout << "\n" << std::endl;
	}
	// catch any OpenCL function errors
	catch (cl::Error e) {
		// call function to handle errors
		handle_error(e);
	}

#ifdef _WIN32
	// wait for a keypress on Windows OS before exiting
	std::cout << "\npress a key to quit...";
	std::cin.ignore();
#endif

	return 0;
}