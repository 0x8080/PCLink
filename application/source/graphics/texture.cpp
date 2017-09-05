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
		
		
		--->> texture.cpp
		
*/

#include "texture.hh"

#include <debugnet.h>















Texture::Texture() {
	path = "";
	texture = NULL;
	used = 0;
	}


Texture::~Texture() {
	vita2d_free_texture(texture);
	}


vita2d_texture* Texture::create(std::string _path) {
	path = _path;
	texture = vita2d_load_PNG_file(path.c_str());
	used++;
	return texture;
	}
