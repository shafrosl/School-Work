#define CL_USE_DEPRECATED_OPENCL_2_0_APIS	// using OpenCL 1.2, some functions deprecated in OpenCL 2.0
#define __CL_ENABLE_EXCEPTIONS				// enable OpenCL exemptions

// C++ standard library and STL headers
#include <iostream>
#include <fstream>

// OpenCL header, depending on OS
#ifdef __APPLE__
#include <OpenCL/cl.hpp>
#else
#include <CL/cl.hpp>
#endif

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
    cl_int global_id[1];
    cl_int work_id[1];
    cl_int local_id[1];
    
	cl::Buffer global_id_buffer;
    cl::Buffer work_id_buffer;
    cl::Buffer local_id_buffer;

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
        if(!build_program(&program, &context, "source.cl"))
        {
            // if OpenCL program build error
            quit_program("OpenCL program build error.");
        }
        
        // create a kernel
        kernel = cl::Kernel(program, "passCrack");
        
        // create command queue
        queue = cl::CommandQueue(context, device);
        
        // create buffers
		global_id_buffer = cl::Buffer(context, CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR, sizeof(cl_int), &global_id[0]);
		work_id_buffer = cl::Buffer(context, CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR, sizeof(cl_int), &work_id[0]);
		local_id_buffer = cl::Buffer(context, CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR, sizeof(cl_int), &local_id[0]);
        
        // set kernel arguments
        kernel.setArg(0, global_id_buffer);
        kernel.setArg(1, work_id_buffer);
        kernel.setArg(2, local_id_buffer);
        
        // enqueue kernel for execution
        cl::NDRange offset(0);
        cl::NDRange global_size(99999999);
        queue.enqueueNDRangeKernel(kernel, offset, global_size);
        
        //queue.enqueueTask(kernel);
        
        std::cout << "Kernel enqueued." << std::endl;
        std::cout << "--------------------" << std::endl;
        
        // enqueue command to read from device to host memory
        queue.enqueueReadBuffer(global_id_buffer, CL_TRUE, 0, sizeof(cl_int), &global_id[0]);
        queue.enqueueReadBuffer(work_id_buffer, CL_TRUE, 0, sizeof(cl_int), &work_id[0]);
        queue.enqueueReadBuffer(local_id_buffer, CL_TRUE, 0, sizeof(cl_int), &local_id[0]);
        
        std::cout << "Global ID: " << global_id[0] << "\n" << "Work Group ID: " << work_id[0] << "\n" << "Local ID: " << local_id[0] << std::endl;
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
