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


		--->> control-manager.cpp

*/

#include "control-manager.hh"

#include <cstring>




#define SCE_CTRL_LEFT_ANALOG_UP 	0x0200000
#define SCE_CTRL_LEFT_ANALOG_DOWN 	0x0800000
#define SCE_CTRL_LEFT_ANALOG_LEFT 	0x1000000
#define SCE_CTRL_LEFT_ANALOG_RIGHT 	0x0400000

#define SCE_CTRL_RIGHT_ANALOG_UP 	0x0020000
#define SCE_CTRL_RIGHT_ANALOG_RIGHT 0x0040000
#define SCE_CTRL_RIGHT_ANALOG_DOWN 	0x0080000
#define SCE_CTRL_RIGHT_ANALOG_LEFT 	0x0100000

#define SCE_CTRL_ANALOG_CENTER 		128
#define SCE_CTRL_ANALOG_THRESHOLD 	120

#define lerp(value, from_max, to_max) ((((value * 10) * (to_max * 10)) / (from_max * 10)) / 10)
#define pointInRectangle(px, py, x1, y1, x2, y2) ((px) > (x1) && (px) < (x2) && (py) > (y1) && (py) < (y2) ? 1 : 0)
#define pointInY(py, y1, y2) ((py) > (y1) && (py) < (y2) ? 1 : 0)
#define pointInX(px, x1, x2) ((px) > (x1) && (px) < (x2) ? 1 : 0)


bool ControlManager::instanceFlag = false;
ControlManager* ControlManager::controlManager = NULL;


ControlManager* ControlManager::getInstance() {
    if (!instanceFlag) {
        controlManager = new ControlManager();
        instanceFlag = true;
        return controlManager;
		}
    else
        return controlManager;
	}







ControlManager::ControlManager() {
	sceCtrlSetSamplingMode(SCE_CTRL_MODE_ANALOG);
	std::memset(&ctrlData, 0, sizeof(ctrlData));
	sceTouchSetSamplingState(SCE_TOUCH_PORT_FRONT, SCE_TOUCH_SAMPLING_STATE_START);
	std::memset(&touchData, 0, sizeof(SceTouchData));
	}


ControlManager::~ControlManager() {
	instanceFlag = false;
	}


// gamepad
SceCtrlData ControlManager::getCtrlData() {
	return ctrlData;
	}


void ControlManager::gamepadUpdate() {
	// TODO: private, update only when required.
	sceCtrlPeekBufferPositive(0, &ctrlData, 1);

	if (ctrlData.ly < SCE_CTRL_ANALOG_CENTER - SCE_CTRL_ANALOG_THRESHOLD)
		ctrlData.buttons |= SCE_CTRL_LEFT_ANALOG_UP;
	else if (ctrlData.ly > SCE_CTRL_ANALOG_CENTER + SCE_CTRL_ANALOG_THRESHOLD)
		ctrlData.buttons |= SCE_CTRL_LEFT_ANALOG_DOWN;

	if (ctrlData.lx < SCE_CTRL_ANALOG_CENTER - SCE_CTRL_ANALOG_THRESHOLD)
		ctrlData.buttons |= SCE_CTRL_LEFT_ANALOG_LEFT;
	else if (ctrlData.lx > SCE_CTRL_ANALOG_CENTER + SCE_CTRL_ANALOG_THRESHOLD)
		ctrlData.buttons |= SCE_CTRL_LEFT_ANALOG_RIGHT;

	if (ctrlData.ry < SCE_CTRL_ANALOG_CENTER - SCE_CTRL_ANALOG_THRESHOLD)
		ctrlData.buttons |= SCE_CTRL_RIGHT_ANALOG_UP;
	else if (ctrlData.ry > SCE_CTRL_ANALOG_CENTER + SCE_CTRL_ANALOG_THRESHOLD)
		ctrlData.buttons |= SCE_CTRL_RIGHT_ANALOG_DOWN;

	if (ctrlData.rx < SCE_CTRL_ANALOG_CENTER - SCE_CTRL_ANALOG_THRESHOLD)
		ctrlData.buttons |= SCE_CTRL_RIGHT_ANALOG_LEFT;
	else if (ctrlData.rx > SCE_CTRL_ANALOG_CENTER + SCE_CTRL_ANALOG_THRESHOLD)
		ctrlData.buttons |= SCE_CTRL_RIGHT_ANALOG_RIGHT;

	buttonsCurrent = ctrlData.buttons;
	buttonsPressed = buttonsCurrent & ~buttonsPrevious;
	buttonsHeldA = buttonsPressed;
	buttonsHeldB = buttonsPressed;
	buttonsReleased = ~buttonsCurrent & buttonsPrevious;

	// FIX: hold buttons
	static int holdN = 0, holdN2 = 0;
	if (buttonsPrevious == buttonsCurrent) {
		holdN++;
		if (holdN >= 10) {
			buttonsHeldA = buttonsCurrent;
			holdN = 6;
			}

		holdN2++;
		if (holdN2 >= 10) {
			buttonsHeldB = buttonsCurrent;
			holdN2 = 10;
			}
		}
	else {
		holdN = 0;
		holdN2 = 0;
		buttonsPrevious = buttonsCurrent;
		}
	}


bool ControlManager::gamepadCheckPressed(int _btn) {
	return (bool)(buttonsPressed & _btn);
	}


bool ControlManager::gamepadCheckReleased(int _btn) {
	return (bool)(buttonsReleased & _btn);
	}


// touch
SceTouchData ControlManager::getTouchData() {
	return touchData;
	}


int ControlManager::touchGetX() {
	return touchX;
	}


int ControlManager::touchGetY() {
	return touchY;
	}


bool ControlManager::touchCheckPressed() {
	return pressed;
	}


bool ControlManager::touchCheckReleased() {
	return released;
	}

bool ControlManager::touchCheckHeld() {
	return held;
	}


bool ControlManager::touchInX(int _x1, int _x2) {
	return pointInX(touchX, _x1, _x2);
	}


bool ControlManager::touchInY(int _y1, int _y2) {
	return pointInY(touchY, _y1, _y2);
	}


bool ControlManager::inRectangle(int _x1, int _y1, int _x2, int _y2) {
	return pointInRectangle(touchX, touchY, _x1, _y1, _x2, _y2);
	}


// TODO: Touch::inCircle


void ControlManager::touchUpdate() {
	// TODO: private, update only when required.
	sceTouchPeek(SCE_TOUCH_PORT_FRONT, &touchData, 1);
	if (touchData.reportNum > 0) {
		held = true;
		touchX = (lerp(touchData.report[0].x, 1919, 960));
		touchY = (lerp(touchData.report[0].y, 1087, 544));
		released = false;
		releasedPrev = false;
		if (!pressedPrev) {
			pressedPrev = true;
			pressed = true;
			}
		else
			pressed = false;
		}
	else {
		held = false;
		pressed = false;
		pressedPrev = false;
		if (!releasedPrev) {
			releasedPrev = true;
			released = true;
			}
		else
			released = false;
		}
	}
