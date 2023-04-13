#include <iostream>
#include <fstream>
#include <iomanip>
#include "FonctionRobot.h"
#include "FonctionHumain.h"
#pragma warning(disable:4996)


using namespace std;

/**
 * @brief Génère une lettre au hasard pour le tour du robot
 * @return une lettre au hasard
 */
char Lettre_Robot_Hasard() {

	srand(time(NULL));

	char c = (rand() % ((90 - 65) + 1)) + 65;

	c = transforme(c);

	return c;
}
/**
 * @brief Verifie si les lettres actuelle qui compose le mot en cours peuvent potentiellement former le debut d'un mot existant
 * @param[in] j : structure de la partie
 * @return true si le mot est present dans le dictionnaire, sinon false.
 */
bool verif_existence_mot_en_cours(const Jeux& j) {

	ifstream dico("dico.txt");

	if (!dico) {
		cout << "le dictionnaire n'a pu etre ouvert" << endl;
		return 0;
	}

	if (strlen(j.mot_en_cours) < 3) { //On prends pas en compte les mots de 2 lettres
		return true;
	}

	char mot_dico[MAX_CHAR];
	dico >> setw(MAX_CHAR) >> mot_dico; // on essaye de lire le premier mot
	while (dico) {
		unsigned int validite = 0;
		for (unsigned int i = 0; i < strlen(j.mot_en_cours); ++i) {
			if (mot_dico[i] == j.mot_en_cours[i]) {
				validite += 1;
			}
			if (validite == strlen(j.mot_en_cours))
				return true;
		}
		dico >> setw(MAX_CHAR) >> mot_dico; // on essaye de lire le mot suivant
	}

	dico.close();
	return false;
}

/**
 * @brief trouve un mot dans le dictionnaire commençant par les lettres du mot en cours
 * @param[in] j : la partie
 * @param[in,out] a : le mot trouvé
 */
int trouver_mot(const Jeux& j, char a[MAX_CHAR]) {

	ifstream dico("dico.txt");

	if (!dico) {
		cout << "le dictionnaire n'a pu etre ouvert" << endl;
		return 1;
	}
	char mot_dico[MAX_CHAR];
	dico >> setw(MAX_CHAR) >> mot_dico;// on essaye de lire le premier mot

	while (dico) {
		unsigned int validite = 0;
		for (unsigned int i = 0; i < j.indice_mot; ++i) {
			if (mot_dico[i] == j.mot_en_cours[i]) {
				validite += 1;
			}
			if ((validite == j.indice_mot) && strlen(mot_dico) > 2) {
				strcpy(a, mot_dico);
				return 0;
			}
		}
		dico >> setw(MAX_CHAR) >> mot_dico; // on essaye de lire le mot suivant
	}
	dico.close();

	return 1;
}

/**
 * @brief  Trouve toutes les lettres qui peuvent former un mot en finissant le mot en cours
 * @param[in,out] j : la partie
 */
void lettre_perdante(Jeux& j) {

	ifstream dico("dico.txt");
	if (!dico) {
		cout << "le dictionnaire n'a pu etre ouvert" << endl;
		return;
	}
	char mot_dico[MAX_CHAR] = "";
	dico >> setw(MAX_CHAR) >> mot_dico; // on essaye de lire le premier mot

	j.indice_lettre = 0;
	unsigned int nb_lettre = 2;
	j.lettre_perdante = new char[nb_lettre];
	for (unsigned int i = 0; i < nb_lettre; ++i) {
		j.lettre_perdante[i] = NULL;
	}

	while (dico) {
		unsigned int validite = 0;
		for (unsigned int i = 0; i <j.indice_mot; ++i) {
			if (mot_dico[i] == j.mot_en_cours[i]) {
				validite++;
				if (validite == j.indice_mot) {
					if (strlen(mot_dico) > 2) {
						if (strlen(mot_dico) == j.indice_mot + 1) {
							if (j.indice_lettre == nb_lettre - 1) {
								++nb_lettre;
								char* lettre_perdante = new char[nb_lettre];
								for (unsigned int i = 0; i < nb_lettre; ++i) {
									lettre_perdante[i] = NULL;
								}
								strcpy(lettre_perdante, j.lettre_perdante);
								delete[]j.lettre_perdante;
								j.lettre_perdante = lettre_perdante;
							}
							j.lettre_perdante[j.indice_lettre] = mot_dico[j.indice_mot];
							++j.indice_lettre;
						}
					}
				}
			}
		}
		dico >> setw(MAX_CHAR) >> mot_dico; // on essaye de lire le mot suivant
	}
	dico.close();
	return;
}

/**
 * @brief  Trouve toutes les lettres qui peuvent former un mot en finissant le mot en cours
 * @param[in,out] j : la partie
 */
char trouver_lettre_mot_long(const Jeux& j) {
	char mot_dico[MAX_CHAR] = "";
	ifstream dico("dico.txt");

	if (!dico) {
		cout << "le dictionnaire n'a pu etre ouvert" << endl;
		return 0;
	}
	dico >> setw(MAX_CHAR) >> mot_dico; // on essaye de lire le premier mot
	unsigned int taille = 0;
	taille = (int) strlen(mot_dico);
	char plus_grand[MAX_CHAR] = "";
	strcpy(plus_grand, mot_dico);
	while (dico) {
		unsigned int validite = 0;
		for (unsigned int i = 0; i < j.indice_mot; ++i) {
			if (mot_dico[i] == j.mot_en_cours[i]) {
				validite++;
				if ((validite == j.indice_mot) && strlen(mot_dico) > 2) {
					unsigned int taille_intermediaire = 0;
					taille_intermediaire = (int) strlen(mot_dico);
					if (taille_intermediaire > taille) {
						unsigned int validite2 = 0;
						for (unsigned int u = 0; u < j.indice_lettre; ++u) {
							if (j.lettre_perdante[u] != mot_dico[j.indice_mot]) {
								validite2++;
							}
						}
						if (validite2 == j.indice_lettre) {
							taille = taille_intermediaire;
							strcpy(plus_grand, mot_dico);
						}
					}
				}
			}
		}
		dico >> setw(MAX_CHAR) >> mot_dico; // on essaye de lire le mot suivant
	}
	if (strcmp("AA", plus_grand) == 0) {
		return '?';
	}
	return plus_grand[j.indice_mot];
}
/**
 * @brief trouve l'avant derniere lettre d'un mot qui commence par les meme que le mot en cours mot ou un "?" si aucune lettre n'est trouvee
 * @param[in] j : la partie
 * @return "?" si aucune lettre n'est trouvee, sinon la lettre piege.
 */
char trouver_lettre_piege(const Jeux& j) {
	char mot_dico[MAX_CHAR] = "";
	ifstream dico("dico.txt");

	if (!dico) {
		cout << "le dictionnaire n'a pu etre ouvert" << endl;
		return 0;
	}
	dico >> setw(MAX_CHAR) >> mot_dico; // on essaye de lire le premier mot
	char piege[MAX_CHAR] = "";
	strcpy(piege, mot_dico);
	while (dico) {
		unsigned int validite = 0;
		for (unsigned int i = 0; i < j.indice_mot; ++i) {
			if (mot_dico[i] == j.mot_en_cours[i]) {
				validite++;
				if ((validite == j.indice_mot) && (strlen(mot_dico) == (j.indice_mot + 2))) {// Pour pieger
					unsigned int validite2 = 0;
					for (unsigned int u = 0; u < j.indice_lettre; ++u) {
						if (j.lettre_perdante[u] != mot_dico[j.indice_mot]) {
							validite2++;
						}
					}
					if (validite2 == j.indice_lettre) {
						strcpy(piege, mot_dico);
						return piege[j.indice_mot];
					}
				}
			}
		}
		dico >> setw(MAX_CHAR) >> mot_dico; // on essaye de lire le mot suivant
	}
	return '?';
}

/**
 * @brief Se lance quand c'est le tour d'un robot
 * @param[in,out] j : structure de la partie
 * @param[in] joueurs : tableau contenant les lettres qui correspondent au nombre de joueurs et leur nature
 * @param[in] indice: indice du joueur en cours
 * @return true si la manche est finie, sinon false
 */
bool jeux_robot(Jeux& j, const char joueurs[], const unsigned int indice) {
	bool manche_fini = false;
	cout << indice + 1 << "R, (" << j.mot_en_cours << ") > ";
	if (j.indice_mot == 0) {
		char c;
		c = Lettre_Robot_Hasard();
		cout << c << endl;
		ajout_lettre(j, indice, c, joueurs);
		j.joueur_precedant_indice = j.passage_r;
		j.passage_r++;
	}

	else if (verif_existence_mot_en_cours(j) == false) {
		cout << "?" << endl;
		if (joueurs[j.joueur_precedent] == 'H') {
			char mot_donne[MAX_CHAR];
			cout << j.joueur_precedent + 1 << "H, saisir le mot > ";
			cin >> setw(MAX_CHAR) >> mot_donne; //inutile de tester le mot vu que la fonction "verifier_existence_mot_en_cours" verifie qu'aucun mot ne commence par les lettres donn�es.	
			cin.ignore(INT_MAX, '\n');
			if (verifier_validite_mot(mot_donne, j) == true) {
				cout << "le mot " << mot_donne << " n'existe pas, " << j.joueur_precedent + 1 << "H prend un quart de singe" << endl;
				j.joueurs[j.joueur_precedant_indice].nb_quart_singe += 0.25;
				j.joueur_perdant = j.joueur_precedent;
			}
			else {
				j.joueurs[j.joueur_precedant_indice].nb_quart_singe += 0.25;
				j.joueur_perdant = j.joueur_precedent;
			}
			j.passage_h = j.joueur_precedant_indice;
			j.partie_fini = affichage(j, joueurs);
			manche_fini = true;
		}
	}

	else {
		lettre_perdante(j);
		char c = trouver_lettre_piege(j);
		if (c == '?') {
			char c = trouver_lettre_mot_long(j);
			if (c == '?') {
				if (joueurs[((indice + 1) % j.nb_joueurs)] == 'H') {
					if (joueurs[j.joueur_precedent] == 'H') {
						srand(time(NULL));
						unsigned int i = (rand() % 2); // Une chance sur 2 de bluffer
						if (i == 0) {
							char t;
							bool lettre_valide = false;
							do {
								t =  Lettre_Robot_Hasard();
								unsigned int validite = 0;
								for (unsigned int i = 0; i < j.indice_lettre; ++i) {
									if (j.lettre_perdante[i] != t)
										validite++;
									if (validite == j.indice_lettre)
										lettre_valide = true;
								}
							} while (lettre_valide == false);
							cout << t << endl;
							ajout_lettre(j, indice, t, joueurs);
							j.joueur_precedant_indice = j.passage_r;
							j.passage_r++;
						}
						else {
							cout << c << endl;
							char mot_donne[MAX_CHAR];
							cout << j.joueur_precedent + 1 << "H, saisir le mot > ";
							cin >> setw(MAX_CHAR) >> mot_donne;
							cin.ignore(INT_MAX, '\n');
							unsigned int taille = (int)strlen(mot_donne);
							for (unsigned int f = 0; f < taille; ++f) {
								mot_donne[f] = transforme(mot_donne[f]);
							}

							if (verifier_validite_mot(mot_donne, j) == true) {	

								if (verif_existence_mot(mot_donne) == true) {
									j.robots[j.passage_r].nb_quart_de_singe += 0.25;
									cout << "le mot " << mot_donne << " existe, le joueur " << indice + 1 << "R prend un quart de singe" << endl;
									j.joueur_perdant = indice;
								}
								else {
									j.joueurs[j.joueur_precedant_indice].nb_quart_singe += 0.25;
									cout << "le mot " << mot_donne << " n'existe pas, le joueur " << j.joueur_precedent + 1 << "H prend un quart de singe" << endl;
									j.joueur_perdant = j.joueur_precedent;
									j.passage_h = j.joueur_precedant_indice;
								}
							}
							else {
								j.joueurs[j.joueur_precedant_indice].nb_quart_singe += 0.25;
								j.joueur_perdant = j.joueur_precedent;
							}
							j.partie_fini = affichage(j, joueurs);
							manche_fini = true;
						}
					}
					else {
						char t;
						bool lettre_valide = false;
						do {
							t = Lettre_Robot_Hasard();
							unsigned int validite = 0;
							for (unsigned int i = 0; i < j.indice_lettre; ++i) {
								if (j.lettre_perdante[i] != t)
									validite++;
								if (validite == j.indice_lettre)
									lettre_valide = true;
							}
						} while (lettre_valide == false);
						t = Lettre_Robot_Hasard();
						cout << t << endl;
						ajout_lettre(j, indice, t, joueurs);// On va bluffer l'humain qui joue apr�s car avant c'est un robot qui joue
						j.joueur_precedant_indice = j.passage_r;
						j.passage_r++;
					}
				}
				else {
					if (joueurs[j.joueur_precedent] == 'H') {
						cout << c << endl;
						char mot_donne[MAX_CHAR];
						cout << j.joueur_precedent + 1 << "H, saisir le mot > ";
						cin >> setw(MAX_CHAR) >> mot_donne;
						cin.ignore(INT_MAX, '\n');
						for (unsigned int f = 0; f < strlen(mot_donne); ++f) {
							mot_donne[f] = transforme(mot_donne[f]);
						}

						if (verifier_validite_mot(mot_donne, j) == true) {
							if (verif_existence_mot(mot_donne) == true) {
								j.robots[j.passage_r].nb_quart_de_singe += 0.25;
								cout << "le mot " << mot_donne << " existe, le joueur " << indice + 1 << "R prend un quart de singe" << endl;
								j.joueur_perdant = indice;
 							}
							else {
								j.joueurs[j.joueur_precedant_indice].nb_quart_singe += 0.25;
								cout << "le mot " << mot_donne << " n'existe pas, le joueur " << j.joueur_precedent + 1 << "H prend un quart de singe" << endl;
								j.joueur_perdant = j.joueur_precedent;
								j.passage_h = j.joueur_precedant_indice;
							}
						}
						else
						{
							j.joueurs[j.joueur_precedant_indice].nb_quart_singe += 0.25;
							j.joueur_perdant = j.joueur_precedent;
						}
					}
					else {
						cout << "!" << endl;
						j.robots[j.passage_r].nb_quart_de_singe += 0.25;
						cout << "le joueur " << indice + 1 << "R abandonne la manche et prend un quart de singe" << endl;
						j.joueur_perdant = indice;
					}
					j.partie_fini = affichage(j, joueurs);
					manche_fini = true;
				}
				

			}
			else {
				cout << c << endl;
				ajout_lettre(j, indice, c, joueurs);
				j.joueur_precedant_indice = j.passage_r;
				++j.passage_r;
			}
		}
		else {
			cout << c << endl;
			ajout_lettre(j, indice, c, joueurs);
			j.joueur_precedant_indice = j.passage_r;
			++j.passage_r;
		}
		delete[]j.lettre_perdante;
	}
	return manche_fini;
}
