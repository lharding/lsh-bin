#!/bin/sh

edit_cmd=nvim
allowx=true

if test "$1" = "--nofork" || test -n "$SSH_CONNECTION"; then
    allowx=false
    shift
fi

# rejoin whitespace in args
args=$(
    IFS='' 
    for arg in $@; do printf '"%s" ' "$arg"; done)
echo $args

if $allowx && canx; then
    $TERMINAL -e sh -c "$edit_cmd $args" &
else
    eval "$edit_cmd $args"
fi
