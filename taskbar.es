#!/bin/env es
xsk Super_L Super_R && noTimeout='-t 0'

fn windowState { 
    win=`{pfw}
    state=``''{xprop -id $win}

    printf '['

    {printf '%s' $state | grep -qi 'floating[^=]*= 1'} && printf 'F '
    {printf '%s' $state | grep -qi maximized} && printf '+ '
    {printf '%s' $state | grep -qi sticky} && printf 'S '
    
    printf '%s] %s' `{xdotool get_desktop} ``\n{wname $win}
}

fn powerState {
    cd /sys/class/power_supply
    for(supply = ``\n{ls}) {
        printf '%s' $sep
        
        type=`{cat $supply/type}
        if {~ $type Mains} {
            ~ `{cat $supply/online} 1 && printf '%s: online' $supply
        } {~ $type Battery} {
            ~ `{cat $supply/present} 1 && \
            printf '%s: %s%% (%s)' $supply `{cat $supply/capacity} `{cat $supply/status}
        }

        sep=' / '
    }

    printf '\n'
}

fn soundState {
    amixer get Master | tail -1 | sed 's/^[^:]\+:/Master/'
}

fn playerState {
     xdotool search YouTube getwindowname | sed 's/- YouTube - Chromium//'
}

cpuCount=`{cat /proc/cpuinfo | grep -c processor}
fn cpuState {
    out=``''{top -b -n 2 -d 0.05 -w 80}
    printf '%s' $out | grep Tasks | tail -1
    printf '%s' $out | grep Mem | tail -1
    printf '%s' $out | grep '%Cpu' | tail -$cpuCount
}

fn netState {
    ip a show up | grep inet | scut 2-3 | tail -n +3 | tr '\n' ' '
    printf '\n'
}

fn draw {
    feedback -r 1337 $noTimeout ``''{windowState} ``''{
        echo
        date +'%a %Y/%m/%d %H:%M.%S (epoch+%s)'
        powerState
        netState
        echo
        playerState
        soundState
        echo 
        ~ $skipped () || cpuState
        ~ $skipped () && printf 'Waiting for top...\n\n\n\n\n%79s' '.'
    } > /dev/null
}


#TODO: move into a 'wait for super up' script
if {! ~ $#noTimeout 0} {
    while true {
        draw
        sleep 0.2
        skipped=1
    } &
    loopId=$apid

    xsk | while true {
        k=<=%read
        echo $k
        if {~ $k Super_*\ 0} {
               kill $loopId;
               feedback -x 1337;
               exit
        }
    }
} {true} { 
    skipped=1
    draw 
}

