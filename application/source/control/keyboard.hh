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
		
		
		--->> keyboard.hh
	
*/

#pragma once

#include <psp2/ime_dialog.h>
#include <psp2/common_dialog.h>
#include <psp2/types.h>

#include <string>
#include <cstring>















class Keyboard {
	public:
		static Keyboard* getInstance();
		
		bool init(unsigned int _maxLen, std::string _initText, std::string* _dest);
		bool isActive();
		void update();
		
	private:
		Keyboard();
		
		static bool instanceFlag;
		static Keyboard* keyboard;
		
		bool active;
		
		SceImeDialogParam imeParam;
		//SceCommonDialogParam commonParam;
		
		std::string* returnStr;
		
		uint16_t titleUi16[SCE_IME_DIALOG_MAX_TITLE_LENGTH];
		uint16_t initialTextUi16[SCE_IME_DIALOG_MAX_TEXT_LENGTH];
		uint16_t textBufferUi16[SCE_IME_DIALOG_MAX_TEXT_LENGTH + 1];
		uint8_t textBufferUi8[SCE_IME_DIALOG_MAX_TEXT_LENGTH + 1];
		
		void toUtf8(uint16_t* src, uint8_t* dst);
		void toUtf16(uint8_t* src, uint16_t* dst);
		
		~Keyboard();
		
	};
