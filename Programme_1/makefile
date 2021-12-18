PWD=$(shell pwd)
REP=$(shell basename $(PWD))
SOURCES=$(shell cat makefile_sources)
CIBLE=$(REP).exe
CFLAGS=-Wall

# makefile générique pour produire un code source 
# dont le nom correspond au nom du répertoire qui le contient

all: displayAVL.exe
	@echo "Le programme displayAVL.exe a été produit dans le répertoire $(REP)"


displayAVL.exe: displayAVL.c $(SOURCES)
	@ gcc $(CFLAGS) displayAVL.c $(SOURCES) -o $@

main.exe: main.c $(SOURCES)
	@ gcc $(CFLAGS) main.c $(SOURCES) -o $@

	

clean: 
	@echo "Nettoyage de $(CIBLE)"
	@rm -rf $(CIBLE)
