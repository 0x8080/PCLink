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
		
		
		--->> ui-splash.cpp
		
*/

#include "ui-splash.hh"

#include <debugnet.h>

#include "../util/utilities.hh"
#include "../view/view.hh"

#define SPLASH_INTERVAL 200
#define ANIMATION_SPEED 34
#define FADE_SPEED 34




bool UiSplash::instanceFlag = false;
UiSplash* UiSplash::uiSplash = NULL;

UiSplash* UiSplash::getInstance() {
    if (!instanceFlag) {
        uiSplash = new UiSplash();
        instanceFlag = true;
        return uiSplash;
		}
    else
        return uiSplash;
	}















UiSplash::UiSplash() {
	textureBg = textureManager.getTexture("img_uisplash_bg.png");
	textureIcon = textureManager.getTexture("img_uisplash_icon.png");
	timer = 0;
	active = true;
	released = false;
	}


UiSplash::~UiSplash() {
	instanceFlag = false;
	}


void UiSplash::update() {
	if (active) {
		if (timer++ > SPLASH_INTERVAL)
			active = false;
		}
	else {
		if (alpha < (255 - FADE_SPEED))
			alpha += FADE_SPEED;
		else {
			alpha = 255;
			View &view = *View::getInstance();
			view.load(VIEW_MAIN);
			}
		}
	}


void UiSplash::draw() {
	if (!released) {
		textureManager.drawTexture(textureBg, 0, 0);
		textureManager.drawTexture(textureIcon, 381, 206);
		fontManager.setHalign(FONT_ALIGN_RIGHT);
		fontManager.draw(FNT_GST_24, 940, 524, RGBA8(255, 255, 255, 255), VERSION_STRING);
		}
	textureManager.drawRectangle(0, 0, 960, 544, RGBA8(255, 255, 255, alpha));
	}


void UiSplash::release() {
	textureManager.removeTexture(textureBg);
	textureManager.removeTexture(textureIcon);
	released = true;
	}