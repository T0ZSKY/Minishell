# Minishell

## Description
Minishell est un projet de l'école 42 qui consiste à recréer un interpréteur de commandes basique en C. Ce projet permet de mieux comprendre le fonctionnement d'un shell et de manipuler des concepts avancés comme les processus, les redirections, les pipes et la gestion des signaux.

## Fonctionnalités
- Affichage d'un prompt interactif.
- Gestion de l'historique des commandes.
- Exécution des binaires en fonction de la variable d'environnement PATH.
- Gestion des chemins relatifs et absolus.
- Prise en charge des quotes simples et doubles.
- Gestion des redirections (`<`, `>`, `<<`, `>>`).
- Implémentation des pipes (`|`).
- Gestion des variables d'environnement (`$VAR`, `$?`).
- Gestion des signaux (`ctrl-C`, `ctrl-D`, `ctrl-\`).
- Implémentation des built-ins suivants :
  - `echo` (avec `-n`)
  - `cd`
  - `pwd`
  - `export`
  - `unset`
  - `env`
  - `exit`

## Compilation et exécution
### Compilation
```sh
make
```
### Exécution
```sh
./minishell
```

## Crédits
Projet réalisé dans le cadre de l'école 42.
merci au goat taomalbe

