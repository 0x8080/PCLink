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
		
		
		This Class is based on code provided by 'Freakler'.
		--->> keyboard.cpp
	
*/

#include "keyboard.hh"

#include <psp2/appmgr.h>
#include <psp2/apputil.h>
#include <psp2/message_dialog.h>
#include <psp2/types.h>


#include <debugnet.h>





bool Keyboard::instanceFlag = false;
Keyboard* Keyboard::keyboard = NULL;

Keyboard* Keyboard::getInstance() {
    if (!instanceFlag) {
        keyboard = new Keyboard();
        instanceFlag = true;
        return keyboard;
		}
    else
        return keyboard;
	}















Keyboard::Keyboard() {
	active = false;
	sceImeDialogParamInit(&imeParam);
	//imeParaminputMethod = SCE_IME_TYPE_NUMBER;
	imeParam.supportedLanguages = SCE_IME_LANGUAGE_ENGLISH;
	imeParam.languagesForced = SCE_TRUE;
	imeParam.type = SCE_IME_TYPE_EXTENDED_NUMBER;
	imeParam.option = (SCE_IME_OPTION_NO_AUTO_CAPITALIZATION | SCE_IME_OPTION_NO_ASSISTANCE);
	//imeParam.dialogMode = SCE_IME_DIALOG_DIALOG_MODE_WITH_CANCEL;
	//imeParam.textBoxMode = SCE_IME_DIALOG_TEXTBOX_MODE_DEFAULT;
	imeParam.enterLabel = SCE_IME_ENTER_LABEL_DEFAULT;
	}


Keyboard::~Keyboard() {
	instanceFlag = false;
	}


bool Keyboard::init(unsigned int _maxLen, std::string _initText, std::string* _dest) {
	char* title = "title";
	toUtf16((char*)title, titleUi16);
	imeParam.title = titleUi16;
	char* initialText = new char[_initText.length() + 1];
	strcpy(initialText, _initText.c_str());
	toUtf16((uint8_t *)initialText, initialTextUi16);
	
	imeParam.maxTextLength = _maxLen;
	imeParam.initialText = initialTextUi16;
	imeParam.inputTextBuffer = textBufferUi16;
	returnStr = _dest;
	
	int ret = sceImeDialogInit(&imeParam);
	if (ret < 0)
		debugNetPrintf(INFO, "sceImeDialogInit failed ret = 0x%x\n", ret);
	active = true;
	delete [] initialText;
	return true;
	}


bool Keyboard::isActive() {
	return active;
	}


void Keyboard::update() {
	if (active) {
		SceCommonDialogStatus imeStatus = sceImeDialogGetStatus();
		if (imeStatus == SCE_COMMON_DIALOG_STATUS_FINISHED) {
			active = false;
			sceImeDialogTerm();
			return;
			}
		SceImeDialogResult result;
		memset(&result, 0, sizeof(SceImeDialogResult));
		sceImeDialogGetResult(&result);
		toUtf8(textBufferUi16, textBufferUi8);
		returnStr->assign((char*)textBufferUi8);
		}
	}


void Keyboard::toUtf8(uint16_t* src, uint8_t* dst) {
	int i;
	for (i = 0; src[i]; i++) {
		if ((src[i] & 0xFF80) == 0)
			*(dst++) = src[i] & 0xFF;
		else if((src[i] & 0xF800) == 0) {
			*(dst++) = ((src[i] >> 6) & 0xFF) | 0xC0;
			*(dst++) = (src[i] & 0x3F) | 0x80;
			}
		else if((src[i] & 0xFC00) == 0xD800 && (src[i + 1] & 0xFC00) == 0xDC00) {
			*(dst++) = (((src[i] + 64) >> 8) & 0x3) | 0xF0;
			*(dst++) = (((src[i] >> 2) + 16) & 0x3F) | 0x80;
			*(dst++) = ((src[i] >> 4) & 0x30) | 0x80 | ((src[i + 1] << 2) & 0xF);
			*(dst++) = (src[i + 1] & 0x3F) | 0x80;
			i += 1;
			}
		else {
			*(dst++) = ((src[i] >> 12) & 0xF) | 0xE0;
			*(dst++) = ((src[i] >> 6) & 0x3F) | 0x80;
			*(dst++) = (src[i] & 0x3F) | 0x80;
			}
		}
	*dst = '\0';
	}


void Keyboard::toUtf16(uint8_t* src, uint16_t* dst) {
	int i;
	for (i = 0; src[i];) {
		if ((src[i] & 0xE0) == 0xE0) {
			*(dst++) = ((src[i] & 0x0F) << 12) | ((src[i + 1] & 0x3F) << 6) | (src[i + 2] & 0x3F);
			i += 3;
			}
		else if ((src[i] & 0xC0) == 0xC0) {
			*(dst++) = ((src[i] & 0x1F) << 6) | (src[i + 1] & 0x3F);
			i += 2;
			}
		else {
			*(dst++) = src[i];
			i += 1;
			}
		}
	*dst = '\0';
	}
