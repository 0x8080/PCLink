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
		
		
		--->> ui-connect.cpp
		
*/

#include "ui-connect.hh"




bool UiConnect::instanceFlag = false;
UiConnect* UiConnect::uiConnect = NULL;
UiConnect* uiConnectCtx;

UiConnect* UiConnect::getInstance() {
    if (!instanceFlag) {
        uiConnect = new UiConnect();
        instanceFlag = true;
        return uiConnect;
		}
    else
        return uiConnect;
	}















UiConnect::UiConnect() {
	alpha = 0;
	fadeType = 0;
	released = true;
	}


UiConnect::~UiConnect() {
	instanceFlag = false;
	}


bool UiConnect::init() {
	textureBg = textureManager.getTexture("img_uimain_bg.png");
	textureIcon[0] = textureManager.getTexture("img_rep_icn_pc_large.png");
	textureIcon[1] = textureManager.getTexture("img_rep_icn_vita_large.png");
	textureLoad[0] = textureManager.getTexture("img_rep_loadinga.png");
	textureLoad[1] = textureManager.getTexture("img_rep_loadingb.png");
	
	alpha = 0;
	fadeType = 1;
	released = false;
	}


void UiConnect::connectThread() {
	
	
	
	}