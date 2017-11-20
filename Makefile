all: diewithparent canx xawaitkill xsk wname

diewithparent: diewithparent.c
	cc -o diewithparent diewithparent.c

canx: canx.c
	cc -o canx -lxcb canx.c || ( printf "#!/bin/sh\nexit 1" > canx; chmod +x canx )

xawaitkill: xawaitkill.c
	cc -o xawaitkill xawaitkill.c

xsk: xsk.c
	cc -o xsk xsk.c -lX11

wname: wname.c
	cc -o wname wname.c -lxcb
