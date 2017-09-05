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
		
		
		--->> touch.hh
	
*/

#pragma once

#include <psp2/touch.h>















class Touch {
	public:
		static Touch* getInstance();
		
		int getX();
		int getY();
		
		bool checkPressed();
		bool checkReleased();
		bool checkHeld();
		
		bool inX(int x1, int x2);
		bool inY(int y1, int y2);
		bool inRectangle(int x1, int y1, int x2, int y2);
		
		void update();
		
	private:
		static bool instanceFlag;
		static Touch* touch;
		
		SceTouchData touchData;
		
		Touch();
		
		int posX = 0;
		int posY = 0;
		bool held = false;
		bool pressed = false;
		bool pressedPrev = false;
		bool released = false;
		bool releasedPrev = false;
		
		~Touch();
		
	};
