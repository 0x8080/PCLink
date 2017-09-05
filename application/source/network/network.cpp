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
		
		
		--->> network.cpp
		
*/

#include "network.hh"
#include <psp2/kernel/threadmgr.h>
#include <debugnet.h>
#include <stdlib.h>
#include <string.h>
#include <psp2/sysmodule.h>
#include <psp2/net/net.h>
#include <psp2/net/netctl.h>



bool Network::instanceFlag = false;
Network* Network::network = NULL;

Network* Network::getInstance() {
    if (!instanceFlag) {
        network = new Network();
        instanceFlag = true;
        return network;
		}
    else
        return network;
	}

#define NETWORK_INIT_SIZE 100 * 1024
#define NETWORK_BUFFER_IN_SIZE 65507
#define NETWORK_BUFFER_OUT_SIZE 256
#define NETWORK_SERVER_PORT 13552













Network::Network() {
	initialized = false;
	networkInfo = "";
	bytesRecieved = 0;
	}


Network::~Network() {
	
	
	
	
	instanceFlag = false;
	}


bool Network::init(std::string ip) {
	if (initialized)
		return true;
	int ret = sceSysmoduleLoadModule(SCE_SYSMODULE_NET);
	if (ret != SCE_SYSMODULE_LOADED) {
		debugNetPrintf(ERROR, "Network::init() : sceSysmoduleLoadModule : ret 0x%x\n");
		networkInfo = "Network Init Error";
		return false;
		}
	SceNetInitParam initParam = {0};
    if (sceNetShowNetstat() == SCE_NET_ERROR_ENOTINIT) {
        initParam.memory = calloc(NETWORK_INIT_SIZE, 1);
        initParam.size = NETWORK_INIT_SIZE;
        ret = sceNetInit(&initParam);
		if (ret < 0) {
			debugNetPrintf(ERROR, "Network::init() : sceNetInit : ret 0x%x\n");
			networkInfo = "Network Init Error";
			return false;
			}
		}
	else {
		debugNetPrintf(ERROR, "Network::init() : SCE_NET_ERROR_ENOTINIT\n");
		networkInfo = "Network Init Error";
        return false;
		}
	
    ret = sceNetCtlInit();
	if (ret < 0) {
		debugNetPrintf(ERROR, "Network::init() : sceNetCtlInit : ret 0x%x\n");
		networkInfo = "Network Init Error";
		return false;
		}
	SceNetCtlInfo netCtlInfo;
    sceNetCtlInetGetInfo(SCE_NETCTL_INFO_GET_IP_ADDRESS, &netCtlInfo);
	static SceNetInAddr netInAddress;
    sceNetInetPton(SCE_NET_AF_INET, netCtlInfo.ip_address, &netInAddress);
    socket = sceNetSocket("PcLink_Net", SCE_NET_AF_INET, SCE_NET_SOCK_DGRAM, SCE_NET_IPPROTO_UDP);
	networkInfo = "Connecting";
	struct SceNetSockaddrIn netSockAddress;
    memset(&netSockAddress, 0, sizeof(netSockAddress));
    netSockAddress.sin_family = SCE_NET_AF_INET;
    netSockAddress.sin_port = sceNetHtons(NETWORK_SERVER_PORT);
    sceNetInetPton(SCE_NET_AF_INET, ip.c_str(), &netSockAddress.sin_addr);
    sceNetConnect(socket, (struct SceNetSockaddr*)&netSockAddress, sizeof(netSockAddress));
	
	bufferIn = (unsigned char*) malloc(NETWORK_BUFFER_IN_SIZE);
	bufferOut = (unsigned char*) malloc(NETWORK_BUFFER_OUT_SIZE);
	
	//decoderInit();
	
	return (initialized = true);
	}


bool Network::isInitialized() {
	return initialized;
	}


std::string Network::getNetworkInfo() {
	return networkInfo;
	}
	

void Network::connect() {
	if (!initialized) {
		debugNetPrintf(ERROR, "Network::connect() : network was not initialized\n");
		networkInfo = "Network Connection Error";
		return;
		}
	networkInfo = "Requesting Link";
	// TODO: request packet
	
	sceNetSend(socket, bufferOut, strlen(bufferOut), 0);
	bytesRecieved = sceNetRecv(socket, bufferIn, NETWORK_BUFFER_IN_SIZE, 0);
	sceKernelDelayThread(2000000); // Delay 2 seconds for animation
	
	
	
	
	
	}
