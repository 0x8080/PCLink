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
		
		
		--->> gamepad.hh
	
*/

#pragma once

#include <psp2/ctrl.h>




#define SCE_CTRL_LEFT_ANALOG_UP 0x0200000
#define SCE_CTRL_LEFT_ANALOG_DOWN 0x0800000
#define SCE_CTRL_LEFT_ANALOG_LEFT 0x1000000
#define SCE_CTRL_LEFT_ANALOG_RIGHT 0x0400000

#define SCE_CTRL_RIGHT_ANALOG_UP 0x0020000
#define SCE_CTRL_RIGHT_ANALOG_RIGHT 0x0040000
#define SCE_CTRL_RIGHT_ANALOG_DOWN 0x0080000
#define SCE_CTRL_RIGHT_ANALOG_LEFT 0x0100000

#define SCE_CTRL_ANALOG_CENTER 128
#define SCE_CTRL_ANALOG_THRESHOLD 120

/*
	SCE_CTRL_UP
	SCE_CTRL_DOWN
	SCE_CTRL_LEFT
	SCE_CTRL_RIGHT
	SCE_CTRL_CROSS
	SCE_CTRL_CIRCLE
	SCE_CTRL_SQUARE
	SCE_CTRL_TRIANGLE
	SCE_CTRL_LTRIGGER
	SCE_CTRL_RTRIGGER
	SCE_CTRL_SELECT
	SCE_CTRL_START
*/















class Gamepad {
	public:
		static Gamepad* getInstance();
		
		SceCtrlData data();
		void update();
		bool checkPressed(int button);
		bool checkReleased(int button);
		
	private:
		static bool instanceFlag;
		static Gamepad* gamepad;
		
		Gamepad();
		
		SceCtrlData ctrlData;
		
		uint32_t buttonsCurrent;
		uint32_t buttonsPrevious;
		uint32_t buttonsPressed;
		uint32_t buttonsReleased;
		uint32_t buttonsHeldA;
		uint32_t buttonsHeldB;
		
		~Gamepad();
		
	};
