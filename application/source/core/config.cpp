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


		--->> config.cpp

*/

#include "config.hh"

#include <debugnet.h>




bool Config::instanceFlag = false;
Config* Config::config = nullptr;

Config* Config::getInstance() {
	if (!instanceFlag) {
		config = new Config();
		instanceFlag = true;
		return config;
		}
	else
		return config;
	}















Config::Config() {
	flushConfig();
    debugNetPrintf(INFO, "Config : created\n");
	}


Config::~Config() {
	flushConfig();
	instanceFlag = false;
	}


void Config::setDisplayWidth(unsigned int _w) {
	displayWidth = _w;
	}


void Config::setDisplayHeight(unsigned int _h) {
	displayHeight = _h;
	}


void Config::setVideoState(bool _state) {
	videoEnabled = _state;
	}


void Config::setVideoWidth(unsigned int _w) {
	videoWidth = _w;
	}


void Config::setVideoHeight(unsigned int _h) {
	videoHeight = _h;
	}


void Config::setAudioState(bool _state) {
	audioEnabled = _state;
	}


unsigned int Config::getDisplayWidth() {
	return displayWidth;
	}


unsigned int Config::getDisplayHeight() {
	return displayHeight;
	}


bool Config::getVideoState() {
	return videoEnabled;
	}


unsigned int Config::getVideoWidth() {
	return videoWidth;
	}


unsigned int Config::getVideoHeight() {
	return videoHeight;
	}


bool Config::getAudioState() {
	return audioEnabled;
	}


void Config::flushConfig() {
	displayWidth = 0;
	displayHeight = 0;
	videoEnabled = false;
	videoWidth = 0;
	videoHeight = 0;
	audioEnabled = false;
	sysOS = "";
	sysCPU = "";
	sysCORE = "";
	sysMEM = "";
	systemInformation = "";
	}
