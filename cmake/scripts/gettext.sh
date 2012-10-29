#!/bin/bash
## Create locale directory:
if [[ ! -d "$2" ]]; then
	mkdir -p "$2" || exit 1
fi
for langf in "$1/"*".po"; do
	## Get language name:
	lang=`basename $langf | cut -d'.' -f1`
	## Print status on console:
	echo -n "Compiling language file for [$lang]... "
	## Create directory "locale/$lang"
	if [[ ! -d "$2/$lang" ]]; then
		mkdir "$2/$lang" || exit 1
	fi
	## Create directory "locale/$lang/LC_MESSAGES"
	if [[ ! -d "$2/$lang/LC_MESSAGES" ]]; then
		mkdir "$2/$lang/LC_MESSAGES" || exit 1
	fi
	## Create .mo file:
	msgfmt -o "$2/$lang/LC_MESSAGES/$3.mo" "$langf"
	## Print status on console:
	if [[ $? -eq 0 ]]; then
		echo "[DONE]"
	else
		echo "[FAIL]"
	fi
done
