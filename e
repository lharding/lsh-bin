#!/bin/sh

edit_cmd=nvim
allowx=true

if test "$1" = "--nofork"; then
    allowx=false
    shift
fi

if $allowx && test -n "$DISPLAY" && (xset -q 2>&1) > /dev/null; then
    $TERMINAL -e $edit_cmd $@
else
    $edit_cmd $@
fi
