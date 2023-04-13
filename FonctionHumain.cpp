#include "FonctionHumain.h"
#include "FonctionRobot.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#pragma warning(disable:4996)

using namespace std;

/**
 * @brief Verifie l'existence d'un mot dans le dictionnaire
 * @param[in] mot_donne : tableau contenant les lettres composant le mot
 * @return true si le mot est present dans le dictionnaire, sinon false.
 */
bool verif_existence_mot(const char mot_donne[MAX_CHAR]) {

	ifstream dico("dico.txt");

	if (!dico) {
		cout << "le dictionnaire n'a pu etre ouvert" << endl;
		return 0;
	}

	char mot_dico[MAX_CHAR];
	dico >> setw(MAX_CHAR) >> mot_dico; // on essaye de lire le premier mot
	while (dico) {
		if (strcmp(mot_dico, mot_donne) == 0) {
			if (strlen(mot_dico) > 2) {
				return true;
			}

		}
		dico >> setw(MAX_CHAR) >> mot_dico; // on essaye de lire le mot suivant
	}

	dico.close();
	return false;
}

/**
 * @brief verifie si le mot donné apres un "?" commence bien par les même lettres que le mot en cours ou si l'humain n'a pas tapé un '!' pour abandonner la manche
 * @param[in] mot : tableau contenant les lettres du mot donné
 * @param[in,out] j :structure de la partie
 * @return true si le mot est valide, sinon false.
 */
bool verifier_validite_mot(char mot[MAX_CHAR], Jeux& j) {
	for (unsigned int i = 0; i < strlen(mot); ++i) {
		mot[i] = transforme(mot[i]);
	}
	for (unsigned int g = 0; g < strlen(j.mot_en_cours); ++g) {
		if (mot[g] == '!') {
			cout << "le joueur " << j.joueur_precedent + 1 << "H abandonne la manche et prend un quart de singe" << endl;
			return false;
		}
		else if (j.mot_en_cours[g] != mot[g]) {
			cout << "le mot " << mot << " ne commence pas par les lettres attendues, le joueur " << j.joueur_precedent + 1 << "H prend un quart de singe" << endl;
			return false;
		}
	}
	return true;

}
/**
 * @brief Se lance quand c'est le tour d'un humain
 * @param[in,out] j : structure de la partie
 * @param[in] joueurs : tableau contenant les lettres qui correspondent au nombre de joueurs et leur nature
 * @param[in] i: indice du joueur actuel
 */
void jeux_humain(Jeux& j, const char joueurs[], const unsigned int i) {
	bool trouve_mot = false;
	bool mot_valide = true;
	char lettre;

	cout << i + 1 << "H, (" << j.mot_en_cours << ") > ";

	cin >> lettre;
	cin.ignore(INT_MAX, '\n');

	lettre = transforme(lettre);

	if (lettre == '?') {

		if (j.nbtour == 0) {

			cout << "Vous etes le premier joueur, lettre incorrect, un quart de singe vous ai attribue" << endl;
			j.joueurs[j.passage_h].nb_quart_singe += 0.25;
			j.joueur_perdant = i;
			j.partie_fini = affichage(j, joueurs);
			j.manche_fini = true;
			return;

		}

		else if (joueurs[j.joueur_precedent] == 'R') {

			cout << j.joueur_precedent + 1 << "R, saisir le mot > ";
			char mot[MAX_CHAR] = "";
			if (trouver_mot(j, mot) == 0) {
				j.joueurs[j.passage_h].nb_quart_singe += 0.25;
				j.joueur_perdant = i;
				cout << mot << endl;
				cout << "le mot " << mot << " existe, le joueur " << i + 1 << "H prend un quart de singe" << endl;
				j.manche_fini = true;
				j.partie_fini = affichage(j, joueurs);
				return;
			}
			else {
				cout << "!" << endl;
				cout << "le joueur " << j.joueur_precedent + 1 << "R abandonne la manche et prend un quart de singe" << endl;
				j.robots[j.joueur_precedant_indice].nb_quart_de_singe += 0.25;
				j.passage_r = j.joueur_precedant_indice;
				j.joueur_perdant = j.joueur_precedent;
				j.manche_fini = true;
				j.partie_fini = affichage(j, joueurs);
				return;
			}
		}

		cout << j.joueur_precedent + 1 << "H, saisir le mot > ";
		char mot[MAX_CHAR];
		cin >> setw(MAX_CHAR) >> mot;
		cin.ignore(INT_MAX, '\n');

		for (unsigned int f = 0; f < strlen(mot); ++f) {
			mot[f] = transforme(mot[f]);
		}

		mot_valide = verifier_validite_mot(mot, j);

		if (mot_valide == false) {
			j.joueurs[j.joueur_precedant_indice].nb_quart_singe += 0.25;
			j.joueur_perdant = j.joueur_precedent;
			j.partie_fini = affichage(j, joueurs);
			j.passage_h =j.joueur_precedant_indice;
			j.manche_fini = true;
			return;
		}

		trouve_mot = verif_existence_mot(mot);
		if (trouve_mot == true) {
			j.joueurs[j.passage_h].nb_quart_singe += 0.25;
			cout << "le mot " << mot << " existe, le joueur " << i + 1 << "H prend un quart de singe" << endl;
			j.joueur_perdant = i;
			j.partie_fini = affichage(j, joueurs);
			j.manche_fini = true;
			return;
		}
		else {
			j.joueurs[j.joueur_precedant_indice].nb_quart_singe += 0.25;
			j.joueur_perdant = j.joueur_precedent;
			cout << "le mot " << mot << " n'existe pas, le joueur " << j.joueur_precedent + 1 << "H prend un quart de singe" << endl;
			j.passage_h = j.joueur_precedant_indice;
			j.manche_fini = true;
			j.partie_fini = affichage(j, joueurs);
			return;


		}
	}
	else if (lettre == '!') {
		j.joueurs[j.passage_h].nb_quart_singe += 0.25;
		cout << "le joueur " << i + 1 << "H abandonne la manche et prend un quart de singe" << endl;
		j.joueur_perdant = i;
		j.partie_fini = affichage(j, joueurs);
		j.manche_fini = true;
		return;

	}
	else {
		ajout_lettre(j, i, lettre, joueurs);
		trouve_mot = verif_existence_mot(j.mot_en_cours);
		j.joueur_precedant_indice = j.passage_h;
		if (trouve_mot == true) {
			j.joueur_perdant = i;
			j.joueurs[j.passage_h].nb_quart_singe += 0.25;
			cout << "le mot " << j.mot_en_cours << " existe, le joueur " << i + 1 << "H prend un quart de singe" << endl;
			j.partie_fini = affichage(j, joueurs);
			j.manche_fini = true;
			return;
		}
		else {
			j.passage_h++;
		}

	}
}
