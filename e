#!/bin/sh

allowx=true

test "$1" = "--nofork" && allowx=false
test -n "$SSH_CONNECTION" && allowx=false

if $allowx && canx; then
    nvim-qt "$@" 2> /dev/null
else
    test "$1" = "--nofork" && shift
    nvim "$@"
fi
