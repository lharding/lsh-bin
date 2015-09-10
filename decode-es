#!/bin/bash

IFS=$'\n'
function extract_field() {
    printf "%s" "$PACKET" | grep "^$1: \\?" | sed "s/^$1: \\?//g"
}

AFTER=''
if [[ $1 == '-after' ]]; then
    shift
    #munge ids into a form we can do string comparison on:
    AFTER=`printf "%024.9f" "$1"`
    shift
fi

while read LINE; do
    if [[ -z $LINE ]]; then
        if [[ -n $PACKET ]]; then
            export EVENT=$(extract_field event)            
            export ID=$(extract_field id)
            export TIME=$(extract_field 'time')
            export META=$(extract_field meta)
            export DATA=$(extract_field data)

            if ([[ -z $ID$AFTER ]] || [[ `printf "%024.9f" "$ID"` > $AFTER ]]) &&\
                [[ -n $EVENT$ID$TIME$META$DATA ]]; then
                
                printf "%s" "$PACKET" | $@;
            fi
        fi    
        PACKET=''
    else
        PACKET+="$LINE"
        PACKET+=$'\n'
    fi
done
