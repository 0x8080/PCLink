/*
	
		Pc Link - Remote desktop streamer
		Playstation Vita [HENkaku Homebrew]
		
		
		This program is free software: you can redistribute it and/or modify
		it under the terms of the GNU General Public License as published by
		the Free Software Foundation, either version 3 of the License, or
		(at your option) any later version.
		
		This program is distributed in the hope that it will be useful,
		but WITHOUT ANY WARRANTY; without even the implied warranty of
		MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
		GNU General Public License for more details.
		
		You should have received a copy of the GNU General Public License
		along with this program.  If not, see <http://www.gnu.org/licenses/>.
		
		
		--->> utilities.cpp
		
*/

#include "utilities.hh"

#include <psp2/kernel/processmgr.h>
#include <psp2/power.h>
#include <psp2/io/stat.h>
#include <psp2/io/fcntl.h>




bool Utilities::instanceFlag = false;
Utilities* Utilities::utilities = NULL;


Utilities* Utilities::getInstance() {
    if (!instanceFlag) {
        utilities = new Utilities();
        instanceFlag = true;
        return utilities;
		}
    else
        return utilities;
	}

Utilities::~Utilities() {
	instanceFlag = false;
	}















// File handling --------------------------------------------------------
bool Utilities::fileExists(const char* path) {
	SceUID fd;
	if ((fd = sceIoOpen(path, SCE_O_RDONLY, 0777)) < 0)
		return false;
	sceIoClose(fd);
	return true;
	}


void Utilities::fileDelete(const char* path) {
	sceIoRemove(path);
	}


std::string Utilities::fileName(std::string filePath) {
	std::string path = filePath;
	const size_t lastSlashIdx = path.find_last_of("\\/");
	if (std::string::npos != lastSlashIdx)
		path.erase(0, lastSlashIdx + 1);
	return path;
	}


bool Utilities::directoryCreate(std::string dirPath) {
	if (sceIoMkdir(dirPath.c_str(), 0777) == 0)
		return true;
	return false;
	}


bool Utilities::directoryExists(const char* dirPath) {
	SceIoStat sb;
	if (sceIoGetstat(dirPath, &sb) == 0 && SCE_S_ISDIR(sb.st_mode))
		return true;
	return false;
	}


void Utilities::directoryDelete(const char* path) {
	sceIoRmdir(path);
	}

/*
void Utilities::directoryRemove(const char* path) {
	struct dirent* entry = NULL;
	DIR* dir = NULL;
	dir = opendir(path);
	while (entry = readdir(dir)) {
		DIR* sub_dir = NULL;
		FILE* file = NULL;
		char abs_path[100] = {0};
		if (*(entry->d_name) != '.') {
			sprintf(abs_path, "%s/%s", path, entry->d_name);
			if (sub_dir = opendir(abs_path)) {
				closedir(sub_dir);
				remove_dir(abs_path);
				}
			else  {
				if (file = fopen(abs_path, "r")) {
					fclose(file);
					remove(abs_path);
					}
				}
			}
		}
	remove(path);
	}
*/

// ----------------------------------------------------------------------


// String handling ------------------------------------------------------
std::string Utilities::stringWrap(std::string str, size_t width) {
    size_t curWidth = width;
    while (curWidth < str.length()) {
        std::string::size_type spacePos = str.rfind(' ', curWidth);
        if (spacePos == std::string::npos)
            spacePos = str.find(' ', curWidth);
        if (spacePos != std::string::npos) {
            str[spacePos] = '\n';
            curWidth = spacePos + width + 1;
			}
		}
    return str.substr(0, str.size() - 1);
	}

// ----------------------------------------------------------------------


// System handling ------------------------------------------------------
void Utilities::overclock(unsigned int target) {
	switch (target) {
		case 0:		// ALL
					scePowerSetArmClockFrequency(444);
					scePowerSetGpuClockFrequency(222);
					scePowerSetBusClockFrequency(222);
					scePowerSetGpuXbarClockFrequency(166);
					break;
		case 1:		// CPU
					scePowerSetArmClockFrequency(444);
					break;
		case 2:		// GPU
					scePowerSetGpuClockFrequency(222);
					break;
		case 3:		// BUS
					scePowerSetBusClockFrequency(222);
					break;
		case 4:		// GPU XBAR
					scePowerSetGpuXbarClockFrequency(166);
					break;
		
		}
	}


void Utilities::backlightOn() {
	sceKernelPowerTick(SCE_KERNEL_POWER_TICK_DEFAULT);
	}

// ----------------------------------------------------------------------
