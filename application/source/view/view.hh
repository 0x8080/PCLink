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
		
		
		--->> view.hh
		
*/

#pragma once

#include <psp2/kernel/threadmgr.h>

#include "../graphics/texture-manager.hh"
#include "../ui/ui-splash.hh"
#include "../ui/ui-main.hh"
#include "../ui/ui-connect-manager.hh"
#include "../ui/ui-connect-add.hh"
#include "../ui/ui-connect.hh"




enum {
	VIEW_INIT,
	VIEW_SPLASH,
	VIEW_MAIN,
	VIEW_CONNECT_MAN,
	VIEW_CONNECT_ADD,
	VIEW_CONNECT,
	VIEW_SETTINGS,
	VIEW_CONTROLS,
	VIEW_STREAM,
	VIEW_EXIT
	};











class TextureManager;
class UiSplash;
class UiMain;
class UiConnectManager;
class UiConnectAdd;
class UiConnect;

class View {
	public:
		static View* getInstance();
		
		void load(unsigned int viewId);
		unsigned int currentView();
		void draw();
		
		unsigned int current;
		unsigned int target;
		bool wait;
		
	private:
		static bool instanceFlag;
		static View* view;
		
		View();
		
		TextureManager &textureManager = *TextureManager::getInstance();
		UiSplash &uiSplash = *UiSplash::getInstance();
		UiMain &uiMain = *UiMain::getInstance();
		UiConnectManager &uiConnectManager = *UiConnectManager::getInstance();
		UiConnectAdd &uiConnectAdd = *UiConnectAdd::getInstance();
		UiConnect &uiConnect = *UiConnect::getInstance();
		
		SceUID threadWaitID;
		void waitThread();
		
		~View();
		
	};
