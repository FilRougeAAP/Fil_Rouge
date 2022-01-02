# Fil Rouge AAP : Arbres AVL



## Description

Fil rouge d'APP 2021-2022, creation d'arbres AVL et leur affichage avec graphviz. Mise en place d'un arbre indexant les mots d'un dictionnaire et recherche des anagrammes dans celui-ci.

## Code

* Lastest version (https://github.com/FilRougeAAP/Fil_Rouge)

## Requirements

**Linux** - Graphviz

---

## Execution 

### Programme 1: 
When you're in Programme_1 folder
* Generic: make displayAVL.exe && ./displayAVL.exe filename_with_names numbers_of_names_display (Since first line of the .txt file)

* Example: 
```sh
make displayAVL.exe && ./displayAVL.exe Prenoms/PrenomsV2.txt 10
```

### Programme 2:
When you're in Programme_2 folder
* Generic: make indexation.exe && ./indexation.exe filename_of_dictionary

* Example: 
```sh 
make indexation.exe && ./indexation.exe Dico_nn/Dico_08.txt 
```

### Programme 3:
When you're in Programme_3 folder

* Generic: make anagrammes.exe && ./anagrammes.exe filename_of_dictionary
* Example: 
```sh
make anagrammes.exe && ./anagrammes.exe Dico_nn/Dico_08.txt | less
```

---

## Realised by

Maistret James, Thieffry Émile, CHEVALIER Romain, Feng Yanli &  Hong Yutong. 