PWD=$(shell pwd)
REP=$(shell basename $(PWD))
SOURCES=$(shell cat makefile_sources)
CIBLE=$(REP).exe
CFLAGS=-Wall

# makefile générique pour produire un code source 
# dont le nom correspond au nom du répertoire qui le contient

all: indexation.exe
	@echo "Le programme indexation.exe a été produit dans le répertoire $(REP)"


indexation.exe: indexation.c $(SOURCES)
	@ gcc $(CFLAGS) indexation.c $(SOURCES) -o $@
	

clean: 
	@echo "Nettoyage de $(CIBLE)"
	@rm -rf $(CIBLE)
