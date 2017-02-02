all: diewithparent canx xawaitkill xsk

diewithparent:
	cc -o diewithparent diewithparent.c

canx: 
	cc -o canx -lxcb canx.c || ( printf "#!/bin/sh\nexit 1" > canx; chmod +x canx )

xawaitkill:
	cc -o xawaitkill xawaitkill.c

xsk:
	cc -o xsk xsk.c -lX11
