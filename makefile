COMPILER = gcc
FILES = main.c arbolesADT.c manejoArch.c 
CFLAGS = -lm -Wall -pedantic -std=c99 -fsanitize=address -g
ROOTNAME = arbolesADT
BUE_LABEL = BUE
VAN_LABEL = VAN
OUTPUT_BUE = $(ROOTNAME)$(BUE_LABEL)
OUTPUT_VAN = $(ROOTNAME)$(VAN_LABEL)

all: arbolesADTVAN arbolesADTBUE
arbolesADTVAN:
	$(COMPILER) -o $(OUTPUT_VAN) $(CFLAGS) $(FILES) -D VAN 
	@echo Compilacion exitosa!

arbolesADTBUE:
	$(COMPILER) -o $(OUTPUT_BUE) $(CFLAGS) $(FILES) -D BUE
	@echo Compilacion exitosa!
clean:
	rm -r arbolesADTVAN arbolesADTBUE
	@echo Limpieza exitosa!
