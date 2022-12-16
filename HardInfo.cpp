/* ******************** HardInfo 1.0 ****************** */
 /*   Collect system information from x64 and x86 machines.
  *   MIT Licence.
  *   Compile using gcc 11.1 (https://gcc.gnu.org/)
  *   Created by Daniel Fros (Dec. 2022)
 * */



#include <iostream>
#include <cpuid.h>
#include <stdio.h>
#include <string.h>
#include <cstring>
#include "sys/sysinfo.h"
#include "sys/types.h"
#include <unistd.h>


using namespace std;

    string GetOperatingSystem_Name(){
#ifdef _WIN64
	    return "Windows 64-bit.";
#elif _WIN32
	    return "Windows 32-bit.";
#elif __APPLE__ || __MACH__
	    return "Mac OSX";
#elif __linux__
	    return "Linux";
#endif

		
    }


	int main() {
	char CPUBrandString[0x40];
	unsigned int CPUInfo[4] = {0,0,0,0};

	__cpuid(0x80000000, CPUInfo[0], CPUInfo[1], CPUInfo[2], CPUInfo[3]);
	unsigned int nExIds = CPUInfo[0];

	memset(CPUBrandString, 0, sizeof(CPUBrandString));
 
	for (unsigned int i = 0x80000000; i <= nExIds; ++i)
	{
    		__cpuid(i, CPUInfo[0], CPUInfo[1], CPUInfo[2], CPUInfo[3]);

    	if (i == 0x80000002)
        	memcpy(CPUBrandString, CPUInfo, sizeof(CPUInfo));
    	else if (i == 0x80000003)
        	memcpy(CPUBrandString + 16, CPUInfo, sizeof(CPUInfo));
    	else if (i == 0x80000004)
        	memcpy(CPUBrandString + 32, CPUInfo, sizeof(CPUInfo));
	}
	

	// string includes manufacturer, model and clockspeed.
	cout << "=====================CPU======================" << endl;
	cout << "CPU Type: " << CPUBrandString << endl;
	cout << "\n" << endl;

	


	// Get total system memory
	long pages = sysconf(_SC_PHYS_PAGES);
	long page_size = sysconf(_SC_PAGE_SIZE);
	long totalMem = pages * page_size;
	int totalMemInMB = totalMem / 1024;
	int totalMemInGB = totalMemInMB / 1024;

	cout << "=====================MEMORY===================" << endl;
	cout << "Total System Memory: " << totalMemInMB << " MB  ~  " << totalMemInGB << " GB "  << endl;
	cout << "\n" << endl;
	cout << "================OPERATING SYSTEM==============" << endl;
	cout << GetOperatingSystem_Name() << endl;
			
	}
