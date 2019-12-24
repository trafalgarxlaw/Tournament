# Travail pratique 1 : Génération d'une grille de tournoi


## Description

Ce projet est un Travail pratique universitaire pour le cours INF3135 (Construction et maintenance de logiciels) qui se donne à Université du Québec à Montréal en automne 2019. Il s'agit d'un programme écrit en C qui consiste à générer une grille de tournois à partir d'une liste de joueurs (ou d'équipes). 

Le lien vers l'[énoncé du
travail ce trouve ici.](https://gitlab.info.uqam.ca/inf3135-aut2019/inf3135-aut2019-tp1-enonce)

## Auteur
Yassine Hasnaoui (HASY04089702)


## Fonctionnement
Pour faire fonctionner le programme, il suffit simplement de taper la commande: make sur le terminal en étang dans le répertoire du projet afin de compiler le programme.

Ensuite, la prochaine commande à taper sur le terminal est<br />
./tournament -s table < examples/(le nom d'un fichier contenant une liste de joueurs).in

## Tests
Pour lancer les tests automatiques, il suffit d'utiliser la commande  `make test`.
<br />
<br />
*Note (manque de temps): <br />
les deux derniers tests échouent à cause d'un décalage dans l'affichage. <br />
Mes fonctions sont beaucoup trop longues, contiennent des structures fortement imbriquées et des valeurs magiques. 

## Dépendances

Le projet utilise comme dependance les élément suivant :<br />
          - [Bats](https://github.com/sstephenson/bats)<br />
          - Compilateur gcc


## Références

Aucune référence n'a été utilisée pour ce projet en dehors des notes de cours.

## État du projet

* [x] Le nom du dépôt GitLab est exactement `inf3135-aut2019-tp1` (Pénalité de
  **50%**).
* [x] L'URL du dépôt GitLab est exactement (remplacer `utilisateur` par votre
  nom identifiant GitLab) `https://gitlab.info.uqam.ca/utilisateur/inf3135-aut2019-tp1`
  (Pénalité de **50%**).
* [x] L'utilisateur `blondin_al` (groupe 20) ou `francoeur_g` (groupe 40)
  a accès au projet en mode *Developer* (Pénalité de **50%**).
* [x] Le dépôt GitLab est un **clone** de [ce
  dépôt](https://gitlab.info.uqam.ca/inf3135-aut2019/inf3135-aut2019-tp1)
  (Pénalité de **50%**).
* [x] Le dépôt GitLab est privé (Pénalité de **50%**).
* [x] Le dépôt contient au moins un fichier `.gitignore`.
* [x] Le fichier `Makefile` permet de compiler le projet lorsqu'on entre
  `make`. Il supporte les cibles `html`, `test` et `clean`.
* [x] Le nombre de tests qui réussissent/échouent avec la `make test` est
  indiqué.
* [x] Les sections incomplètes de ce fichier (`README.md`) ont été complétées.
* [ ] L'en-tête du fichier est documentée.
* [ ] L'en-tête des prototypes des fonctions est documentée (*docstring*).
* [ ] Le programme ne contient pas de valeurs magiques.



