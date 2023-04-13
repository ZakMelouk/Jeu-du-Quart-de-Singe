#include <iostream>
#include <fstream>
#include <iomanip> // pour setw
#pragma warning(disable:4996)
using namespace std;

#include "FonctionRobot.h"
#include "FonctionHumain.h"

/**
 * @brief transforme un caractere en majuscule si c'est une majuscule
 * @param[in] c : un caractere
 * @return le caractere majuscule
 */
char transforme(char c) {
	c = toupper(c);
	return c;
}
/**
 * @brief initialise la partie
 * @param[in,out] j : structure de la partie
 * @param[in] joueurs : tableau contenant les lettres qui correspondent au nombre de joueurs et leur nature
 */
void intialiser_struct(Jeux& j, const char joueurs[]) {

	j.nb_humains = 0;
	j.nb_robots = 0;

	for (int i = 0; i < strlen(joueurs); ++i) {

		if (joueurs[i] == 'R') {
			j.nb_robots++;
		}
		else {
			j.nb_humains++;
		}
	}
	j.indice_mot = 0;
	j.nb_joueurs = j.nb_humains + j.nb_robots;
	j.joueurs = new Joueurs[j.nb_humains];
	j.robots = new Robots[j.nb_robots];
	j.nbtour = 0;
	j.joueur_perdant = 0;
	j.passage_h = 0;
	j.passage_r = 0;
	j.indice_lettre = 0;
	j.partie_fini = false;
	j.manche_fini = false;

	for (unsigned int i = 0; i < j.nb_humains; ++i) {
		j.joueurs[i].indice_joueur_humain = i;
		j.joueurs[i].nb_quart_singe = 0;
	}

	for (unsigned int i = 0; i < j.nb_robots; ++i) {	
		j.robots[i].indice_joueur_robots = i;
		j.robots[i].nb_quart_de_singe = 0;
	}

	j.mot_en_cours = new char[MAX_CHAR];
	j.agrandissement_mot = MAX_CHAR;
	for (unsigned int i = 0; i < MAX_CHAR; ++i) {
		j.mot_en_cours[i] = NULL;
	}
}
/**
 * @brief verifie que le nombre et la nature des joueurs sont bons
 * @param[in] joueurs : tableau contenant les lettres qui correspondent au nombre de joueurs et leur nature
 * @return 1 si les conditions ne sont pas respectées, sinon 0
 */
int verif(char joueurs[]) {

	unsigned int taille = 0;
	taille = (int) strlen(joueurs);
	for (unsigned int i = 0; i < taille; ++i) {
		joueurs[i] = transforme(joueurs[i]);
	}
	for (unsigned int i = 0; i < taille; ++i) {

		if (joueurs[i] != 'R' && joueurs[i] != 'H') {
			cout << "Les lettres que vous avez entrer ne sont pas valides" << endl;
			return 1;
		}
	}

	if (taille < 2){
		cout << "Le nombre de joueurs doit-etre superieur ou egal a 2" << endl;
		return 1;
	}
	return 0;
}
/**
 * @brief Lance une partie
 * @param[in,out] j : structure de la partie
 * @param[in] joueurs : tableau contenant les lettres qui correspondent au nombre de joueurs et leur nature
 */
void partie(Jeux& j, const char joueurs[]) {

	do {
		if (j.manche_fini == false) {
			j.passage_h = 0;
			j.passage_r = 0;
		}
		for (unsigned int i = 0; i < j.nb_joueurs; ++i) {
			if (j.manche_fini) {
				i = j.joueur_perdant;
			}
			j.manche_fini = false;

			if (joueurs[i] == 'R') {
				j.manche_fini = jeux_robot(j, joueurs, i);
			}
			else {
				jeux_humain(j, joueurs, i);

				if (j.partie_fini == true || j.manche_fini == true)
					break;
			}
		}
	} while (j.partie_fini == false);
}

/**
 * @brief affiche le nombre de quart de singe de chaque joueur et si la partie est finie
 * @param[in,out] j : structure de la partie
 * @param[in] joueurs : tableau contenant les lettres qui correspondent au nombre de joueurs et leur nature
 * @return true si la partie est finie, sinon false
 */
bool affichage(Jeux& j, const char joueurs[]) {
	unsigned int humain = 0;
	unsigned int robot = 0;
	for (unsigned int u = 0; u < j.nb_joueurs;) {
		if (joueurs[u] == 'H') {
			cout << u + 1 << 'H' << " : " << j.joueurs[humain].nb_quart_singe;
			++humain;
			++u;
		}
		else {
			cout << u + 1 << "R" << " : " << j.robots[robot].nb_quart_de_singe;
			++robot;
			++u;
		}

		if (u == j.nb_joueurs) {
			cout << endl;

		}
		else
			cout << "; ";
	}
	for (unsigned int i = 0; i < j.nb_humains; ++i) {
		if (j.joueurs[i].nb_quart_singe == 1) {
			cout << "La partie est finie" << endl;
			delete[]j.mot_en_cours;
			return true;
		}
	}
	for (unsigned int i = 0; i < j.nb_robots; ++i) {
		if (j.robots[i].nb_quart_de_singe == 1) {
			cout << "La partie est finie" << endl;
			delete[]j.mot_en_cours;
			return true;
		}
	}
	delete[]j.mot_en_cours;
	j.mot_en_cours = new char[MAX_CHAR];
	j.agrandissement_mot = MAX_CHAR;
	for (unsigned int i = 0; i < MAX_CHAR; ++i) {
		j.mot_en_cours[i] = NULL;
	}
	j.indice_mot = 0;
	j.nbtour = 0;
	return false;
}


/**
 * @brief ajoute une lettre au tableau contenant le mot en cours
 * @param[in,out] j : structure de la partie
 * @param[in] i: indice du joueur actuel
 * @param[in] lettre: la lettre à ajouter
 * @param[in] joueurs : tableau contenant les lettres qui correspondent au nombre de joueurs et leur nature
 */
void ajout_lettre(Jeux& j, const unsigned int i, const char lettre, const char joueurs[]) {
	
	 if (j.indice_mot == j.agrandissement_mot - 1) {
		j.agrandissement_mot += 1;
		char* mot_en_cours = new char[j.agrandissement_mot];
		strcpy(mot_en_cours, j.mot_en_cours);
		delete[] j.mot_en_cours;
		j.mot_en_cours = mot_en_cours;
	}
	 char lettre_donnee[2] = "";
	lettre_donnee[0] = lettre;
	strcat(j.mot_en_cours, lettre_donnee);
	j.indice_mot++;
	j.nbtour++;
	j.joueur_precedent = i;
}
/**
 * @brief Désallocation d'une partie
 * @param[in,out] j : structure de la partie
 */
void desallouer(Jeux& j) {
	delete[]j.joueurs;
	delete[]j.robots;
}
