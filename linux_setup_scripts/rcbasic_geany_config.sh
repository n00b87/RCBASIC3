#! /bin/bash

if [ -e "$HOME/.config/geany/filedefs/filetypes.freebasic" ]; then
	if [ ! -d "$HOME/.config/geany/filedefs/freebasic_backup" ]; then
		mkdir "$HOME/.config/geany/filedefs/freebasic_backup"
		mv "$HOME/.config/geany/filedefs/filetypes.freebasic" "$HOME/.config/geany/filedefs/freebasic_backup/filetypes.freebasic"
	fi
fi

ft_rc="$(readlink -f geany_files)/filetypes.rcbasic"


cp "$ft_rc" "$HOME/.config/geany/filedefs/filetypes.freebasic"
