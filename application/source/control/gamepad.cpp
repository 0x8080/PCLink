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
		
		This Class is based on code provided by 'TheFlow'.
		--->> gamepad.cpp
	
*/

#include "gamepad.hh"

#include <cstring>




bool Gamepad::instanceFlag = false;
Gamepad* Gamepad::gamepad = NULL;

Gamepad* Gamepad::getInstance() {
    if(!instanceFlag) {
        gamepad = new Gamepad();
        instanceFlag = true;
        return gamepad;
		}
    else
        return gamepad;
	}















Gamepad::Gamepad() {
	sceCtrlSetSamplingMode(SCE_CTRL_MODE_ANALOG);
	memset(&ctrlData, 0, sizeof(ctrlData));
	}


Gamepad::~Gamepad() {
	
	
	instanceFlag = false;
	}


SceCtrlData Gamepad::data() {
	return ctrlData;
	}


void Gamepad::update() {
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


bool Gamepad::checkPressed(int button) {
	return (bool)(buttonsPressed & button);
	}


bool Gamepad::checkReleased(int button) {
	return (bool)(buttonsReleased & button);
	}
