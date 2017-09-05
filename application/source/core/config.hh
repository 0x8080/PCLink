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


		--->> config.hh

*/

#pragma once

#include <cstdint>
#include <string>















class Config {
	public:
		static Config* getInstance();

		// steam settings
		void setDisplayWidth(unsigned int _w);
		void setDisplayHeight(unsigned int _h);
		void setVideoState(bool _state);
		void setVideoWidth(unsigned int _w);
		void setVideoHeight(unsigned int _h);
		void setAudioState(bool _state);

		unsigned int getDisplayWidth();
		unsigned int getDisplayHeight();
		bool getVideoState();
		unsigned int getVideoWidth();
		unsigned int getVideoHeight();
		bool getAudioState();

		void flushConfig();



	private:
		static bool instanceFlag;
		static Config* config;

		Config();

		unsigned int displayWidth;
		unsigned int displayHeight;

		bool videoEnabled;
		unsigned int videoWidth;
		unsigned int videoHeight;

		bool audioEnabled;

		std::string sysOS;
		std::string sysCPU;
		std::string sysCORE;
		std::string sysMEM;
		std::string systemInformation;

		~Config();
	};
