#!/bin/bash
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
		mkdir "$lang" || return 1
	fi
	## Create directory "locale/$lang/LC_MESSAGES"
	if [[ ! -d "$lang/LC_MESSAGES" ]]; then
		mkdir "$lang/LC_MESSAGES" || return 1
	fi
	## Create .mo file:
	msgfmt -o "$lang/LC_MESSAGES/sf-game.mo" "$langf"
	## Print status on console:
	if [[ $? -eq 0 ]]; then
		echo "[DONE]"
	else
		echo "[FAIL]"
	fi
done
