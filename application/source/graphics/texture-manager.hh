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
		
		
		--->> texture-manager.hh
		
*/

#pragma once

#include <vita2d.h>
#include <vector>
#include <string>

#include "texture.hh"















class TextureManager {
	public:
		static TextureManager* getInstance();
		
		vita2d_texture* getTexture(std::string path);
		void removeTexture(vita2d_texture* _texture);
		
		void drawStart();
		void drawEnd();
		
		void drawTexture(vita2d_texture* _texture, int _x, int _y);
		void drawTextureExt(vita2d_texture* _texture, int _x, int _y, float _scale, unsigned int _color);
		void drawTexturePart(vita2d_texture* _texture, int _x, int _y, int _px, int _py, int _pw, int _ph);
		void drawTextureCentered(vita2d_texture* _texture, int _x, int _y);
		
		void drawRectangle(int _x, int _y, int _w, int _h, unsigned int _colour);
		
	private:
		static bool instanceFlag;
		static TextureManager* textureManager;
		
		TextureManager();
		
		std::vector<Texture*> textureList;
		
		~TextureManager();
		
	};
