# .
# minimum CMake version:
# .
cmake_minimum_required(VERSION 2.8)
# .
# project name:
# .
project(route94)
# .
# project version:
# .
set(GAME_VERSION_MAJOR 0)
set(GAME_VERSION_MINOR1 1)
set(GAME_VERSION_MINOR2 1)
# .
# debug settings:
# .
#set(DATALOADER_DEBUG 1)
#set(DATALOADER_VERBOSE 1)
# .
# find custom modules:
# .
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")
# .
# check for functions:
# .
include(CheckFunctionExists)
check_function_exists(putenv HAVE_PUTENV)
check_function_exists(setenv HAVE_SETENV)
# .
# find libraries:
# .
find_package(SFMLwindow REQUIRED)
find_package(SFMLgraphics REQUIRED)
find_package(SFMLsystem REQUIRED)
find_package(SFMLaudio REQUIRED)
find_package(SFMLnetwork REQUIRED)
find_package(LIBINTL REQUIRED)
find_package(LIBARCHIVE REQUIRED)
#find_package(LIBAVCODEC REQUIRED)
#find_package(LIBAVFORMAT REQUIRED)
#find_package(LIBAVUTIL REQUIRED)
#find_package(LIBSWSCALE REQUIRED)
# .
# add include directories for the libraries:
# .
include_directories("${SFMLwindow_INCLUDE_DIR}")
include_directories("${SFMLgraphics_INCLUDE_DIR}")
include_directories("${SFMLsystem_INCLUDE_DIR}")
include_directories("${SFMLaudio_INCLUDE_DIR}")
include_directories("${SFMLnetwork_INCLUDE_DIR}")
include_directories("${LIBINTL_INCLUDE_DIR}")
include_directories("${LIBARCHIVE_INCLUDE_DIR}")
#include_directories("${LIBAVCODEC_INCLUDE_DIR}")
#include_directories("${LIBAVFORMAT_INCLUDE_DIR}")
#include_directories("${LIBAVUTIL_INCLUDE_DIR}")
#include_directories("${LIBSWSCALE_INCLUDE_DIR}")
# .
# create globals.hpp and make it available:
# .
if (UNIX)
	set(GAME_RUNNINGON "Unix")
elseif (WIN32)
	set(GAME_RUNNINGON "Windows")
else ()
	set(GAME_RUNNINGON "Unknown OS")
endif ()
configure_file(
	"${CMAKE_SOURCE_DIR}/src/globals.hpp.in"
	"${CMAKE_BINARY_DIR}/globals.hpp"
)
include_directories("${CMAKE_BINARY_DIR}")
# .
# add general source files:
# .
set(GAME_SOURCES                 src/main.cpp)
set(GAME_SOURCES ${GAME_SOURCES} src/game.cpp)
set(GAME_SOURCES ${GAME_SOURCES} src/padding_data_calculator.cpp)
set(GAME_SOURCES ${GAME_SOURCES} src/cursor.cpp)
#set(GAME_SOURCES ${GAME_SOURCES} src/video_sequence.cpp)
set(GAME_SOURCES ${GAME_SOURCES} src/fps_counter.cpp)
set(GAME_SOURCES ${GAME_SOURCES} src/widestring.cpp)
set(GAME_SOURCES ${GAME_SOURCES} src/config_common.cpp)
set(GAME_SOURCES ${GAME_SOURCES} src/config_chooser.cpp)
set(GAME_SOURCES ${GAME_SOURCES} src/event_processor_return.cpp)
set(GAME_SOURCES ${GAME_SOURCES} src/numerical_textfield_buffer.cpp)
set(GAME_SOURCES ${GAME_SOURCES} src/universal_drawable.cpp)
set(GAME_SOURCES ${GAME_SOURCES} src/dataloader.cpp)
set(GAME_SOURCES ${GAME_SOURCES} src/level.cpp)
set(GAME_SOURCES ${GAME_SOURCES} src/fireanimation.cpp)
# .
# add external source files:
# .
set(GAME_SOURCES ${GAME_SOURCES} src/external/sha256.c)
# .
# add operating system specific source files:
# .
if (UNIX)
	set(GAME_SOURCES ${GAME_SOURCES} src/config_unix.cpp)
elseif (WIN32)
	set(GAME_SOURCES ${GAME_SOURCES} src/config_windows.cpp)
else ()
	message(FATAL_ERROR "Unsupported system")
endif ()
# .
# add gamemode source files:
# .
set(GAME_SOURCES ${GAME_SOURCES} src/gamemodes/main_menu.cpp)
set(GAME_SOURCES ${GAME_SOURCES} src/gamemodes/settings_menu.cpp)
set(GAME_SOURCES ${GAME_SOURCES} src/gamemodes/settings_general_menu.cpp)
set(GAME_SOURCES ${GAME_SOURCES} src/gamemodes/settings_graphics_menu.cpp)
set(GAME_SOURCES ${GAME_SOURCES} src/gamemodes/settings_control_menu.cpp)
set(GAME_SOURCES ${GAME_SOURCES} src/gamemodes/settings_sound_menu.cpp)
set(GAME_SOURCES ${GAME_SOURCES} src/gamemodes/singleplayer.cpp)
set(GAME_SOURCES ${GAME_SOURCES} src/gamemodes/credits.cpp)
set(GAME_SOURCES ${GAME_SOURCES} src/gamemodes/levelchooser.cpp)
set(GAME_SOURCES ${GAME_SOURCES} src/gamemodes/loadgame.cpp)
set(GAME_SOURCES ${GAME_SOURCES} src/gamemodes/newgame.cpp)
set(GAME_SOURCES ${GAME_SOURCES} src/gamemodes/gameshop.cpp)
set(GAME_SOURCES ${GAME_SOURCES} src/gamemodes/intro.cpp)
# .
# add executable:
# .
add_executable(${CMAKE_PROJECT_NAME} ${GAME_SOURCES})
# .
# add libraries to the executable:
# .
target_link_libraries(${CMAKE_PROJECT_NAME} ${SFMLwindow_LIBRARIES})
target_link_libraries(${CMAKE_PROJECT_NAME} ${SFMLgraphics_LIBRARIES})
target_link_libraries(${CMAKE_PROJECT_NAME} ${SFMLsystem_LIBRARIES})
target_link_libraries(${CMAKE_PROJECT_NAME} ${SFMLaudio_LIBRARIES})
target_link_libraries(${CMAKE_PROJECT_NAME} ${SFMLnetwork_LIBRARIES})
target_link_libraries(${CMAKE_PROJECT_NAME} ${LIBINTL_LIBRARIES})
target_link_libraries(${CMAKE_PROJECT_NAME} ${LIBARCHIVE_LIBRARIES})
#target_link_libraries(${CMAKE_PROJECT_NAME} ${LIBAVCODEC_LIBRARIES})
#target_link_libraries(${CMAKE_PROJECT_NAME} ${LIBAVFORMAT_LIBRARIES})
#target_link_libraries(${CMAKE_PROJECT_NAME} ${LIBAVUTIL_LIBRARIES})
#target_link_libraries(${CMAKE_PROJECT_NAME} ${LIBSWSCALE_LIBRARIES})
# .
# add install target:
# .
#if (UNIX)
#	# bin:
#	install(TARGETS ${CMAKE_PROJECT_NAME} DESTINATION "bin/")
#	# img:
#	file(GLOB files "${CMAKE_SOURCE_DIR}/data/img/*")
#	install(FILES ${files} DESTINATION "share/${CMAKE_PROJECT_NAME}/data/img/")
#	# lang files:
#	file(GLOB files "${CMAKE_BINARY_DIR}/locale/*")
#	foreach(lang ${files})
#		get_filename_component(lang_ ${lang} NAME_WE)
#		install(FILES "${CMAKE_BINARY_DIR}/locale/${lang_}.mo" DESTINATION "share/locale/${lang_}/LC_MESSAGES/" RENAME "${CMAKE_PROJECT_NAME}.mo")
#	endforeach()
#elseif (WIN32)
#	# FIXME: add windows-specific install target
#endif ()
