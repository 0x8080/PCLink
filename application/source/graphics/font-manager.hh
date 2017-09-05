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
		
		
		--->> font-manager.hh
		
*/

#pragma once

#include <vita2d.h>
#include <string>




enum {
	FNT_GST_18,
	FNT_GST_24,
	FNT_GST_28,
	FNT_GST_30,
	FNT_GST_35
	//FNT_CCRALAN_
	
	};

enum {
	FONT_ALIGN_LEFT,
	FONT_ALIGN_CENTER,
	FONT_ALIGN_RIGHT,
	FONT_ALIGN_TOP,
	FONT_ALIGN_MIDDLE,
	FONT_ALIGN_BOTTOM
	};















class FontManager {
	public:
		static FontManager* getInstance();
		
		vita2d_font* getFont(unsigned int fntId);
		
		void setHalign(unsigned int _h);
		void setValign(unsigned int _v);
		
		void draw(unsigned int _fntId, int _x, int _y, unsigned int _color, std::string _str);
		
	private:
		static bool instanceFlag;
		static FontManager* fontManager;
		
		vita2d_font* fontList[5];
		unsigned int fontSizeList[5];
		
		unsigned int hAlign;
		unsigned int vAlign;
		
		FontManager();
		~FontManager();
		
	};
