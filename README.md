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

### Windows
 * Get the source code
 * [Download](https://github.com/LaurentGomila/SFML/zipball/2.0-rc), CMake and make SFML
  * Copy *lib/sfml-{graphics,system,window}-2.dll* into the source dir of the game
  * Copy *include/SFML* into a new directory 'include' in the source dir of the game
 * Download [libintl for Windows](http://gnuwin32.sourceforge.net/packages/libintl.htm):
  * [Binaries](http://gnuwin32.sourceforge.net/downlinks/libintl-bin-zip.php)
   * Copy *bin/libintl3.dll* into the source dir of the game
  * [Dependencies](http://gnuwin32.sourceforge.net/downlinks/libintl-dep-zip.php)
   * Copy *bin/libiconv2.dll* into the source dir of the game
  * [Developer files](http://gnuwin32.sourceforge.net/downlinks/libintl-lib-zip.php)
   * Copy *include/libintl.h* into the created 'include' directory in the source dir of the game
 * CMake the game
 * make the game
 * copy *game.exe* from build dir to source dir
 * create .mo files (locale/$lang.po => locale/$lang/LC_MESSAGES/sf-game.mo)
 * Start the game and hope that it works!

## License
Most of the things are licensed under the GNU General Public License v2 or (at your option) any later version.
For details, see COPYING.
### Exceptions
 * data/grass.png
 * data/creeper.png

### Used libraries & other stuff
 * [Simple and Fast Multimedia Library](http://www.sfml-dev.org/) (SFML) is released under the zlib/libpng license.
 * [gettext](https://www.gnu.org/software/gettext/) is released under the GNU General Public License.
 * [Vollkorn](http://friedrichalthausen.de/?page_id=411) is released under the SIL Open Font License.
