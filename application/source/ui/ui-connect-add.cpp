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
		
		
		--->> ui-connect-add.cpp
		
*/

#include "ui-connect-add.hh"

#include <debugnet.h>

#include "../view/view.hh"
#include "ui-connect-manager.hh"
#include "../util/utilities.hh"
extern "C"
{
#include <vitaIni.h>
}

#define ALPHA_SPEED 34




bool UiConnectAdd::instanceFlag = false;
UiConnectAdd* UiConnectAdd::uiConnectAdd = NULL;

UiConnectAdd* UiConnectAdd::getInstance() {
    if (!instanceFlag) {
        uiConnectAdd = new UiConnectAdd();
        instanceFlag = true;
        return uiConnectAdd;
		}
    else
        return uiConnectAdd;
	}















UiConnectAdd::UiConnectAdd() {
	alpha = 0;
	fadeType = 0;
	active = false;
	released = true;
	btnStateCancel = false;
	btnStateOk = false;
	checkBoxState = false;
	input = "";
	editIdx = -1;
	}


UiConnectAdd::~UiConnectAdd() {
	instanceFlag = false;
	}


bool UiConnectAdd::init() {
	UiConnectManager &connectManager = *UiConnectManager::getInstance();
	editIdx = connectManager.getEditIdx();
	connectManager.setEditIdx(-1);
	textureBg = textureManager.getTexture("img_uimain_bg.png");
	textureBtn[0] = textureManager.getTexture("img_rep_btn_small.png");
	textureBtn[1] = textureManager.getTexture("img_rep_btn_smallhl.png");
	textureInput[0] = textureManager.getTexture("img_rep_input.png");
	textureInput[1] = textureManager.getTexture("img_rep_inputhl.png");
	textureCheckBox[0] = textureManager.getTexture("img_rep_checkbox.png");
	textureCheckBox[1] = textureManager.getTexture("img_rep_checkboxhl.png");
	textureCheckBox[2] = textureManager.getTexture("img_rep_checkboxm.png");
	
	active = true;
	released = false;
	fadeType = 1;
	if (editIdx >= 0) {
		char ipStr[32];
		char sectStr[64];
		sprintf(sectStr, "CONNECTION%d\0", (editIdx + 1));
		iniOpen(PATH_FILE_CONNECTIONS);
		iniReadString(ipStr, sectStr, "ip", "0.0.0.0");
		input.assign(ipStr);
		}
	
	return true;
	}


void UiConnectAdd::update() {
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
			released = true;
			}
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
		if (selectionIdx == 1)
			checkBoxState = !checkBoxState;
		}
	else if (gamepad.checkPressed(SCE_CTRL_CIRCLE)) {
		selectionIdx = 2;
		}
	
	if (gamepad.checkReleased(SCE_CTRL_CIRCLE)) {
		selectionIdx = -1;
		View &view = *View::getInstance();
		view.load(VIEW_CONNECT_MAN);
		}
	else if (gamepad.checkPressed(SCE_CTRL_CROSS)) {
		int sidx = selectionIdx;
		selectionIdx = -1;
		// TODO: add audio call
		
		// TODO: execute selection
		switch (sidx) {
			case 0:  break;
			case 1:  break;
			case 2: {
					View &view = *View::getInstance();
					view.load(VIEW_CONNECT_MAN);
					}
					break;
			case 3: save();
					break;
			}
		}
	
	// touch
	if (touch.checkPressed()) {
		if (touch.inRectangle(434, 132, 916, 200)) {
			// input
			
			}
		else if (touch.inRectangle(437, 222, 490, 275)) {
			// checkbox
			checkBoxState = !checkBoxState;
			}
		else if (touch.inRectangle(0, 482, 175, 544)) {
			// cancel
			btnStateCancel = true;
			}
		else if (touch.inRectangle(785, 482, 960, 544)) {
			// ok
			btnStateOk = true;
			}
		}
	
	if (touch.checkReleased()) {
		if (touch.inRectangle(434, 132, 916, 200)) {
			// input
			if (!keyboard.isActive())
				keyboard.init(15, "0.0.0.0", &input);
			}
		else if (touch.inRectangle(0, 482, 175, 544)) {
			// cancel
			View &view = *View::getInstance();
			view.load(VIEW_CONNECT_MAN);
			}
		else if (touch.inRectangle(785, 482, 960, 544)) {
			// ok
			save();
			}
		btnStateCancel = false;
		btnStateOk = false;
		}
	}


void UiConnectAdd::save() {
	View &view = *View::getInstance();
	if (input != "") {
		iniOpen(PATH_FILE_CONNECTIONS);
		if (editIdx >= 0) {
			char ipStr[32];
			char sectStr[64];
			sprintf(ipStr, "%s", input.c_str());
			sprintf(sectStr, "CONNECTION%d\0", (editIdx + 1));
			iniWriteString(sectStr, "ip", ipStr);
			if (checkBoxState) {
				// tODO: set as default
				
				}
			}
		else {
			int cc = (iniReadReal("CONNECTIONS", "connectionCount", 0) + 1);
			iniWriteReal("CONNECTIONS", "connectionCount", cc);
			char ipStr[32];
			char sectStr[64];
			sprintf(ipStr, "%s", input.c_str());
			sprintf(sectStr, "CONNECTION%d\0", cc);
			iniWriteString(sectStr, "ip", ipStr);
			if (checkBoxState) {
				// tODO: set as default
				
				}
			}
		view.load(VIEW_CONNECT_MAN);
		}
	else {
		// TODO: dialog
		
		}
	}


void UiConnectAdd::draw() {
	// allow draw over ime dialog
	// TODO: messy, redo
	keyboard.update();
	vita2d_end_drawing();
	vita2d_common_dialog_update();
	vita2d_start_drawing();
	//
	textureManager.drawTexturePart(textureBg, 0, 64, 0, 64, 960, 416);
	textureManager.drawTexturePart(textureBg, 0, 0, 0, 0, 960, 64);
	textureManager.drawTexturePart(textureBg, 0, 480, 0, 480, 960, 64);
	
	fontManager.setHalign(FONT_ALIGN_CENTER);
	fontManager.setValign(FONT_ALIGN_MIDDLE);
	fontManager.draw(FNT_GST_35, 480, 44, RGBA8(255, 255, 255, alpha), "Add Desktop");
	
	fontManager.setHalign(FONT_ALIGN_RIGHT);
	fontManager.setValign(FONT_ALIGN_TOP);
	fontManager.draw(FNT_GST_30, 398, 175, RGBA8(255, 255, 255, alpha), "IP Address");
	fontManager.setHalign(FONT_ALIGN_LEFT);
	fontManager.draw(FNT_GST_30, 507, 260, RGBA8(255, 255, 255, alpha), "Set as Default");
	fontManager.draw(FNT_GST_24, 65, 350, RGBA8(255, 255, 255, alpha), "Enter the IP address of the Desktop you would like to connect to.");
	fontManager.draw(FNT_GST_24, 65, 380, RGBA8(255, 255, 255, alpha), "If you are connecting over the Internet, make sure to forward port");
	fontManager.draw(FNT_GST_24, 65, 410, RGBA8(255, 255, 255, alpha), "13123 to this address on your router.");
	
	textureManager.drawTextureExt(textureInput[0], 434, 132, 1.0f, RGBA8(255, 255, 255, alpha));
	if (selectionIdx == 0)
		textureManager.drawTextureExt(textureInput[1], 434, 132, 1.0f, RGBA8(255, 255, 255, alpha));
	fontManager.draw(FNT_GST_30, 455, 176, RGBA8(255, 255, 255, alpha), input.c_str());
	
	textureManager.drawTextureExt(textureCheckBox[0], 440, 216, 1.0f, RGBA8(255, 255, 255, alpha));
	if (selectionIdx == 1)
		textureManager.drawTextureExt(textureCheckBox[1], 438, 222, 1.0f, RGBA8(255, 255, 255, alpha));
	if (checkBoxState)
		textureManager.drawTextureExt(textureCheckBox[2], 440, 216, 1.0f, RGBA8(255, 255, 255, alpha));
	
	if (selectionIdx == 2 || btnStateCancel)
		textureManager.drawTextureExt(textureBtn[1], 12, 490, 1.0f, RGBA8(255, 255, 255, alpha));
	else
		textureManager.drawTextureExt(textureBtn[0], 12, 490, 1.0f, RGBA8(255, 255, 255, alpha));
	if (selectionIdx == 3 || btnStateOk)
		textureManager.drawTextureExt(textureBtn[1], 801, 490, 1.0f, RGBA8(255, 255, 255, alpha));
	else
		textureManager.drawTextureExt(textureBtn[0], 801, 490, 1.0f, RGBA8(255, 255, 255, alpha));
	
	fontManager.setHalign(FONT_ALIGN_CENTER);
	fontManager.draw(FNT_GST_24, 86, 524, RGBA8(255, 255, 255, alpha), "Cancel");
	fontManager.draw(FNT_GST_24, 879, 524, RGBA8(255, 255, 255, alpha), "Ok");
	}


bool UiConnectAdd::isReleased() {
	return released;
	}


void UiConnectAdd::release() {
	fadeType = 0;
	}
