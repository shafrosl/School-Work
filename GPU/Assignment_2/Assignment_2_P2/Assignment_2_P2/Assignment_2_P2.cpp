#define CL_USE_DEPRECATED_OPENCL_2_0_APIS	// using OpenCL 1.2, some functions deprecated in OpenCL 2.0
#define __CL_ENABLE_EXCEPTIONS				// enable OpenCL exemptions

// C++ standard library and STL headers
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <algorithm>

// OpenCL header, depending on OS
#ifdef __APPLE__
#include <OpenCL/cl.hpp>
#else
#include <CL/cl.hpp>
#endif

#include "common.h"
using namespace std;
std::string wallOfText(std::string filename) {
	std::ifstream infile;
	std::string wallOfText = "";

	// opens file to read and check if it is the correct file
	infile.open(filename);
	if (!infile) {
		std::cout << "File Not Found" << std::endl;
	}
	std::string str = "";
	while (getline(infile, str))
	{
		for (int i = 0; i < str.length(); i++)
		{
			// only reads in alphabets
			if ((str[i] >= 65 && str[i] <= 90) || (str[i] >= 97 && str[i] <= 122))
			{
				// stores the text into itself
				wallOfText = wallOfText + str[i];
			}
		}
	}

	// capitalises all the letters
	std::transform(wallOfText.begin(), wallOfText.end(), wallOfText.begin(), ::toupper);

	return wallOfText;
}

//get encryption number
int userNum() {
	std::string a;

	std::cout << "Please enter encyption number: ";
	std::cin >> a;
	std::cin.ignore();

	try {
		// converts string into int
		int input = std::stoi(a);
		return input;
	}
	catch (const std::invalid_argument& e) {
		quit_program("Input is not a valid number.\n");
	}

	return 0;
}

int main(void)
{
	cl::Platform platform;            // device's platform
	cl::Device device;                // device used
	cl::Context context;              // context for the device
	cl::Program program;              // OpenCL program object
	cl::Kernel encKernel;             // encryption kernel
	cl::Kernel decKernel;             // decryption kernel
	cl::CommandQueue queue;           // commandqueue for a context and device

	// initialise data
	std::string text = wallOfText("plaintext");
	int numb = (userNum() % 26);
	int textSize = text.length();

	// declare data and memory objects
	cl_int size = textSize;
	int encNum = numb;
	cl_char* textArray = new cl_char[textSize];
	cl_char* encOutput = new cl_char[textSize];
	cl_char* decOutput = new cl_char[textSize];
	cl_char* textArray1 = new cl_char[textSize];

	// sets starting point and end of NDRange
	cl::NDRange offset(0);
	cl::NDRange globalSize(textSize);

	cl::Buffer textBuffer;
	cl::Buffer encBuffer;
	cl::Buffer decBuffer;
	cl::Buffer enctextBuffer;
	std::cout << std::endl;

	try {
		///////////////////////////////////////////////////////////////////////////////////////////
		std::cout << "===============================================================" << std::endl;
		std::cout << "PART A" << std::endl;
		std::cout << "===============================================================\n" << std::endl;

		// initialise data
		std::string text = wallOfText("plaintext");

		// encrypts the plaintext file
		for (int i = 0; i < text.length(); i++) {
			text[i] += numb;
			if (text[i] > 90) {
				text[i] -= 26;
			}

			else if (text[i] < 65) {
				text[i] += 26;
			}
		}

		for (int i = 5; i < text.length(); i += 6) {
			text.insert(i, " ");
		}

		std::cout << text << std::endl;

		/////////////////////////////////////////////////////////////////////////////////////////////

		std::cout << "\n===============================================================" << std::endl;
		std::cout << "PART B" << std::endl;
		std::cout << "===============================================================\n" << std::endl;

		std::string textB = wallOfText("plaintext");
		cout << endl;

		for (int i = 0; i < textB.length(); i++) {

			textArray1[i] = textB[i];
		}

		// select an OpenCL device
		if (!select_one_device(&platform, &device))
		{
			// if no device selected
			quit_program("Device not selected.");
		}

		// create a context from device
		context = cl::Context(device);

		// build the program
		if (!build_program(&program, &context, "source_B.cl"))
		{
			// if OpenCL program build error
			quit_program("OpenCL program build error.");
		}

		// create a kernel
		encKernel = cl::Kernel(program, "encrypt");
		decKernel = cl::Kernel(program, "decrypt");

		// create command queue
		queue = cl::CommandQueue(context, device);

		// create buffers
		textBuffer = cl::Buffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, sizeof(cl_char) * textSize, &textArray1[0]);
		encBuffer = cl::Buffer(context, CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR, sizeof(cl_char) * textSize, &encOutput[0]);
		decBuffer = cl::Buffer(context, CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR, sizeof(cl_char) * textSize, &decOutput[0]);

		// set kernel arguments
		encKernel.setArg(0, textBuffer);
		encKernel.setArg(1, encNum);
		encKernel.setArg(2, encBuffer);

		decKernel.setArg(0, encBuffer);
		decKernel.setArg(1, encNum);
		decKernel.setArg(2, decBuffer);

		// enqueue kernel for execution
		queue.enqueueNDRangeKernel(encKernel, offset, globalSize);
		queue.enqueueNDRangeKernel(decKernel, offset, globalSize);

		std::cout << "Kernel enqueued." << std::endl;
		std::cout << "--------------------" << std::endl;

		// enqueue command to read from device to host memory
		queue.enqueueReadBuffer(encBuffer, CL_TRUE, 0, sizeof(cl_char) * textSize, &encOutput[0]);
		queue.enqueueReadBuffer(decBuffer, CL_TRUE, 0, sizeof(cl_char) * textSize, &decOutput[0]);

		// output result
		std::cout << "Encryption Output:" << std::endl;
		for (int x = 0; x < textSize; x++) {
			std::cout << encOutput[x];
			if ((x + 1) % 5 == 0) {
				std::cout << " ";
			}
		}
		std::cout << "\n" << std::endl;

		std::cout << "Decryption Output:" << std::endl;
		for (int x = 0; x < textSize; x++) {
			std::cout << decOutput[x];
			if ((x + 1) % 5 == 0) {
				std::cout << " ";
			}
		}
		std::cout << std::endl;

		/////////////////////////////////////////////////////////////////////////////////////////////

		std::cout << "\n===============================================================" << std::endl;
		std::cout << "PART C" << std::endl;
		std::cout << "===============================================================\n" << std::endl;

		// create a context from device
		context = cl::Context(device);

		// build the program
		if (!build_program(&program, &context, "source_C.cl"))
		{
			// if OpenCL program build error
			quit_program("OpenCL program build error.");
		}

		// create a kernel
		encKernel = cl::Kernel(program, "encrypt");
		decKernel = cl::Kernel(program, "decrypt");

		// create command queue
		queue = cl::CommandQueue(context, device);

		// create buffers
		textBuffer = cl::Buffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, sizeof(cl_char) * textSize, &textArray[0]);
		encBuffer = cl::Buffer(context, CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR, sizeof(cl_char) * textSize, &encOutput[0]);
		decBuffer = cl::Buffer(context, CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR, sizeof(cl_char) * textSize, &decOutput[0]);

		// set kernel arguments
		encKernel.setArg(0, textBuffer);
		encKernel.setArg(1, encBuffer);

		decKernel.setArg(0, enctextBuffer);
		decKernel.setArg(1, decBuffer);

		// enqueue kernel
		queue.enqueueNDRangeKernel(encKernel, offset, globalSize);
		queue.enqueueNDRangeKernel(decKernel, offset, globalSize);

		std::cout << "Kernel enqueued." << std::endl;
		std::cout << "--------------------" << std::endl;

		// enqueue command to read from device to host memory
		queue.enqueueReadBuffer(encBuffer, CL_TRUE, 0, sizeof(cl_char) * textSize, &encOutput[0]);
		queue.enqueueReadBuffer(decBuffer, CL_TRUE, 0, sizeof(cl_char) * textSize, &decOutput[0]);

		// output result
		std::cout << "Encrypted Text:" << std::endl;
		for (int x = 0; x < textSize; x++) {
			std::cout << encOutput[x];
			if ((x + 1) % 5 == 0) {
				std::cout << " ";
			}
		}
		std::cout << "\n" << std::endl;

		std::cout << "Decrypted Text:" << std::endl;
		for (int x = 0; x < textSize; x++) {
			std::cout << decOutput[x];
			if ((x + 1) % 5 == 0) {
				std::cout << " ";
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
