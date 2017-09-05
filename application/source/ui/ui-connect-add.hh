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
		
		
		--->> ui-connect-add.hh
		
*/

#pragma once

#include "../graphics/texture-manager.hh"
#include "../graphics/font-manager.hh"
#include "../control/gamepad.hh"
#include "../control/touch.hh"
#include "../control/keyboard.hh"












class TextureManager;
class FontManager;
class Gamepad;
class Touch;
class Keyboard;

class UiConnectAdd {
	public:
		static UiConnectAdd* getInstance();
		
		bool init();
		void update();
		void draw();
		void release();
		bool isReleased();
		
	private:
		UiConnectAdd();
		
		static bool instanceFlag;
		static UiConnectAdd* uiConnectAdd;
		
		int alpha;
		int fadeType;
		bool active;
		bool released;
		
		bool btnStateCancel;
		bool btnStateOk;
		
		std::string input;
		
		int editIdx;
		
		bool checkBoxState;
		
		int selectionIdx;
		
		TextureManager &textureManager = *TextureManager::getInstance();
		FontManager &fontManager = *FontManager::getInstance();
		Gamepad &gamepad = *Gamepad::getInstance();
		Touch &touch = *Touch::getInstance();
		Keyboard &keyboard = *Keyboard::getInstance();
		
		vita2d_texture* textureBg;
		vita2d_texture* textureBtn[2];
		vita2d_texture* textureInput[2];
		vita2d_texture* textureCheckBox[3];
		
		void save();
		
		~UiConnectAdd();
		
	};
