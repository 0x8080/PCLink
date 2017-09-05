## This file is a quick tutorial on writing CMakeLists for targeting the Vita
cmake_minimum_required(VERSION 2.8)

## This includes the Vita toolchain, must go before project definition
# It is a convenience so you do not have to type 
# -DCMAKE_TOOLCHAIN_FILE=$VITASDK/share/vita.toolchain.cmake for cmake. It is 
# highly recommended that you include this block for all projects.
if(NOT DEFINED CMAKE_TOOLCHAIN_FILE)
  if(DEFINED ENV{VITASDK})
    set(CMAKE_TOOLCHAIN_FILE "$ENV{VITASDK}/share/vita.toolchain.cmake" CACHE PATH "toolchain file")
  else()
    message(FATAL_ERROR "Please define VITASDK to point to your SDK path!")
  endif()
endif()

## Define project parameters here
# Name of the project
project(PCLink)
# This line adds Vita helper macros, must go after project definition in order 
# to build Vita specific artifacts (self/vpk).
include("${VITASDK}/share/vita.cmake" REQUIRED)

## Configuration options for this app
# Display name (under bubble in LiveArea)
set(VITA_APP_NAME "PC Link")
# Unique ID must be exactly 9 characters. Recommended: XXXXYYYYY where X = 
# unique string of developer and Y = a unique number for this app
set(VITA_TITLEID  "VITAPCLNK")
# Optional version string to show in LiveArea's more info screen
set(VITA_VERSION  "00.00")

## Flags and includes for building
# Note that we make sure not to overwrite previous flags
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fpermissive -fno-lto -std=c++14")
# Optional. You can specify more param.sfo flags this way.
set(VITA_MKSFOEX_FLAGS "${VITA_MKSFOEX_FLAGS} -d PARENTAL_LEVEL=1")

# Add any additional include paths here
include_directories(
  ../common # This is for debugScreenPrintf(), you shouldn't need it in your projects
  source/core
  source/control
  source/graphics
  source/network
  source/ui
  source/util
  source/view
)

# Add any additional library paths here
# ${CMAKE_CURRENT_BINARY_DIR} lets you use any library currently being built
link_directories(
  ${CMAKE_CURRENT_BINARY_DIR}
)

## Build and link
# Add all the files needed to compile here
add_executable(pclink
  source/pclink.cpp
  source/control/gamepad.cpp
  source/control/keyboard.cpp
  source/control/touch.cpp
  source/core/config.cpp
  source/core/control-manager.cpp
  source/graphics/font-manager.cpp
  source/graphics/texture.cpp
  source/graphics/texture-manager.cpp
  source/network/connection.cpp
  source/network/network.cpp
  source/ui/ui-connect.cpp
  source/ui/ui-connect-add.cpp
  source/ui/ui-connect-manager.cpp
  source/ui/ui-main.cpp
  source/ui/ui-splash.cpp
  source/ui/ui-system-status.cpp
  source/util/utilities.cpp
  source/view/view.cpp
  
)

# Library to link to (drop the -l prefix). This will mostly be stubs.
target_link_libraries(pclink
  SceLibKernel_stub # this line is only for demonstration. It's not needed as                  # the most common stubs are automatically included.
  m
  c
  debugnet
  vita2d
  freetype
  png
  jpeg
  z
  VitaIni
  VitaAudio
  SceTouch_stub
  ScePower_stub
  SceCommonDialog_stub
  SceDisplay_stub
  SceGxm_stub
  SceCtrl_stub
 # ScePgf_stub
 # ScePvf_stub
  SceAppUtil_stub
  SceIme_stub
  SceNetCtl_stub
  SceNet_stub
  SceSysmodule_stub
)

## Create Vita files
vita_create_self(pclink.self pclink)
# The FILE directive lets you add additional files to the VPK, the syntax is 
# FILE src_path dst_path_in_vpk. In this case, we add the LiveArea paths.
vita_create_vpk(pclink.vpk ${VITA_TITLEID} pclink.self
  VERSION ${VITA_VERSION}
  NAME ${VITA_APP_NAME}
  FILE sce_sys/icon0.png sce_sys/icon0.png
  FILE sce_sys/livearea/contents/bg.png sce_sys/livearea/contents/bg.png
  FILE sce_sys/livearea/contents/startup.png sce_sys/livearea/contents/startup.png
  FILE sce_sys/livearea/contents/template.xml sce_sys/livearea/contents/template.xml
  FILE dta/res/fnt/gst.otf dta/res/fnt/gst.otf
  FILE dta/res/spr/img_connection_default_preview.png dta/res/spr/img_connection_default_preview.png
  FILE dta/res/spr/img_rep_bg1.png dta/res/spr/img_rep_bg1.png
  FILE dta/res/spr/img_rep_bg2.png dta/res/spr/img_rep_bg2.png
  FILE dta/res/spr/img_rep_btn_smallhl.png dta/res/spr/img_rep_btn_smallhl.png
  FILE dta/res/spr/img_rep_btn_small.png dta/res/spr/img_rep_btn_small.png
  FILE dta/res/spr/img_rep_checkboxhl.png dta/res/spr/img_rep_checkboxhl.png
  FILE dta/res/spr/img_rep_checkboxm.png dta/res/spr/img_rep_checkboxm.png
  FILE dta/res/spr/img_rep_checkbox.png	dta/res/spr/img_rep_checkbox.png
  FILE dta/res/spr/img_rep_icn_pc_large.png	dta/res/spr/img_rep_icn_pc_large.png
  FILE dta/res/spr/img_rep_icn_vita_large.png dta/res/spr/img_rep_icn_vita_large.png
  FILE dta/res/spr/img_rep_inputhl.png dta/res/spr/img_rep_inputhl.png
  FILE dta/res/spr/img_rep_input.png dta/res/spr/img_rep_input.png
  FILE dta/res/spr/img_rep_loadinga.png	dta/res/spr/img_rep_loadinga.png
  FILE dta/res/spr/img_rep_loadingb.png dta/res/spr/img_rep_loadingb.png
  FILE dta/res/spr/img_rep_panelhl.png dta/res/spr/img_rep_panelhl.png
  FILE dta/res/spr/img_rep_panel.png dta/res/spr/img_rep_panel.png
  FILE dta/res/spr/img_sysstatus_icon_circle.png dta/res/spr/img_sysstatus_icon_circle.png
  FILE dta/res/spr/img_sysstatus_icon_cross.png dta/res/spr/img_sysstatus_icon_cross.png
  FILE dta/res/spr/img_sysstatus_icon_glow.png dta/res/spr/img_sysstatus_icon_glow.png
  FILE dta/res/spr/img_sysstatus_icon_square.png dta/res/spr/img_sysstatus_icon_square.png
  FILE dta/res/spr/img_sysstatus_icon_triangle.png dta/res/spr/img_sysstatus_icon_triangle.png
  FILE dta/res/spr/img_uisplash_bg.png dta/res/spr/img_uisplash_bg.png
  FILE dta/res/spr/img_uisplash_icon.png dta/res/spr/img_uisplash_icon.png

)