COMPILER=gcc
FLAGS=-pedantic -std=c99 -Wall -fsanitize=address -lm
COMMON= arbolesADT.c manejoArch.c
all: VAN BUE

BUE: OUTPUT_FILE=arbolesADTBUE
BUE: mainBUE.c
	$(COMPILER) -o $(OUTPUT_FILE) mainBUE.c $(COMMON) $(FLAGS)
	@echo Compilacion exitosa!

VAN: OUTPUT_FILE=arbolesADTVAN
VAN: mainVAN.c
	$(COMPILER) -o $(OUTPUT_FILE) mainVAN.c $(COMMON) $(FLAGS)
	@echo Compilacion exitosa!
clean:
	rm -r arbolesADTVAN arbolesADTBUE
	@echo Limpieza exitosa!
