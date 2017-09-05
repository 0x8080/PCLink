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
		
		
		--->> ui-main.cpp
		
*/

#include "ui-main.hh"

#include <debugnet.h>

#include "../view/view.hh"
#include "../util/utilities.hh"

#define ALPHA_SPEED 34
#define PULSE_SPEED 7




bool UiMain::instanceFlag = false;
UiMain* UiMain::uiMain = NULL;

UiMain* UiMain::getInstance() {
    if (!instanceFlag) {
        uiMain = new UiMain();
        instanceFlag = true;
        return uiMain;
		}
    else
        return uiMain;
	}















UiMain::UiMain() {
	whiteFadeAlpha = 255;
	alpha = 255;
	fadeType = 0;
	selectionIdx = -1;
	selectionRB = 0;
	selectionPulseDirection = 1;
	selectionAlpha = 255;
	active = false;
	released = true;
	}


UiMain::~UiMain() {
	instanceFlag = false;
	}


bool UiMain::init() {
	textureBg = textureManager.getTexture("img_uimain_bg.png");
	fadeType = 1;
	active = true;
	released = false;
	return true;
	}


void UiMain::update() {
	// main white fade in
	if (whiteFadeAlpha > ALPHA_SPEED)
		whiteFadeAlpha -= ALPHA_SPEED;
	else
		whiteFadeAlpha = 0;
	
	// main fade
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
			released = true;
			}
		}
	
	// pulse animation
	if (selectionPulseDirection) {
		if (selectionRB < (255 - PULSE_SPEED))
			selectionRB += PULSE_SPEED;
		else {
			selectionRB = 255;
			selectionPulseDirection = !selectionPulseDirection;
			}
		}
	else {
		if (selectionRB > PULSE_SPEED)
			selectionRB -= PULSE_SPEED;
		else
			selectionPulseDirection = !selectionPulseDirection;
		}
	
	// gamepad
	if (gamepad.checkPressed(SCE_CTRL_UP)) {
		if (selectionIdx == 0)
			return;
		selectionIdx = UTIL_MAX(0, selectionIdx - 1);
		// TODO: add audio call
		
		}
	else if (gamepad.checkPressed(SCE_CTRL_DOWN)) {
		if (selectionIdx == 3)
			return;
		selectionIdx = UTIL_MIN(3, selectionIdx + 1);
		// TODO: add audio call
		
		}
	else if (gamepad.checkPressed(SCE_CTRL_CROSS)) {
		if (selectionIdx < 0) {
			selectionIdx = 0;
			return;
			}
		// TODO: add audio call
		
		// TODO: execute selection
		View &view = *View::getInstance();
		switch (selectionIdx) {
			case 0: view.load(VIEW_CONNECT_MAN); break;
			case 1: view.load(VIEW_CONTROLS); break;
			case 2: view.load(VIEW_SETTINGS); break;
			case 3: view.load(VIEW_EXIT); break;
			}
		}
	}


bool UiMain::isReleased() {
	return released;
	}


void UiMain::draw() {
	textureManager.drawTexturePart(textureBg, 0, 64, 0, 64, 960, 416);
	textureManager.drawTexturePart(textureBg, 0, 0, 0, 0, 960, 64);
	textureManager.drawTexturePart(textureBg, 0, 480, 0, 480, 960, 64);
	
	fontManager.setHalign(FONT_ALIGN_CENTER);
	fontManager.setValign(FONT_ALIGN_MIDDLE);
	fontManager.draw(FNT_GST_35, 480, 44, RGBA8(255, 255, 255, alpha), "PC Link");
	unsigned int i = 0, posy = 213;
	for (i = 0; i < selectionLabels.size(); i++) {
		if (i == selectionIdx)
			fontManager.draw(FNT_GST_30, 480, posy, RGBA8(selectionRB, 255, selectionRB, alpha), selectionLabels[i]);
		else
			fontManager.draw(FNT_GST_28, 480, posy, RGBA8(255, 255, 255, alpha), selectionLabels[i]);
		posy += 40;
		}
	if (whiteFadeAlpha)
		textureManager.drawRectangle(0, 0, 960, 544, RGBA8(255, 255, 255, whiteFadeAlpha));
	}


void UiMain::release() {
	fadeType = 0;
	}
