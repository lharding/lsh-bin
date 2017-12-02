#!/bin/sh

allowx=true

test "$1" = "--nofork" && allowx=false
test -n "$SSH_CONNECTION" && allowx=false

if $allowx && canx; then
    #nvim-qt "$@" 2> /dev/null
    $TERMINAL -e "tmux bind-key -T __nobinds C-M-S-m set mouse off \; switch-client -T __nobinds \; set mouse off \; rename-session editor_$(randstr); nvim $@"
else
    test "$1" = "--nofork" && shift
    nvim "$@"
fi
