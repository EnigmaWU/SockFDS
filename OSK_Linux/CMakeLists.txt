#IF kernel-x.y.z directory doest exist
#THEN use cmake external app module to fetch linux kernel from kernel.org with URL: https://cdn.kernel.org/pub/linux/kernel/v4.x/linux-4.19.285.tar.xz
#AND extract it to kernel-x.y.z directory
#USE ARCH=arm64 and its defconfig with CROSS_COMPILE=aarch64-linux-gnu- to make uImage

#use cmake's external app module
include(ExternalProject)
if(NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/kernel-4.19.285)
    ExternalProject_Add(
        kernel
        URL https://cdn.kernel.org/pub/linux/kernel/v4.x/linux-4.19.285.tar.xz
        PREFIX ${CMAKE_CURRENT_SOURCE_DIR}/kernel-4.19.285
        CONFIGURE_COMMAND "make ARCH=arm64 CROSS_COMPILE=aarch64-linux-gnu- defconfig"
        BUILD_COMMAND "make ARCH=arm64 CROSS_COMPILE=aarch64-linux-gnu- uImage"
        BUILD_IN_SOURCE 1
    )
    
endif()
