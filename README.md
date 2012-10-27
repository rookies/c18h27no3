c18h27no3
=======

## Installation

### Linux
 * *git clone git://github.com/rookies/c18h27no3.git*
 * *cd sf-game*
 * *./build.sh all*
 * *./game*

### Windows
 * Get the source code
 * [Download](https://github.com/LaurentGomila/SFML/zipball/2.0-rc), CMake and make SFML
  * Copy *{SFML_BUILDDIR}/lib/sfml-{graphics,system,window}-2.dll* into {GAME_SOURCEDIR}
  * Copy *{SFML_SOURCEDIR}/include/SFML* into {GAME_SOURCEDIR}/include
 * Download [libintl for Windows](http://gnuwin32.sourceforge.net/packages/libintl.htm):
  * [Binaries](http://gnuwin32.sourceforge.net/downlinks/libintl-bin-zip.php)
   * Copy *bin/libintl3.dll* into {GAME_SOURCEDIR}
  * [Dependencies](http://gnuwin32.sourceforge.net/downlinks/libintl-dep-zip.php)
   * Copy *bin/libiconv2.dll* into {GAME_SOURCEDIR}
  * [Developer files](http://gnuwin32.sourceforge.net/downlinks/libintl-lib-zip.php)
   * Copy *include/libintl.h* into {GAME_SOURCEDIR}/include
 * CMake the game
 * make the game
 * copy *game.exe* from build dir to source dir
 * create .mo files ({GAME_SOURCEDIR}/locale/$lang.po => {GAME_SOURCEDIR}/locale/$lang/LC_MESSAGES/c18h27no3.mo)
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
