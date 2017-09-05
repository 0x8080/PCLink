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
		
		
		--->> font-manager.cpp
		
*/

#include "font-manager.hh"




bool FontManager::instanceFlag = false;
FontManager* FontManager::fontManager = NULL;

FontManager* FontManager::getInstance() {
    if (!instanceFlag) {
        fontManager = new FontManager();
        instanceFlag = true;
        return fontManager;
		}
    else
        return fontManager;
	}















FontManager::FontManager() {
	hAlign = FONT_ALIGN_LEFT;
	vAlign = FONT_ALIGN_BOTTOM;
	fontSizeList[FNT_GST_18] = 18;
	fontList[FNT_GST_18] = vita2d_load_font_file("app0:dta/res/fnt/gst.otf");
	fontSizeList[FNT_GST_24] = 24;
	fontList[FNT_GST_24] = vita2d_load_font_file("app0:dta/res/fnt/gst.otf");
	fontSizeList[FNT_GST_28] = 28;
	fontList[FNT_GST_28] = vita2d_load_font_file("app0:dta/res/fnt/gst.otf");
	fontSizeList[FNT_GST_30] = 30;
	fontList[FNT_GST_30] = vita2d_load_font_file("app0:dta/res/fnt/gst.otf");
	fontSizeList[FNT_GST_35] = 35;
	fontList[FNT_GST_35] = vita2d_load_font_file("app0:dta/res/fnt/gst.otf");
	}


FontManager::~FontManager() {
	// TODO: release font list
	
	
	
	instanceFlag = false;
	}


vita2d_font* FontManager::getFont(unsigned int fntId) {
	return fontList[fntId];
	}


void FontManager::setHalign(unsigned int _h) {
	hAlign = _h;
	}


void FontManager::setValign(unsigned int _v) {
	vAlign = _v;
	}


void FontManager::draw(unsigned int _fntId, int _x, int _y, unsigned int _color, std::string _str) {
	// TODO: re-write this ridiculous function. :-)
	int xOffset = _x;
	int yOffset = _y;
	switch (hAlign) {
		case FONT_ALIGN_LEFT:	break;
		case FONT_ALIGN_CENTER:	xOffset -= (vita2d_font_text_width(fontList[_fntId], fontSizeList[_fntId], _str.c_str()) / 2); break;
		case FONT_ALIGN_RIGHT:	xOffset -= vita2d_font_text_width(fontList[_fntId], fontSizeList[_fntId], _str.c_str()); break;
		}
	switch (hAlign) {
		case FONT_ALIGN_BOTTOM:	break;
		case FONT_ALIGN_TOP:	yOffset += vita2d_font_text_height(fontList[_fntId], fontSizeList[_fntId], _str.c_str()); break;
		case FONT_ALIGN_MIDDLE:	yOffset += (vita2d_font_text_height(fontList[_fntId], fontSizeList[_fntId], _str.c_str()) / 2); break;
		}
	vita2d_font_draw_text(fontList[_fntId], xOffset, yOffset, _color, fontSizeList[_fntId], _str.c_str());
	}


// TODO: add drawf()
