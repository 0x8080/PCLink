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
		
		
		--->> ui-connect-manager.cpp
		
*/

#include "ui-connect-manager.hh"

#include <debugnet.h>
#include <cmath>

#include "../view/view.hh"
#include "../util/utilities.hh"
extern "C"
{
#include <vitaIni.h>
}

#define LIST_SPACING 154
#define LIST_START_POSITION 92
#define ALPHA_SPEED 34




bool UiConnectManager::instanceFlag = false;
UiConnectManager* UiConnectManager::uiConnectManager = NULL;
UiConnectManager* connectManagerCtx;

UiConnectManager* UiConnectManager::getInstance() {
    if (!instanceFlag) {
        uiConnectManager = new UiConnectManager();
        instanceFlag = true;
        return uiConnectManager;
		}
    else
        return uiConnectManager;
	}















UiConnectManager::UiConnectManager() {
	yOrigin = 0;
	scrolling = false;
	prevY = 0;
	useMomentum = true;
	momentum = 0;
	scrollDir = 0;
	ground = 0;
	clickable = true;
	newY = 0;
	alpha = 0;
	fadeType = 1;
	btnStateAdd = false;
	selectionIdx = -1;
	touchIdx = -1;
	editIdx = -1;
	active = false;
	released = true;
	}


UiConnectManager::~UiConnectManager() {
	instanceFlag = false;
	}


bool UiConnectManager::init() {
	fadeType = 1;
	textureBg = textureManager.getTexture("img_uimain_bg.png");
	active = true;
	released = false;
	// TODO: amend priority
	threadLoadID = sceKernelCreateThread("PCLinkUiConnectManagerThread", (SceKernelThreadEntry)&UiConnectManager::loadThread, 0x10000100, 0x10000, 0, 0, NULL);
	if (threadLoadID >= 0) {
		connectManagerCtx = this;
		sceKernelStartThread(threadLoadID, 0, NULL);
		return true;
		}
	debugNetPrintf(ERROR, "UiConnectManager::init(): failed to start loadThread.\n");
	return false;
	}


void UiConnectManager::loadThread() {
	iniOpen(PATH_FILE_CONNECTIONS);
	unsigned int connectionCount = iniReadReal("CONNECTIONS", "connectionCount", 0);
	unsigned int i;
	char ipStr[32];
	char sectStr[64];
	for (i = 0; i < connectionCount; i++ ) {
		sprintf(sectStr, "CONNECTION%d\0", (i + 1));
		iniReadString(ipStr, sectStr, "ip", "\0");
		if (ipStr == '\0')
			continue;
		Connection* conn = new Connection(ipStr);
		connectManagerCtx->connectionList.push_back(conn);
		}
	sceKernelExitDeleteThread(0);
	}


void UiConnectManager::update() {
	// fade
	if (fadeType) {
		if (alpha < (255 - ALPHA_SPEED))
			alpha += ALPHA_SPEED;
		else
			alpha = 255;
		}
	else {
		if (alpha > ALPHA_SPEED)
			alpha -= ALPHA_SPEED;
		else {
			alpha = 0;
			connectionList.clear();
			released = true;
			}
		}
	
	
	
	// gamepad
	if (gamepad.checkPressed(SCE_CTRL_SQUARE)) {
		View &view = *View::getInstance();
		// TODO: add audio call
		
		view.load(VIEW_CONNECT_ADD);
		}
	if (gamepad.checkPressed(SCE_CTRL_CIRCLE)) {
		View &view = *View::getInstance();
		// TODO: add audio call
		
		view.load(VIEW_MAIN);
		}
	
	// touch
	if (touch.checkPressed()) {
		if (touch.inX(33, 255)) {
			touchIdx = floor((abs(yOrigin) + touch.getY() - LIST_START_POSITION) / LIST_SPACING);
			if (touchIdx > connectionList.size())
				touchIdx = -1;
			else {
				if (touch.inX(185, 255)) {
					unsigned int i;
					int tarY;
					for (i = 0; i < connectionList.size(); i++) {
						tarY = yOrigin + LIST_START_POSITION + (i * LIST_SPACING) + 89;
						if (touch.inY(tarY, tarY + 40))
							editIdx = i;
						}
					}
				}
			}
		else if (touch.inRectangle(898, 0, 960, 62)) {
			btnStateAdd = true;
			}
		}
	
	if (touch.checkReleased()) {
		if (touch.inX(33, 255)) {
			if (editIdx >= 0) {
				View &view = *View::getInstance();
				view.load(VIEW_CONNECT_ADD);
				}
			else if (touchIdx >= 0) {
				
				
				
				
				}
			}
		else if (touch.inRectangle(898, 0, 960, 62)) {
			View &view = *View::getInstance();
			view.load(VIEW_CONNECT_ADD);
			}
		
		
		btnStateAdd = false;
		touchIdx = -1;
		}
	
	scroll();
	}


void UiConnectManager::scroll() {
	if (momentum < -1 || momentum > 1) {
		clickable = false;
		touchIdx = -1;
		editIdx = -1;
		}
	else if (!scrolling)
		clickable = true;
		
	if (touch.getY() > 64) {
		if (scrolling && ground > 480) {
			if (touch.checkHeld()) {
				newY = yOrigin + (touch.getY() - prevY);
				if (useMomentum) {
					momentum = abs(round((touch.getY() - prevY) / 2));
					if (touch.getY() - prevY > 0)
						scrollDir = 1;
					else
						scrollDir = 0;
					}
				if (newY > 0)
					newY = 0;
				if (newY - 544 < (-ground))
					newY = (-ground) + 544;
				yOrigin = newY;
				prevY = touch.getY();          
				}
			if (touch.checkReleased()) {
				prevY = 0;
				scrolling = false;
				}
			}
		else {
			if (touch.checkPressed()) {
				scrolling = true;
				prevY = touch.getY();
				}
			if (useMomentum && momentum > 0) {
				newY = 0;
				if (scrollDir == 1) {
					newY = yOrigin + momentum;
					if (newY > 0) {
						newY = 0;
						momentum = 0;
						}
					}
				else {
					newY = yOrigin - momentum;
					if (newY - 544 <= (-ground)) {
						newY = (-ground) + 544;
						momentum = 0;
						}
					}
				yOrigin = newY;
				if (momentum > 0)
					momentum -= 0.2;
				}    
			}
		}
	}


void UiConnectManager::draw() {
	textureManager.drawTexturePart(textureBg, 0, 64, 0, 64, 960, 416);
	
	fontManager.setHalign(FONT_ALIGN_CENTER);
	fontManager.setValign(FONT_ALIGN_MIDDLE);
	
	if (!connectionList.size()) {
		fontManager.draw(FNT_GST_24, 480, 120, RGBA8(255, 255, 255, alpha), "To get started, add the remote desktop");
		fontManager.draw(FNT_GST_24, 480, 145, RGBA8(255, 255, 255, alpha), "that you would like to connect to.");
		}
	else {
		unsigned int i;
		int a = 0;
		int posy = yOrigin + LIST_START_POSITION;
		for (i = 0; i < connectionList.size(); i++) {
			connectionList[i]->setHighlight((i == touchIdx));
			connectionList[i]->setEditHighlight((i == editIdx));
			connectionList[i]->draw(34, posy);
			posy += LIST_SPACING;
			}
		ground = UTIL_MAX(475, (posy + 92));
		}
	
	textureManager.drawTexturePart(textureBg, 0, 0, 0, 0, 960, 64);
	textureManager.drawTexturePart(textureBg, 0, 480, 0, 480, 960, 64);
	
	fontManager.setHalign(FONT_ALIGN_CENTER);
	fontManager.draw(FNT_GST_35, 480, 44, RGBA8(255, 255, 255, alpha), "Connection Manager");
	if (btnStateAdd) {
		textureManager.drawRectangle(884, 0, 76, 63, RGBA8(255, 255, 255, 119));
		textureManager.drawRectangle(909, 30, 26, 3, RGBA8(48, 48, 48, 255));
		textureManager.drawRectangle(920, 18, 3, 26, RGBA8(48, 48, 48, 255));
		}
	else {
		textureManager.drawRectangle(909, 30, 26, 3, RGBA8(255, 255, 255, alpha));
		textureManager.drawRectangle(920, 18, 3, 26, RGBA8(255, 255, 255, alpha));
		}
	}

void UiConnectManager::release() {
	fadeType = 0;
	}

bool UiConnectManager::isReleased() {
	return released;
	}


int UiConnectManager::getEditIdx() {
	return editIdx;
	}


void UiConnectManager::setEditIdx(int _idx) {
	editIdx = _idx;
	}