#define CL_USE_DEPRECATED_OPENCL_2_0_APIS    // using OpenCL 1.2, some functions deprecated in OpenCL 2.0
#define __CL_ENABLE_EXCEPTIONS                // enable OpenCL exemptions

// C++ standard library and STL headers
#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>

// OpenCL header, depending on OS
#ifdef __APPLE__
#include <OpenCL/cl.hpp>
#else
#include <CL/cl.hpp>
#endif

// functions to handle errors
#include "error.h"

// gets user input on which device to be accessed
int select_cpu_gpu()
{
    unsigned int devType;   // dev type
    std::string input;      // user input
    
    std::cout << "Please select from the following: " << std::endl;
    std::cout << "   0: CPU" << std::endl;
    std::cout << "   1: GPU" << std::endl;
    std::cout << "Enter choice: ";
    std::cin >> input;
    std::cin.ignore();
    
    std::istringstream stringStream(input);
    
    // check whether valid option was selected
    // check if input was an integer
    if (stringStream >> devType)
    {
        char c;
        
        // check if there was anything after the integer
        if (!(stringStream >> c))
        {
            // check if valid option range
            if (devType >= 0 && devType < 2)
            {
                // return device type
                return devType;
            }
        }
    }
    return 2;
}

// uses the input to return the device type selected
cl_device_type devType(int select_cpu_gpu)
{
	if (select_cpu_gpu == 0)
	{
		return CL_DEVICE_TYPE_CPU;
	}
	else if (select_cpu_gpu == 1)
	{
		return CL_DEVICE_TYPE_GPU;
	}
	else 
	{
		quit_program("\nDevice not selected.");
	}
}

// function that allows the user to select a CPU device
// it displays the available CPU platform and device options
// returns whether selection was successful, the selected CPU device and its platform
bool select_one_device(cl::Platform* platfm, cl::Device* dev, cl_device_type devType)
{
    std::vector<cl::Platform> platforms;						// available platforms
    std::vector< std::vector<cl::Device> > platformDevices;		// devices available for each platform
    std::string outputString;									// string for output
    unsigned int i, j;											// counters

    try {
        // get the number of available OpenCL platforms
        cl::Platform::get(&platforms);
        std::cout << "\n--------------------\n" << std::endl;
        std::cout << "Number of OpenCL platforms: " << platforms.size() << std::endl;
        
        // find and store the devices available to each platform
        for (i = 0; i < platforms.size(); i++)
        {
			// available devices
			std::vector<cl::Device> devices;
            
            try
            {
                // get devices available to the platform
                platforms[i].getDevices(devType, &devices);
            }
            
            catch (cl::Error e)
            {

            }
                
            // store available devices for the platform
            platformDevices.push_back(devices);
        }
        
        // display available platforms and devices
        std::cout << "\n--------------------\n" << std::endl;
        std::cout << "Available options:" << std::endl;
        
        // store options as platform and device indices
        std::vector< std::pair<int, int> > options;
        std::vector<size_t> work_item;
        std::size_t size;	
        unsigned int units;
        unsigned int optionCounter = 0;    // option counter
        
        // for CPU platforms
        for (i = 0; i < platforms.size(); i++)
        {
            // for CPU devices per platform
            for (j = 0; j < platformDevices[i].size(); j++)
            {
                // display options
                std::cout << "Option " << optionCounter << ":" << std::endl;
                
                // platform vendor name
                outputString = platforms[i].getInfo<CL_PLATFORM_VENDOR>();
                std::cout << "   Platform - " << outputString << std::endl;
                
                // device type
				if (platformDevices[i][j].getInfo<CL_DEVICE_TYPE>() == CL_DEVICE_TYPE_CPU)
				{
					outputString = "CPU";
				}
				else
				{
					outputString = "GPU";
				}
                std::cout << "   Device Type - " << outputString << std::endl;
                
                // device name
                outputString = platformDevices[i][j].getInfo<CL_DEVICE_NAME>();
                std::cout << "   Device Name - " << outputString << std::endl;
                
                // device max compute units
                units = platformDevices[i][j].getInfo<CL_DEVICE_MAX_COMPUTE_UNITS>();
                std::cout << "   Device Max Compute Units - " << units << std::endl;
                
                // device max work grp size
                size = platformDevices[i][j].getInfo<CL_DEVICE_MAX_WORK_GROUP_SIZE>();
                std::cout << "   Device Max Work Grp Size - " << size << std::endl;
                
                // device max work item sizes
                work_item = platformDevices[i][j].getInfo<CL_DEVICE_MAX_WORK_ITEM_SIZES>();
                std::cout << "   Device Max Work Item Sizes - ";
                
                for (auto x :work_item)
                    {
                        std::cout << x << ' ';
                    }
                
                std::cout << std::endl;
                
                // device local mmr size
                size = platformDevices[i][j].getInfo<CL_DEVICE_LOCAL_MEM_SIZE>();
                std::cout << "   Device Local Memory Size - " << size/1024 << "kb" << std::endl;
                
                // store option
                options.push_back(std::make_pair(i, j));
                optionCounter++; // increment option counter
            }
        }
        
        std::cout << "\n--------------------\n" << std::endl;
        std::cout << "Select a device: ";
        
        std::string inputString;
        unsigned int selectedOption;    // option that was selected
        
        std::getline(std::cin, inputString);
        std::istringstream stringStream(inputString);
        
        // check whether valid option was selected
        // check if input was an integer
        if (stringStream >> selectedOption)
        {
            char c;
            
            // check if there was anything after the integer
            if (!(stringStream >> c))
            {
                // check if valid option range
                if (selectedOption >= 0 && selectedOption < optionCounter)
                {
                    // return the platform and device
                    int platformNumber = options[selectedOption].first;
                    int deviceNumber = options[selectedOption].second;
                    
                    *platfm = platforms[platformNumber];
                    *dev = platformDevices[platformNumber][deviceNumber];
                    
                    return true;
                }
            }
        }
        // if invalid option selected
        std::cout << "\n--------------------\n" << std::endl;
        std::cout << "Invalid option." << std::endl;
    }
    // catch any OpenCL function errors
    catch (cl::Error e) 
	{
        // call function to handle errors
        handle_error(e);
    }
    
    return false;
}

// builds program from given filename
bool build_program(cl::Program* prog, const cl::Context* ctx, const std::string filename)
{
    // get devices from the context
    std::vector<cl::Device> contextDevices = ctx->getInfo<CL_CONTEXT_DEVICES>();
    
    // open input file stream to .cl file
    std::ifstream programFile(filename);
    
    // check whether file was opened
    if (!programFile.is_open())
    {
        std::cout << "File not found." << std::endl;
        return false;
    }
    
    // create program string and load contents from the file
    std::string programString(std::istreambuf_iterator<char>(programFile), (std::istreambuf_iterator<char>()));
    
    // create program source from one input string
    cl::Program::Sources source(1, std::make_pair(programString.c_str(), programString.length() + 1));
    // create program from source
    *prog = cl::Program(*ctx, source);
    
    // try to build program
    try {
        // build the program for the devices in the context
        prog->build(contextDevices);
        
        std::cout << "Program build: Successful." << std::endl;
        std::cout << "\n--------------------\n" << std::endl;

		// check build status for all all devices in context
		for (unsigned int i = 0; i < contextDevices.size(); i++)
		{
			// get device name and build log
			std::string outputString = contextDevices[i].getInfo<CL_DEVICE_NAME>();
			std::string build_log = prog->getBuildInfo<CL_PROGRAM_BUILD_LOG>(contextDevices[i]);

			std::cout << "Device - " << outputString << ", build log:" << std::endl;
			std::cout << build_log << "\n--------------------\n" << std::endl;
		}
    }
    catch (cl::Error e) {
        // if failed to build program
        if (e.err() == CL_BUILD_PROGRAM_FAILURE)
        {
            // output program build log
            std::cout << e.what() << ": Failed to build program." << std::endl;
            
            // check build status for all all devices in context
            for (unsigned int i = 0; i < contextDevices.size(); i++)
            {
                // get device's program build status and check for error
                // if build error, output build log
                if (prog->getBuildInfo<CL_PROGRAM_BUILD_STATUS>(contextDevices[i]) == CL_BUILD_ERROR)
                {
                    // get device name and build log
                    std::string outputString = contextDevices[i].getInfo<CL_DEVICE_NAME>();
                    std::string build_log = prog->getBuildInfo<CL_PROGRAM_BUILD_LOG>(contextDevices[i]);
                    
                    std::cout << "Device - " << outputString << ", build log:" << std::endl;
                    std::cout << build_log << "\n--------------------\n" << std::endl;
                }
            }
            return false;
        }
        else
        {
            // call function to handle errors
            handle_error(e);
        }
    }
    return true;
}

int main(void)
{
    cl::Platform platform;			// device's platform
	cl::Device device;				// device used
    cl::Context context;			// context for the device
    cl::Program program;			// OpenCL program object
    cl::CommandQueue queue;			// commandqueue for a context and device
    std::string outputString;		// string for output
    
    try {
		// select an OpenCL device
        if (!select_one_device(&platform, &device, devType(select_cpu_gpu())))
		{        
			// if no device selected
            quit_program("\nDevice not selected.");
        }
        
        // create a context from device
        context = cl::Context(device);
        
        // check devices in the context
        std::cout << "\nDevices in the context:" << std::endl;
        
        // get devices in the context
        std::vector<cl::Device> contextDevices = context.getInfo<CL_CONTEXT_DEVICES>();
        
        // output names of devices in the context
        for (int i = 0; i < contextDevices.size(); i++)
        {
            outputString = contextDevices[i].getInfo<CL_DEVICE_NAME>();
            std::cout << "  Device " << i << ": " << outputString << std::endl;
        }
        
        std::cout << "\n--------------------\n" << std::endl;

		// create command queue
		queue = cl::CommandQueue(context, device);
        
        // build the program
        if(!build_program(&program, &context, "source.cl"))
        {
            // if OpenCL program build error
            quit_program("OpenCL program build error.");
        }
        
        // create a kernel
		std::vector<cl::Kernel> kernels;
		program.createKernels(&kernels);

		//Find and display number of kernels in the program
		std::cout << "Number of kernels: " << program.getInfo<CL_PROGRAM_NUM_KERNELS>() << std::endl;
        
		//Display kernel names
		std::cout << "\nKernels:" << std::endl;
		for (auto x : kernels)
			std::cout << "   " << x.getInfo<CL_KERNEL_FUNCTION_NAME>() << std::endl;
        std::cout << "\n--------------------\n" << std::endl;
    }
    
    // catch any OpenCL function errors
    catch (cl::Error e) {
        // call function to handle errors
        handle_error(e);
    }
    
#ifdef _WIN32
    // wait for a keypress on Windows OS before exiting
    std::cout << "Press enter to quit...";
    std::cin.ignore();
#endif
    
    return 0;
}
