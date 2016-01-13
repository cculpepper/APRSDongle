project=APRSDongle
SOURCES=$(wildcard ,/Sources/*.c) $(wildcard ./Generated_Code/*.c)  
all: $(SOURCES)
	echo Making the program....
	sh ./make.sh


srec: all
	echo Converting to srecord...
	wine ~/.wine/drive_c/Keil_v5/ARM/ARMCC/bin/fromelf.exe --m32combined ./UVBuild/kl05test.axf --output ./$(project).srec


DEPLOY_VOLUME = $(shell df -h 2>/dev/null | fgrep " 128M" | awk '{print $$6}')
deploy: $(project).srec srec
	echo Deploying to $(DEPLOY_VOLUME)
	dd conv=fsync bs=64k if=./$(project).srec of=$(DEPLOY_VOLUME)/$(project).srec
		
clean:
	rm ./UVBuild/*.o
