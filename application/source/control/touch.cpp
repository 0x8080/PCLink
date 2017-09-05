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
		
		
		--->> touch.cpp
	
*/

#include "touch.hh"

#include <cstring>




#define lerp(value, from_max, to_max) ((((value * 10) * (to_max * 10)) / (from_max * 10)) / 10)
#define pointInRectangle(px, py, x1, y1, x2, y2) ((px) > (x1) && (px) < (x2) && (py) > (y1) && (py) < (y2) ? 1 : 0)
#define pointInY(py, y1, y2) ((py) > (y1) && (py) < (y2) ? 1 : 0)
#define pointInX(px, x1, x2) ((px) > (x1) && (px) < (x2) ? 1 : 0)


bool Touch::instanceFlag = false;
Touch* Touch::touch = NULL;


Touch* Touch::getInstance() {
    if (!instanceFlag) {
        touch = new Touch();
        instanceFlag = true;
        return touch;
		}
    else
        return touch;
	}















Touch::Touch() {
	sceTouchSetSamplingState(SCE_TOUCH_PORT_FRONT, SCE_TOUCH_SAMPLING_STATE_START);
	memset(&touchData, 0, sizeof(SceTouchData));
	}


Touch::~Touch() {
	// release
	
	
	instanceFlag = false;
	}


int Touch::getX() {
	return posX;
	}


int Touch::getY() {
	return posY;
	}


bool Touch::checkPressed() {
	return pressed;
	}


bool Touch::checkReleased() {
	return released;
	}

bool Touch::checkHeld() {
	return held;
	}


bool Touch::inX(int x1, int x2) {
	return pointInX(posX, x1, x2);
	}


bool Touch::inY(int y1, int y2) {
	return pointInY(posY, y1, y2);
	}


bool Touch::inRectangle(int x1, int y1, int x2, int y2) {
	return pointInRectangle(posX, posY, x1, y1, x2, y2);
	}


// TODO: Touch::inCircle

	
void Touch::update() {
	// TODO: private, update only when required.
	sceTouchPeek(SCE_TOUCH_PORT_FRONT, &touchData, 1);
	if (touchData.reportNum > 0) {
		held = true;
		posX = (lerp(touchData.report[0].x, 1919, 960));
		posY = (lerp(touchData.report[0].y, 1087, 544));
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
