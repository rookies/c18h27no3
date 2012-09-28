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

### Used libraries
 * [Simple and Fast Multimedia Library](http://www.sfml-dev.org/) (SFML) is released under the zlib/libpng license.
 * libavcodec (part of the [FFmpeg](http://ffmpeg.org/) project) is released under the GNU Lesser General Public License.
 * libintl (part of the [GNU gettext](http://www.gnu.org/software/gettext/gettext.html) project) is released under the GNU Lesser General Public License.
