#ifndef _FONCTIONJEUX_
#define _FONCTIONJEUX_

#include <iostream>
using namespace std;

enum { MAX_CHAR = 25 };
enum { NB_MOT = 369085 };

struct Joueurs {
	unsigned int indice_joueur_humain;
	float nb_quart_singe;
};

struct Robots {
	unsigned int indice_joueur_robots;
	float nb_quart_de_singe;
};


struct Jeux {
	Joueurs* joueurs;
	Robots* robots;
	unsigned int nb_joueurs;
	char* mot_en_cours;
	char* lettre_perdante;
	unsigned int indice_mot;
	unsigned int agrandissement_mot;
	unsigned int joueur_precedent;
	unsigned int joueur_precedant_indice;
	unsigned int nbtour;
	unsigned int joueur_perdant;
	unsigned int passage_h;
	unsigned int passage_r;
	unsigned int nb_robots;
	unsigned int nb_humains;
	unsigned int indice_lettre;
	bool partie_fini;
	bool manche_fini;
};

/**
 * @brief transforme un caractere en majuscule si c'est une majuscule
 * @param[in] c : un caractere
 * @return le caractere majuscule
 */
char transforme(char c);

/**
 * @brief initialise la partie 
 * @param[in,out] j : structure de la partie
 * @param[in] joueurs : tableau contenant les lettres qui correspondent au nombre de joueurs et leur nature 
 */
void intialiser_struct(Jeux& j, const char joueurs[]);

/**
 * @brief verifie que le nombre et la nature des joueurs sont bons
 * @param[in] joueurs : tableau contenant les lettres qui correspondent au nombre de joueurs et leur nature 
 * @return 1 si les conditions ne sont pas respectées, sinon 0
 */
int  verif(char joueurs[]);

/** 
 * @brief Lance une partie
 * @param[in,out] j : structure de la partie
 * @param[in] joueurs : tableau contenant les lettres qui correspondent au nombre de joueurs et leur nature
 */
void partie(Jeux& j, const char joueurs[]);

/**
 * @brief ajoute une lettre au tableau contenant le mot en cours 
 * @param[in,out] j : structure de la partie 
 * @param[in] i: indice du joueur actuel
 * @param[in] lettre: la lettre à ajouter
 * @param[in] joueurs : tableau contenant les lettres qui correspondent au nombre de joueurs et leur nature
 */
void ajout_lettre(Jeux& j, const unsigned int i, const char lettre, const char joueurs[]);

/**
 * @brief affiche le nombre de quart de singe de chaque joueur et si la partie est finie
 * @param[in,out] j : structure de la partie
 * @param[in] joueurs : tableau contenant les lettres qui correspondent au nombre de joueurs et leur nature
 * @return true si la partie est finie, sinon false
 */
bool affichage(Jeux& j, const char joueurs[]);

/** 
 * @brief Désallocation d'une partie
 * @param[in,out] j : structure de la partie
 */
void desallouer(Jeux& j);


#endif 
