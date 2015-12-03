diewithparent:
	cc -o diewithparent diewithparent.c

canx: 
	cc -o canx -lxcb canx.c || ( printf "#!/bin/sh\nexit 1" > canx; chmod +x canx )
