# Codex Naturalis - Projet LO21

Application permettant de jouer au jeu de société **Codex Naturalis** (édité par Bombyx), développée dans le cadre de l'UV LO21 à l'UTC (Université de Technologie de Compiègne).
Le jeu est jouable de 1 à 4 joueurs, incluant un mode solo, en mode console ou avec une interface graphique.

---

##  Prérequis
Pour compiler et exécuter ce projet, vous devez disposer des outils suivants :
* **Compilateur C++ (17 ou +)**
* **CMake** (version 3.28.1 minimum)
* **Qt 6** 

Sur Ubuntu/Debian, installez les dépendances avec :
```bash
sudo apt update
sudo apt install build-essential cmake qt6-base-dev
```

## Compilation et Exécution

Placez-vous à la racine du projet et exécutez les commandes suivantes :

```bash
# Créer le dossier de compilation
cmake -B build

# Build le projet
cmake --build build
```

**Pour lancer le jeu :**
* Mode Console : `./build/src/console/Codex_Console`
* Mode Graphique : `./build/src/gui/Codex_GUI`

## Architecture du projet
* `src/core/` : Contient toute la logique du jeu (indépendante de l'affichage). Compilé sous forme de bibliothèque statique.
* `src/gui/` : Interface graphique développée avec Qt 6.
* `src/console/` : Interface textuelle jouable dans le terminal.