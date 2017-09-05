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
		
		
		--->> ui-connect.hh
		
*/

#pragma once

#include <psp2/kernel/threadmgr.h>

#include "../graphics/texture-manager.hh"
#include "../graphics/font-manager.hh"
#include "../control/gamepad.hh"
#include "../network/network.hh"












class TextureManager;
class FontManager;
class Gamepad;
class Network;

class UiConnect {
	public:
		static UiConnect* getInstance();
		bool init();
		
	private:
		UiConnect();
		
		static bool instanceFlag;
		static UiConnect* uiConnect;
		
		enum {
			CONNECT_STATE_INIT,
			CONNECT_STATE_
			};
		
		int alpha;
		int fadeType;
		bool released;
		
		TextureManager &textureManager = *TextureManager::getInstance();
		FontManager &fontManager = *FontManager::getInstance();
		Gamepad &gamepad = *Gamepad::getInstance();
		Network &network = *Network::getInstance();
		
		vita2d_texture* textureBg;
		vita2d_texture* textureIcon[2];
		vita2d_texture* textureLoad[2];
		
		SceUID threadConnectID;
		void connectThread();
		
		~UiConnect();
		
	};
