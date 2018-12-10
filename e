#!/bin/sh

allowx=true

if test "$1" = "--nofork"; then
    allowx=false
    shift
fi

test -n "$SSH_CONNECTION" && allowx=false

if $allowx && canx; then
    #nvim-qt "$@" 2> /dev/null
    if test "$#" -gt 0; then argStr="$@"; fi
    echo "$argStr"
    $TERMINAL -e "tmux bind-key -T __nobinds C-M-S-m set mouse off \; switch-client -T __nobinds \; set mouse off \; rename-session editor_$(randstr); nvim $argStr"
else
    test "$1" = "--nofork" && shift
    nvim "$@"
fi
