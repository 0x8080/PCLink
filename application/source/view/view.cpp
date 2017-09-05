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
		
		
		--->> view.cpp
		
*/

#include "view.hh"

#include <debugnet.h>
#include <vita2d.h>




bool View::instanceFlag = false;
View* View::view = NULL;
View* viewCtx;
extern bool programRun;

View* View::getInstance() {
    if (!instanceFlag) {
        view = new View();
        instanceFlag = true;
        return view;
		}
    else
        return view;
	}















View::View() {
	current = VIEW_INIT;
	target = VIEW_INIT;
	wait = true;
	}


View::~View() {
	instanceFlag = false;
	}


void View::load(unsigned int viewId) {
	target = viewId;
	wait = true;
	switch (current) {
		case VIEW_INIT:			wait = false;
								break;
								
		case VIEW_SPLASH:		uiSplash.release();
								uiMain.init();
								wait = false;
								break;
								
		case VIEW_MAIN:			uiMain.release();
								break;
								
		case VIEW_CONNECT_MAN:	uiConnectManager.release();
								break;
								
		case VIEW_CONNECT_ADD:	uiConnectAdd.release();
								break;
		}
	if (wait) {
		threadWaitID = sceKernelCreateThread("PCLinkWaitThread", (SceKernelThreadEntry)&View::waitThread, 0x10000100, 0x10000, 0, 0, NULL);
		if (threadWaitID >= 0) {
			viewCtx = this;
			sceKernelStartThread(threadWaitID, 0, NULL);
			}
		return;
		}
	current = target;
	}


// wait thread for UI animations
void View::waitThread() {
	bool hold = true;
	while (hold) {
		switch (viewCtx->current) {
									
			case VIEW_MAIN:			if (viewCtx->uiMain.isReleased())
										hold = false;
									break;
									
			case VIEW_CONNECT_MAN:	if (viewCtx->uiConnectManager.isReleased())
										hold = false;
									break;
									
			case VIEW_CONNECT_ADD:	if (viewCtx->uiConnectAdd.isReleased())
										hold = false;
									break;
			}
		}
	
	switch (viewCtx->target) {
		case VIEW_MAIN: 		viewCtx->uiMain.init();
								break;
								
		case VIEW_CONNECT_MAN:	viewCtx->uiConnectManager.init();
								break;
								
		case VIEW_CONNECT_ADD:	viewCtx->uiConnectAdd.init();
								break;
								
		case VIEW_EXIT:			programRun = false;
								break;
		}
	viewCtx->current = viewCtx->target;
	sceKernelExitDeleteThread(0);
	}


unsigned int View::currentView() {
	return current;
	}


void View::draw() {
	
	switch (current) {
		case VIEW_SPLASH: 		uiSplash.update();
								textureManager.drawStart();
								uiSplash.draw();
								textureManager.drawEnd();
								break;
								
		case VIEW_MAIN:			uiMain.update();
								textureManager.drawStart();
								uiMain.draw();
								textureManager.drawEnd();
								break;
								
		case VIEW_CONNECT_MAN:	uiConnectManager.update();
								textureManager.drawStart();
								uiConnectManager.draw();
								textureManager.drawEnd();
								break;
								
		case VIEW_CONNECT_ADD:	uiConnectAdd.update();
								textureManager.drawStart();
								uiConnectAdd.draw();
								textureManager.drawEnd();
		}
	
	}
