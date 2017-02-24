#!/bin/sh

allowx=true

test "$1" = "--nofork" && allowx=false
test -n "$SSH_CONNECTION" && allowx=false

if $allowx && canx; then
    nvim-qt "$@"
else
    test "$1" = "--nofork" && shift
    nvim "$@"
fi
