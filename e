#!/bin/sh

edit_cmd=nvim

if [[ -n "$DISPLAY" ]] && xset -q &> /dev/null; then
    $TERMINAL -e $edit_cmd $@
else
    $edit_cmd $@
fi
