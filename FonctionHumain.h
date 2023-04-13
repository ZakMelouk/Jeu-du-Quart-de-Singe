#ifndef _FONCTIONHUMAIN_
#define _FONCTIONHUMAIN_
#include <iostream>
#include "FonctionJeux.H"
/**
 * @brief Verifie l'existence d'un mot dans le dictionnaire
 * @param[in] mot_donne : tableau contenant les lettres composant le mot
 * @return true si le mot est present dans le dictionnaire, sinon false.
 */
bool verif_existence_mot(const char mot_donne[MAX_CHAR]);

/**
 * @brief verifie si le mot donné apres un "?" commence bien par les même lettres que le mot en cours ou si l'humain n'a pas tapé un '!' pour abandonner la manche
 * @param[in] mot : tableau contenant les lettres du mot donné
 * @param[in,out] j :structure de la partie
 * @return true si le mot est valide, sinon false.
 */
bool verifier_validite_mot(char mot[MAX_CHAR], Jeux& j);
/**
 * @brief Se lance quand c'est le tour d'un humain 
 * @param[in,out] j : structure de la partie
 * @param[in] joueurs : tableau contenant les lettres qui correspondent au nombre de joueurs et leur nature
 * @param[in] i: indice du joueur actuel
 */
void jeux_humain(Jeux& j, const char joueurs[], const unsigned int i);

#endif
