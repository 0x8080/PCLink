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
		
		
		--->> utilities.hh
		
*/

#pragma once

#include <string>




#define VERSION_STRING "v0.1-a1"
#define SCREEN_WIDTH 960
#define SCREEN_HEIGHT 544

#define PATH_DIR_DATA_ROOT 		"ux0:data/pclink/"
#define PATH_DIR_PREVIEWS 		PATH_DIR_DATA_ROOT "previews/"

#define PATH_FILE_CONNECTIONS 	PATH_DIR_DATA_ROOT "connections.ini"
#define PATH_CONFIG_FILE 		PATH_DIR_DATA_ROOT "config.ini"

#define UTIL_MIN(x, y) (((x) < (y)) ? (x) : (y))
#define UTIL_MAX(x, y) (((x) > (y)) ? (x) : (y))

#define UTIL_OVERCLOCK_ALL 0
#define UTIL_OVERCLOCK_CPU 1
#define UTIL_OVERCLOCK_GPU 2
#define UTIL_OVERCLOCK_BUS 3
#define UTIL_OVERCLOCK_XBAR 4















class Utilities {
	
	public:
		static Utilities* getInstance();
		
		bool fileExists(const char* path);
		void fileDelete(const char* path);
		std::string fileName(std::string filePath);
		
		bool directoryCreate(std::string dirPath);
		bool directoryExists(const char* dirPath);
		void directoryDelete(const char* path);
		//void directoryRemove(const char* path);
		
		std::string stringWrap(std::string str, size_t width);
		
		void overclock(unsigned int target);
		void backlightOn();
		
	private:
		static bool instanceFlag;
		static Utilities* utilities;
		
		~Utilities();
	};
