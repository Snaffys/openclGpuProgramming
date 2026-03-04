#include <CL/cl.h>
#include <iostream>

int main()
{
    cl_uint numPlatforms;
    cl_int status = clGetPlatformIDs(0, nullptr, &numPlatforms);

    if (status != CL_SUCCESS) {
        std::cerr << "Unable to get OpenCL platforms. Error: " << status << "\n";
        return 1;
    }

    std::cout << "Number of OpenCL platforms: " << numPlatforms << "\n";
    return 0;
}

