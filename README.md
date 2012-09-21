sf-game
=======

## Installation
 * **1. Create build directory and change into it**
 * **2. Create Makefile with CMake**
  * *Linux:* Run *cmake ..*
  * *Windows:* Run *cmake-gui* and create the Makefile for your IDE
 * **3. Compile**
  * *Linux:* Run *make*
  * *Windows:* Compile with your IDE
 * **4. Run the Game from the main directory, otherwise it won't find the data files (pictures, sounds, ...)**

## License
Most of the things are licensed under the GNU General Public License v2 or (at your option) any later version.
For details, see COPYING.
### Exceptions
 * data/grass.png
 * Parts of the FFmpeg project (unmodified, for sources and license information see below):
  * avcodec-54.dll
  * avformat-54.dll
  * swscale-2.dll
  * include/libavcodec/*
  * include/libavformat/*
  * include/libavutil/*
  * include/libswscale/*
 * Parts of the SFML project (unmodified, for sources and license information see below):
  * sfml-graphics-2.dll
  * sfml-system-2.dll
  * sfml-window-2.dll
  * include/SFML/*

### Used libraries
 * [Simple and Fast Multimedia Library](http://www.sfml-dev.org/) (SFML) is released under the zlib/libpng license.
 * libavcodec (part of the [FFmpeg](http://ffmpeg.org/) project) is released under the GNU Lesser General Public License.
