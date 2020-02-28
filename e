allowx=true

if test "$1" = "--nofork"; then
    allowx=false
    shift
fi

test -n "$SSH_CONNECTION" && allowx=false

if $allowx && canx; then
    urxvtc -e nvim "$@"
else
    test "$1" = "--nofork" && shift
    nvim "$@"
fi
