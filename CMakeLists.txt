cmake_minimum_required(VERSION 3.0 FATAL_ERROR)
project(socialBtns VERSION 0.1.0 LANGUAGES CXX)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fms-extensions -Xlinker --no-demangle")
set(CMAKE_CXX_STANDARD 17)
set(BUILD_SHARED_LIBS Off)

    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/Out")
    set(CMAKE_BUILD_TYPE RelWithDebInfo)
    add_definitions(-DCC_TARGET_OS_WIN32)
    include_directories(
        gd.h/cocos2dx
        gd.h/include
        gd.h/
        cocos-headers/
        cocos-headers/extensions
        cocos-headers/cocos2dx
        cocos-headers/cocos2dx/include
        cocos-headers/cocos2dx/kazmath/include
        cocos-headers/cocos2dx/platform/win32
        cocos-headers/cocos2dx/platform/third_party/win32
        cocos-headers/cocos2dx/platform/third_party/win32/OGLES
		cJSON-1.7.15
    )
    set(CMAKE_SIZEOF_VOID_P 4)
    set(CMAKE_SYSTEM_PROCESSOR "i686")
    set(CMAKE_GENERATOR_PLATFORM x86)


add_library(${PROJECT_NAME} SHARED 
    main.cpp
 )


    target_link_libraries(${PROJECT_NAME} 
        "${CMAKE_SOURCE_DIR}/cocos-headers/cocos2dx/libcocos2d.lib"
        "${CMAKE_SOURCE_DIR}/cocos-headers/extensions/libExtensions.lib"
    )

    install(
        TARGETS ${PROJECT_NAME} 
        DESTINATION ${CMAKE_BINARY_DIR}/out/
    )
