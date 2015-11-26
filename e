#!/bin/sh

edit_cmd=nvim
allowx=true

if [[ "$1" == "--nofork" ]]; then
    allowx=false
    shift
fi

if $allowx && [[ -n "$DISPLAY" ]] && xset -q &> /dev/null; then
    $TERMINAL -e $edit_cmd $@
else
    $edit_cmd $@
fi
