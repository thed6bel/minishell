# Projet Minishell - École 42

## Description
Minishell est un projet de l'École 42 qui consiste à créer un shell simple mais fonctionnel, inspiré de bash. Ce projet permet d'approfondir la compréhension des processus, des descripteurs de fichiers, et de la gestion des signaux en programmation système.

## Objectifs
- Implémenter un shell fonctionnel avec des fonctionnalités de base
- Gérer l'exécution de commandes et les processus
- Implémenter des built-ins shell
- Gérer les redirections et les pipes
- Implémenter l'expansion des variables d'environnement

## Fonctionnalités
- Affichage d'un prompt en attente d'une nouvelle commande
- Gestion de l'historique des commandes
- Recherche et lancement du bon exécutable (basé sur la variable PATH ou en utilisant un chemin relatif ou absolu)
- Gestion des guillemets simples et doubles
- Implémentation des redirections : `<`, `>`, `<<`, `>>`
- Implémentation des pipes `|`
- Gestion des variables d'environnement
- Gestion des signaux ctrl-C, ctrl-D et ctrl-\
- Implémentation des built-ins : `echo`, `cd`, `pwd`, `export`, `unset`, `env`, `exit`

## Built-ins implémentés
- `echo` avec option -n
- `cd` avec seulement un chemin relatif ou absolu
- `pwd` sans options
- `export` sans options
- `unset` sans options
- `env` sans options ni arguments
- `exit` sans options

## Compétences développées
- Programmation en C
- Gestion des processus et des signaux
- Manipulation des descripteurs de fichiers
- Parsing et interprétation de commandes
- Gestion de l'environnement système

## Installation et utilisation
1. Clonez ce dépôt :
   ```
   git clone https://github.com/votre-username/minishell.git
   ```
2. Naviguez dans le dossier du projet :
   ```
   cd minishell
   ```
3. Compilez le projet :
   ```
   make
   ```
4. Lancez le shell :
   ```
   ./minishell
   ```

## Utilisation
Une fois le shell lancé, vous pouvez entrer des commandes comme vous le feriez dans bash. Par exemple :
```
$> ls -l | grep .c > output.txt
$> echo $HOME
$> cd /path/to/directory
$> export NEW_VAR=value
$> ./program < input.txt
```

## Gestion des erreurs
Le shell gère les erreurs de manière similaire à bash, en affichant des messages d'erreur appropriés et en définissant la variable `$?` avec le code de sortie de la dernière commande exécutée.
