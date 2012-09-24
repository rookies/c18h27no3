#!/bin/bash
cd "`dirname '$0'`/locale"
for lang in *.po; do
	echo -n "Compiling [$lang]... "
	msgfmt -o "`echo $lang | cut -d'.' -f1`/LC_MESSAGES/sf-game.mo" "$lang"
	if [[ $? -eq 0 ]]; then
		echo "[DONE]"
	else
		echo "[FAIL]"
	fi
done
