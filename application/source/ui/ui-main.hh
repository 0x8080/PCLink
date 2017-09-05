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
		
		
		--->> ui-main.hh
		
*/

#pragma once

#include <vector>
#include <string>

#include "../graphics/texture-manager.hh"
#include "../graphics/font-manager.hh"
#include "../control/gamepad.hh"










class TextureManager;
class FontManager;
class Gamepad;

class UiMain {
	public:
		static UiMain* getInstance();
		
		bool init();
		void update();
		void draw();
		bool isReleased();
		void release();
		
	private:
		static bool instanceFlag;
		static UiMain* uiMain;
		
		UiMain();
		
		int whiteFadeAlpha;
		int alpha;
		int fadeType;
		
		bool active;
		bool released;
		
		std::vector<std::string> selectionLabels = {"Connection Manager", "Control Config", "Settings", "Exit"};
		unsigned int selectionIdx;
		int selectionRB;
		int selectionPulseDirection;
		int selectionAlpha;
		
		TextureManager &textureManager = *TextureManager::getInstance();
		FontManager &fontManager = *FontManager::getInstance();
		Gamepad &gamepad = *Gamepad::getInstance();
		
		vita2d_texture* textureBg;
		
		void updateMain();
		~UiMain();
		
	};
