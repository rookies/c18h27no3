sf-game
=======

## Installation

### Linux
 * *git clone git://github.com/rookies/sf-game.git*
 * *cd sf-game*
 * *./build.sh* (creates build directory and runs cmake & make)
 * *./build-mo.sh* (compiles the language files, needs gettext)
 * *./build/game*
 * or: *ln -s build/game game* and *./game*

## License
Most of the things are licensed under the GNU General Public License v2 or (at your option) any later version.
For details, see COPYING.
### Exceptions
 * data/grass.png
 * data/creeper.png
 * Parts of the FFmpeg project (unmodified, for sources and license information see below):
  * avcodec-54.dll
  * avformat-54.dll
  * avutil-51.dll
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
 * libintl (part of the [GNU gettext](http://www.gnu.org/software/gettext/gettext.html) project) is released under the GNU Lesser General Public License.
