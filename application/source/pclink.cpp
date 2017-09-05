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
		
		
		--->> pclink.cpp
		
*/


#include <psp2/kernel/processmgr.h>
#include <psp2/appmgr.h>
#include <psp2/apputil.h>


#include <debugnet.h>

#include "util/utilities.hh"
#include "view/view.hh"




#define DEBUGNET_IP ""
#define DEBUGNET_PORT 18194

bool programRun = true;















int main() {
	sceAppUtilInit(&(SceAppUtilInitParam){}, &(SceAppUtilBootParam){});
    sceCommonDialogSetConfigParam(&(SceCommonDialogConfigParam){});
	
	debugNetInit(DEBUGNET_IP, DEBUGNET_PORT, DEBUG);
	debugNetPrintf(INFO, "\n\n\n\n>>>>>-----------------------------------<<<<<\n");
	debugNetPrintf(INFO, ">>>>> PC Link - Remote desktop streamer <<<<<\n");
	debugNetPrintf(INFO, ">>>>>         Playstation Vita          <<<<<\n");
	debugNetPrintf(INFO, ">>>>>        [HENkaku Homebrew]         <<<<<\n");
	debugNetPrintf(INFO, ">>>>>-----------------------------------<<<<<\n\n\n\n");
	
	Utilities &util = *Utilities::getInstance();
	util.directoryCreate(PATH_DIR_DATA_ROOT);
	
	View &view = *View::getInstance();
	Gamepad &gamepad = *Gamepad::getInstance();
	Touch &touch = *Touch::getInstance();
	
	
	
	
	
	
	view.load(VIEW_SPLASH);
	while (programRun) {
		gamepad.update(); // TODO: no need to update every cycle
		touch.update(); // TODO: no need to update every cycle
		
		view.draw();
		
		}
	
	
	
	return sceKernelExitProcess(0);
	}
