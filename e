#!/bin/sh

allowx=true

if test "$1" = "--nofork"; then
    allowx=false
    shift
fi

test -n "$SSH_CONNECTION" && allowx=false

if $allowx && canx; then
    alacritty -e nvim "$@"
else
    test "$1" = "--nofork" && shift
    nvim "$@"
fi
