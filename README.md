# Jeu-du-quart-de-singe

Le but du projet est de d´evelopper un logiciel permettant `a un ensemble de joueurs de disputer une partie de quart
de singe. L’application doit veiller au respect des règles du jeu et gérer la totalité du déroulement de la partie jusqu’à
l’annonce du perdant. Cette ensemble de joueurs peut-être constitués d'humains et de robots. Les robots sont très performants et presque 
imbattables sauf dans certaines situations que je vous laisse découvrir par vous-même. 
Les fonctionnalités du projet et le bilan sont détaillés dans le rapport et voici les règles du jeu ainsi que les consignes d'utilisation.


1) Règles du jeu

Les joueurs annoncent à tour de rôle une lettre qui vient compléter un mot. Un joueur donnant une lettre terminant
un mot existant (de plus de deux lettres) perd la manche et est gratifié d’un quart de singe. Le joueur courant devant
annoncer une lettre peut préférer demander au joueur précédant à quel mot il pense. Si ce dernier est incapable de
donner un mot existant et qui soit cohérent avec les lettres déjà annoncées, il perd la manche. Dans le cas contraire,
c’est le joueur qui a posé la question qui perd la manche. Le premier joueur ayant récolté quatre quarts de singe perd
la partie.
Admettons que, lors des tours précédents d’une manche, les lettres ’A’, ’B’, ’A’ et ’C’ ont été annoncées dans
cet ordre. Si le joueur courant annonce ’A’, il perd la manche car le mot ”ABACA” est un mot existant (c’est une
matière textile). Si par contre, il joue ’U’ et que le joueur suivant lui demande à quel mot il pense, il pourra répondre
”ABACULE” (c’est un petit élément cubique d’une mosaïque) et ce joueur écopera d’un quart de singe.
Les mots retenus sont ceux acceptés au Scrabble, les accents sont ignorés et les verbes peuvent être conjugués.

2) Consignes d'utilisation

Le nombre de joueurs, leur nature (humain ou robot) et l’ordre dans lequel les joueurs prendront leur tour
sont spécifiés par la chaîne de caractère passée sur la ligne de commande. Par exemple, si le fichier exécutable
est nommée singe.exe, alors la commande singe HRHR lance une partie ou 4 joueurs s’affrontent. Le premier et le
troisième sont des humains alors que le deuxième et le quatrième sont des robots.
Le joueur saisit soit une lettre de l’alphabet (non accentuée et en majuscule ou en minuscule) s’il veut compléter la chaîne de lettre, 
soit le caract`ere ’?’ s’il veut demander au joueur précrédent à quel mot qu’il pense, soit le caract`ere ’!’ s’il veut abandonner la manche 
(et prendre un quart de singe). Seuls les mots de plus de deux lettres participent au jeu. L' application fait l’hypothèse que le fichier 
texte correspondant au dictionnaire se trouve dans le répertoire courant ou est lancée l’application.

