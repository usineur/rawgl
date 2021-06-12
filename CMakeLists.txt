cmake_minimum_required(VERSION 3.0)

if( NOT DEFINED CMAKE_TOOLCHAIN_FILE )
  set(CMAKE_TOOLCHAIN_FILE "/opt/devkitpro/cmake/Switch.cmake" CACHE PATH "Toolchain file")
endif()

project(rawgl)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D__SWITCH__ -DBYPASS_PROTECTION -DUSE_GL -DGLEW_NO_GLU -O3 -g")

include_directories(
  ${DEVKITPRO}/portlibs/switch/include
  ${DEVKITPRO}/portlibs/switch/include/SDL2
)

link_directories(
  ${DEVKITPRO}/libnx/lib
  ${DEVKITPRO}/portlibs/switch/lib
)

file(GLOB SRCS *.cpp)
add_executable(${CMAKE_PROJECT_NAME}.elf
  ${SRCS}
)

target_link_libraries(${CMAKE_PROJECT_NAME}.elf
  SDL2_mixer
  SDL2
  GLEW
  EGL
  glapi
  drm_nouveau
  vorbisfile
  vorbis
  ogg
  mpg123
  modplug
  mikmod
  fluidsynth
  FLAC
  opusfile
  opus
  z
  nx
  m
)

add_custom_target(${CMAKE_PROJECT_NAME}.nro
  DEPENDS ${CMAKE_PROJECT_NAME}.elf
  COMMAND nacptool --create "Another World" "usineur" "2.0" ${CMAKE_PROJECT_NAME}.nacp
  COMMAND elf2nro ${CMAKE_PROJECT_NAME}.elf ${CMAKE_PROJECT_NAME}.nro --icon=${CMAKE_SOURCE_DIR}/res/icon.jpg --nacp=${CMAKE_PROJECT_NAME}.nacp
)

add_custom_target(send
  COMMAND curl -T ${CMAKE_PROJECT_NAME}.nro ftp://$(SWITCHIP):5000/switch/${CMAKE_PROJECT_NAME}/
  DEPENDS ${CMAKE_PROJECT_NAME}.nro
)

add_custom_target(nxlink
  COMMAND nxlink -a $(SWITCHIP) ${CMAKE_PROJECT_NAME}.nro -s -p ${CMAKE_PROJECT_NAME}/${CMAKE_PROJECT_NAME}.nro
  DEPENDS ${CMAKE_PROJECT_NAME}.nro
)
