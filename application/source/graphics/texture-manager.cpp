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
		
		
		--->> texture-manager.cpp
		
*/

#include "texture-manager.hh"

#include <debugnet.h>

#include "../util/utilities.hh"









bool TextureManager::instanceFlag = false;
TextureManager* TextureManager::textureManager = NULL;

TextureManager* TextureManager::getInstance() {
    if (!instanceFlag) {
        textureManager = new TextureManager();
        instanceFlag = true;
        return textureManager;
		}
    else
        return textureManager;
	}















TextureManager::TextureManager() {
	vita2d_init();
	vita2d_set_clear_color(RGBA8(0, 0, 0, 255));
	}


TextureManager::~TextureManager() {
	// TODO: release texture list
	
	
	
	instanceFlag = false;
	}


vita2d_texture* TextureManager::getTexture(std::string path) {
	std::string fullPath = "app0:dta/res/spr/" + path;
	unsigned int i;
	for (i = 0; i < textureList.size(); i++) {
		if (textureList[i]->path.compare(fullPath) == 0) {
			textureList[i]->used++;
			return textureList[i]->texture;
			}
		}
	Utilities &util = *Utilities::getInstance();
	if (!util.fileExists(fullPath.c_str())) {
		debugNetPrintf(ERROR, "TextureManager::getTexture() : COULD NOT FIND %s\n", fullPath.c_str());
		return NULL;
		}
	Texture* tex = new Texture();
	textureList.push_back(tex);
	return tex->create(fullPath);
	}


void TextureManager::removeTexture(vita2d_texture* _texture) {
	unsigned int i;
	for (i = 0; i < textureList.size(); i++) {
		if (textureList[i]->texture == _texture) {
			textureList[i]->used--;
			if (textureList[i]->used == 0) {
				delete textureList[i];
				textureList.erase(textureList.begin() + i);
				}
			break;
			}
		}
	
	}


void TextureManager::drawStart() {
	vita2d_start_drawing();
	vita2d_clear_screen();
	}


void TextureManager::drawEnd() {
	vita2d_end_drawing();
	vita2d_wait_rendering_done();
	//vita2d_common_dialog_update();
	vita2d_swap_buffers();
	}


void TextureManager::drawTexture(vita2d_texture* _texture, int _x, int _y) {
	vita2d_draw_texture(_texture, _x, _y);
	}


void TextureManager::drawTextureExt(vita2d_texture* _texture, int _x, int _y, float _scale, unsigned int _color) {
	vita2d_draw_texture_tint_scale(_texture, _x, _y, _scale, _scale, _color);
	}


void TextureManager::drawTexturePart(vita2d_texture* _texture, int _x, int _y, int _px, int _py, int _pw, int _ph) {
	vita2d_draw_texture_part(_texture, _x, _y, _px, _py, _pw, _ph);
	}


void TextureManager::drawTextureCentered(vita2d_texture* _texture, int _x, int _y) {
	vita2d_draw_texture(_texture, _x - (vita2d_texture_get_width(_texture) / 2), _y - (vita2d_texture_get_height(_texture) / 2));
	}


void TextureManager::drawRectangle(int _x, int _y, int _w, int _h, unsigned int _colour) {
	vita2d_draw_rectangle(_x, _y, _w, _h, _colour);
	}
