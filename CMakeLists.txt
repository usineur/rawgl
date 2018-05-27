cmake_minimum_required(VERSION 3.0)

if( NOT DEFINED CMAKE_TOOLCHAIN_FILE )
  set(CMAKE_TOOLCHAIN_FILE "Toolchain.cmake" CACHE PATH "Toolchain file")
endif()

project(rawgl)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D__SWITCH__ -DBERMUDA_POSIX -DBERMUDA_VORBIS -DBERMUDA_ZLIB -O3 -g")

include_directories(
  ${DEVKITPRO}/portlibs/switch/include/SDL2
)

link_directories(
  ${DEVKITPRO}/libnx/lib
  ${DEVKITPRO}/portlibs/switch/lib
)

add_executable(${CMAKE_PROJECT_NAME}.elf
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
  resource_mac.cpp
  resource_nth.cpp
  resource_win31.cpp
  script.cpp
  sfxplayer.cpp
  staticres.cpp
  systemstub_sdl.cpp
  unpack.cpp
  util.cpp
  video.cpp
)

target_link_libraries(${CMAKE_PROJECT_NAME}.elf
  SDL2_mixer
  SDL2
  mpg123
  vorbisfile
  vorbis
  ogg
  modplug
  mikmod
  z
  nx
  m
 -specs=${DEVKITPRO}/libnx/switch.specs
)

add_custom_target(${CMAKE_PROJECT_NAME}.nro
  DEPENDS ${CMAKE_PROJECT_NAME}.elf
  COMMAND nacptool --create "Another World" "usineur" "1.0" ${CMAKE_PROJECT_NAME}.nacp
  COMMAND elf2nro ${CMAKE_PROJECT_NAME}.elf ${CMAKE_PROJECT_NAME}.nro --icon=${CMAKE_SOURCE_DIR}/res/icon.jpg --nacp=${CMAKE_PROJECT_NAME}.nacp
)
