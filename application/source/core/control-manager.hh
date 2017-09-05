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


		--->> control-manager.hh

*/

#pragma once

#include <psp2/ctrl.h>
#include <psp2/touch.h>




/*	SCE_CTRL_UP
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
	SCE_CTRL_START */















class ControlManager {
	public:
		static ControlManager* getInstance();

		// gamepad
		SceCtrlData getCtrlData();
		void gamepadUpdate();
		bool gamepadCheckPressed(int _btn);
		bool gamepadCheckReleased(int _btn);

		// touch
		SceTouchData getTouchData();
		int  touchGetX();
		int  touchGetY();
		bool touchCheckPressed();
		bool touchCheckReleased();
		bool touchCheckHeld();
		bool touchInX(int _x1, int _x2);
		bool touchInY(int _y1, int _y2);
		bool inRectangle(int _x1, int _y1, int _x2, int _y2);
		void touchUpdate();


	private:
		static bool instanceFlag;
		static ControlManager* controlManager;

		ControlManager();

		// gamepad
		SceCtrlData ctrlData;
		uint32_t buttonsCurrent;
		uint32_t buttonsPrevious;
		uint32_t buttonsPressed;
		uint32_t buttonsReleased;
		uint32_t buttonsHeldA;
		uint32_t buttonsHeldB;

		// touch
		SceTouchData touchData;
		int touchX = 0;
		int touchY = 0;
		bool held = false;
		bool pressed = false;
		bool pressedPrev = false;
		bool released = false;
		bool releasedPrev = false;














		~ControlManager();
	};
