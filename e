#!/bin/sh

edit_cmd=nvim
allowx=true

if test "$1" = "--nofork"; then
    allowx=false
    shift
fi

if $allowx && canx; then
    $TERMINAL -e $edit_cmd $@
else
    $edit_cmd $@
fi
