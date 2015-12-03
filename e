#!/usr/bin/env rc

edit_cmd=nvim
allowx=true

~ $1 --nofork && { allowx=false; shift }
test -n $"SSH_CONNECTION && allowx=false

if( $allowx && canx ) {
    # have to split $TERMINAL into words!
    `{echo $TERMINAL} -e $edit_cmd $* &
}
if not $edit_cmd $*
