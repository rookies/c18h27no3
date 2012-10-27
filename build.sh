#!/bin/bash
PROJECTNAME="c18h27no3"

build_default()
{
	## Create build directory:
	if [[ ! -d build ]]; then
		echo " ==> Creating build directory ..."
		mkdir build || exit 1
	fi
	## Change into build directory:
	cd build || exit 1
	## Run CMake:
	echo " ==> Running CMake ..."
	cmake .. || exit 1
	## Run make:
	echo " ==> Running make ..."
	make || exit 1
	## Create symlink:
	cd ..
	if [[ ! -e game ]]; then
		echo " ==> Creating symlink game -> build/game ..."
		ln -s build/game game || exit 1
	fi
}
build_clean()
{
	echo " ==> Removing build directory ..."
	rm -rf build
	echo " ==> Removing game symlink ..."
	rm -f game
}
build_mo()
{
	echo " ==> Compiling language files ..."
	## Change into locale directory:
	cd "`dirname '$0'`/locale"
	## Run through .po files:
	for langf in *.po; do
		## Get language name:
		lang=`echo $langf | cut -d'.' -f1`
		## Print status on console:
		echo -n "Compiling language file for [$lang]... "
		## Create directory "locale/$lang"
		if [[ ! -d "$lang" ]]; then
			mkdir "$lang" || exit 1
		fi
		## Create directory "locale/$lang/LC_MESSAGES"
		if [[ ! -d "$lang/LC_MESSAGES" ]]; then
			mkdir "$lang/LC_MESSAGES" || exit 1
		fi
		## Create .mo file:
		msgfmt -o "$lang/LC_MESSAGES/$PROJECTNAME.mo" "$langf"
		## Print status on console:
		if [[ $? -eq 0 ]]; then
			echo "[DONE]"
		else
			echo "[FAIL]"
		fi
	done
}
build_countlines()
{
	echo -n " ==> Counting lines ... "
	cd "`dirname $0`"
	find src -type f -exec cat {} + | wc -l
}

case $1 in
	all)
		build_clean
		build_default
		build_mo
		;;
	update)
		build_default
		build_mo
		;;
	clean)
		build_clean
		;;
	mo)
		build_mo
		;;
	build)
		build_default
		;;
	countlines)
		build_countlines
		;;
	*)
		echo "Usage: $0 {clean,build,mo,countlines,all,update}"
		echo ""
		echo "  clean:      remove build directory and game symlink"
		echo "  build:      create build directory, run CMake, make and create game symlink"
		echo "  mo:         create *.mo language files"
		echo "  countlines: count source code lines"
		echo ""
		echo "  all         = clean+build+mo"
		echo "  update      = build+mo"
		;;
esac
