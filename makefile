PWD=$(shell pwd)
REP=$(shell basename $(PWD))
SOURCES=$(shell cat makefile_sources2)
CIBLE=$(REP).exe
CFLAGS=-Wall

# makefile générique pour produire un code source 
# dont le nom correspond au nom du répertoire qui le contient

all: $(CIBLE)
	@echo "Le programme $(CIBLE) a été produit dans le répertoire $(REP)"

$(CIBLE) : $(SOURCES)
	@echo -n "Production de $(CIBLE)"
	@echo " à partir des fichiers : $(SOURCES)"
	gcc $(CFLAGS) $(SOURCES) -o $@

displayAVL.exe: displayAVL.c $(SOURCES)
	@ gcc $(CFLAGS) displayAVL.c $(SOURCES) -o $@

main.exe: main.c $(SOURCES)
	@ gcc $(CFLAGS) main.c $(SOURCES) -o $@

clean: 
	@echo "Nettoyage de $(CIBLE)"
	@rm -rf $(CIBLE)
