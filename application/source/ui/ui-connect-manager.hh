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
		
		
		--->> ui-connect-manager.hh
		
*/

#pragma once

#include <psp2/kernel/threadmgr.h>

#include <vector>


#include "../network/connection.hh"
#include "../graphics/texture-manager.hh"
#include "../graphics/font-manager.hh"
#include "../control/gamepad.hh"
#include "../control/touch.hh"












class TextureManager;
class FontManager;
class Gamepad;
class Touch;

class UiConnectManager {
	public:
		static UiConnectManager* getInstance();
		
		bool init();
		void update();
		void draw();
		void release();
		bool isReleased();
		int getEditIdx();
		void setEditIdx(int _idx);
		
	private:
		UiConnectManager();
		
		static bool instanceFlag;
		static UiConnectManager* uiConnectManager;
		
		std::vector<Connection*> connectionList;
		
		int yOrigin;
		bool scrolling;
		int prevY;
		bool useMomentum;
		double momentum;
		int scrollDir;
		int ground;
		bool clickable;
		int newY;
		
		int alpha;
		int fadeType;
		bool active;
		bool released;
		
		int selectionIdx;
		int touchIdx;
		int editIdx;
		
		bool btnStateAdd;
		
		SceUID threadLoadID;
		void loadThread();
		
		void scroll();
		
		TextureManager &textureManager = *TextureManager::getInstance();
		FontManager &fontManager = *FontManager::getInstance();
		Gamepad &gamepad = *Gamepad::getInstance();
		Touch &touch = *Touch::getInstance();
		
		vita2d_texture* textureBg;
		
		~UiConnectManager();
		
	};
