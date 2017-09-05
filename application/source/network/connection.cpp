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
		
		
		--->> connection.cpp
		
*/

#include "connection.hh"

#include <debugnet.h>

#include "../util/utilities.hh"

#define ALPHA_SPEED 34















Connection::Connection(std::string _ipStr) : ipStr(_ipStr) {
	alpha = 0;
	highlight = false;
	editHighlight = false;
	Utilities &utilities = *Utilities::getInstance();
	std::string targetFile = ipStr + ".png";
	if (utilities.fileExists(targetFile.c_str())) {
		texturePreview = textureManager.getTexture(targetFile);
		return;
		}
	// default preview
	texturePreview = textureManager.getTexture("img_connection_default_preview.png");
	}


Connection::~Connection() {
	textureManager.removeTexture(texturePreview);
	}


void Connection::setHighlight(bool state) {
	highlight = state;
	}


void Connection::setEditHighlight(bool state) {
	editHighlight = state;
	}


void Connection::draw(int _x, int _y) {
	if (alpha < (255 - ALPHA_SPEED))
		alpha += ALPHA_SPEED;
	else
		alpha = 255;
	textureManager.drawRectangle(_x, _y, 222, 126, RGBA8(255, 255, 255, alpha));
	textureManager.drawTexture(texturePreview, _x + 1, _y + 1);
	
	if (editHighlight)
		textureManager.drawRectangle(_x + 158, _y + 89, 63, 36, RGBA8(255, 255, 255, 119));
	else if (highlight)
		textureManager.drawRectangle(_x, _y, 222, 126, RGBA8(255, 255, 255, 119));
	fontManager.setHalign(FONT_ALIGN_LEFT);
	fontManager.draw(FNT_GST_18, _x + 6, _y + 114, RGBA8(255, 255, 255, alpha), ipStr.c_str());
	}
