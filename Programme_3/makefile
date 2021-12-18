PWD=$(shell pwd)
REP=$(shell basename $(PWD))
SOURCES=$(shell cat makefile_sources)
CIBLE=$(REP).exe
CFLAGS=-Wall

# makefile générique pour produire un code source 
# dont le nom correspond au nom du répertoire qui le contient

all: anagrammes.exe
	@echo "Le programme anagrammes.exe a été produit dans le répertoire $(REP)"

anagrammes.exe: anagrammes.c $(SOURCES)
	@ gcc $(CFLAGS) anagrammes.c $(SOURCES) -o $@
	

clean: 
	@echo "Nettoyage de $(CIBLE)"
	@rm -rf $(CIBLE)
