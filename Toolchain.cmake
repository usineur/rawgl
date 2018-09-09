set(CMAKE_SYSTEM_NAME "Generic")
set(DEVKITPRO $ENV{DEVKITPRO})

set(CMAKE_SYSTEM_PROCESSOR "armv8-a")
set(CMAKE_C_COMPILER "${DEVKITPRO}/devkitA64/bin/aarch64-none-elf-gcc")
set(CMAKE_CXX_COMPILER "${DEVKITPRO}/devkitA64/bin/aarch64-none-elf-g++")
set(CMAKE_ASM_COMPILER "${DEVKITPRO}/devkitA64/bin/aarch64-none-elf-as")
set(CMAKE_AR "${DEVKITPRO}/devkitA64/bin/aarch64-none-elf-gcc-ar" CACHE STRING "")
set(CMAKE_RANLIB "${DEVKITPRO}/devkitA64/bin/aarch64-none-elf-gcc-ranlib" CACHE STRING "")

set(COMMON_FLAGS "-march=armv8-a -mtune=cortex-a57 -mtp=soft -fPIE -I${DEVKITPRO}/libnx/include -I${DEVKITPRO}/portlibs/switch/include")
set(CMAKE_C_FLAGS "${COMMON_FLAGS}" CACHE STRING "C flags")
set(CMAKE_CXX_FLAGS "${COMMON_FLAGS} -fpermissive -fno-rtti -fno-exceptions" CACHE STRING "C++ flags")

set(CMAKE_FIND_ROOT_PATH ${DEVKITPRO} ${DEVKITPRO}/devkitA64 ${DEVKITPRO}/libnx ${DEVKITPRO}/portlibs/switch)
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)

set(BUILD_SHARED_LIBS OFF CACHE INTERNAL "Shared libs not available")
