cmake_minimum_required(VERSION 2.8)

# VitaSDK defines
if( NOT DEFINED CMAKE_TOOLCHAIN_FILE )
  if( DEFINED ENV{VITASDK} )
    set(CMAKE_TOOLCHAIN_FILE "$ENV{VITASDK}/share/vita.toolchain.cmake" CACHE PATH "toolchain file")
  else()
    message(FATAL_ERROR "Please define VITASDK to point to your SDK path!")
  endif()
endif()

# Project start
set(VITA_APPNAME  AnotherWorld)
set(VITA_LAUNCHER launcher)
set(VITA_TITLEID  "RAWGLVITA")

project(${VITA_APPNAME})
include("${VITASDK}/share/vita.cmake" REQUIRED)

# Flags and includes
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DBYPASS_PROTECTION -fno-exceptions -g -O3")

include_directories(
  ${VITASDK}/arm-vita-eabi/include/SDL2
)

link_directories(
  ${CMAKE_CURRENT_BINARY_DIR}
)

# Builds
add_executable(${VITA_APPNAME}
  aifcplayer.cpp
  bitmap.cpp
  engine.cpp
  file.cpp
  graphics_soft.cpp
  main.cpp
  mixer.cpp
  pak.cpp
  resource_3do.cpp
  resource.cpp
  resource_nth.cpp
  resource_win31.cpp
  screenshot.cpp
  scaler.cpp
  script.cpp
  sfxplayer.cpp
  staticres.cpp
  systemstub_sdl.cpp
  unpack.cpp
  util.cpp
  video.cpp
)

target_link_libraries(${VITA_APPNAME}
  SDL2_mixer
  SDL2
  vita2d
  vorbisfile
  vorbis
  ogg
  mpg123
  mikmod
  modplug
  FLAC
  z
  SceAppMgr_stub
  SceAppUtil_stub
  SceAudio_stub
  SceCommonDialog_stub
  SceCtrl_stub
  SceDisplay_stub
  SceGxm_stub
  SceHid_stub
  SceSysmodule_stub
  SceTouch_stub
)

add_executable(${VITA_LAUNCHER}
  launcher.cpp
)

target_link_libraries(${VITA_LAUNCHER}
  imgui
  vitaGL
  vitashark
  mathneon
  SceAppMgr_stub
  SceCommonDialog_stub
  SceCtrl_stub
  SceDisplay_stub
  SceGxm_stub
  SceShaccCg_stub
  SceTouch_stub
)

# Create Vita artifacts
vita_create_self(rawgl.bin ${VITA_APPNAME}  UNSAFE)
vita_create_self(eboot.bin ${VITA_LAUNCHER} UNSAFE)
vita_create_vpk(${VITA_APPNAME}.vpk ${VITA_TITLEID} eboot.bin
  NAME ${VITA_APPNAME}
  FILE ${CMAKE_CURRENT_BINARY_DIR}/rawgl.bin rawgl.bin
  FILE res/icon0.png sce_sys/icon0.png
  FILE res/bg.png sce_sys/livearea/contents/bg.png
  FILE res/startup.png sce_sys/livearea/contents/startup.png
  FILE res/template.xml sce_sys/livearea/contents/template.xml
)
