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
		
		
		--->> ui-system-status.cpp
		
*/

#include "ui-system-status.hh"

#include <cstddef>




bool UiSystemStatus::instanceFlag = false;
UiSystemStatus* UiSystemStatus::uiSystemStatus = NULL;

UiSystemStatus* UiSystemStatus::getInstance() {
    if (!instanceFlag) {
        uiSystemStatus = new UiSystemStatus();
        instanceFlag = true;
        return uiSystemStatus;
		}
    else
        return uiSystemStatus;
	}















UiSystemStatus::UiSystemStatus() {
	
	}


UiSystemStatus::~UiSystemStatus() {
	
	
	
	instanceFlag = false;
	}


