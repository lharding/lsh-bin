#!/bin/sh

shouldFork=true

if test "$1" = "--nofork"; then
    shouldFork=false
    shift
fi

test -n "$SSH_CONNECTION" && shouldFork=false

if canx; then
    if $shouldFork; then
        alacritty -e nvim "$@" &
    else
        alacritty -e nvim "$@"
    fi
else
    test "$1" = "--nofork" && shift
    nvim "$@"
fi
