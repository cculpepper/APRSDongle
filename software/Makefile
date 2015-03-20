all:
	sh ./make.sh


flash: all
	wine ~/.wine/drive_c/Keil_v5/ARM/ARMCC/bin/fromelf.exe --m32combined ./UVBuild/kl05test.axf --output ./test.srec
