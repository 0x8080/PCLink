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
		
		
		--->> network.hh
		
*/

#pragma once

#include <string>




enum {
	CMD_TYPE_CONNECTION,
	CMD_TYPE_VIDEO,
	CMD_TYPE_AUDIO,
	CMD_TYPE_NETWORK,
	CMD_TYPE_KEYBOARD,
	CMD_TYPE_MOUSE,
	CMD_TYPE_OS
	};

enum {
	CMD_CONNECTION_CONNECT,
	CMD_CONNECTION_DISCONNECT,
	CMD_CONNECTION_GET_PC_INFO,
	CMD_CONNECTION_SET_CONFIG,
	
	CMD_VIDEO_ENABLED,
	CMD_VIDEO_RESOLUTION,
	CMD_VIDEO_QUALITY,
	CMD_VIDEO_REFRESH_RATE,
	CMD_VIDEO_FOLLOW_MOUSE,
	CMD_VIDEO_PINCH_ZOOM,
	CMD_VIDEO_MOUSE_CURSOR,
	
	CMD_AUDIO_ENABLED,
	
	CMD_KEYBOARD_PRESS,
	CMD_KEYBOARD_RELEASE,
	
    CMD_MOUSE_POSITION,
	CMD_MOUSE_LEFT_BTN,
	CMD_MOUSE_MIDDLE_BTN,
    CMD_MOUSE_RIGHT_BTN,
	
	CMD_OS_SHUTDOWN,
	CMD_OS_RESET,
	CMD_OS_SLEEP,
	CMD_OS_GET_SUPPORTED_RESOLUTIONS,
	CMD_OS_GET_RESOLUTION,
	CMD_OS_SET_RESOLUTION,
	CMD_OS_SET_ORIENTATION,
	CMD_OS_SET_DISPLAY_STATE // on/off
	};















class Network {
	public:
		static Network* getInstance();
		
		void connect();
		
		bool init(std::string ip);
		bool isInitialized();
		std::string getNetworkInfo();
		
	private:
		static bool instanceFlag;
		static Network* network;
		
		bool initialized;
		int socket;
		std::string networkInfo;
		
		int bytesRecieved;
		unsigned char* bufferIn;
		unsigned char* bufferOut;
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		Network();
		
		
		~Network();
		
	};
