#ifndef UTILISATEUR_H
#define UTILISATEUR_H

#include <string>
#include "Film.h"
#include "Pays.h"
/**
*represente tous les informations d'un utilisateur qui regarde le film
*/
class Utilisateur
{
public:
	/**
	* inilialiser l'utilisateur avec les paremetres
	* c'est un constructeur
	*/
	Utilisateur(const std::string& nom, unsigned int age, bool estPremium, Pays pays);

	/**
	* Verifier les deux conditions: Le film n’est pas restreint dans le pays de l’utilisateur.
	*Si le film a une restriction d’âge, l’utilisateur doit avoir plus de 16 ans
	*@return true si les deux conditions s'appliquent.
	*/
	bool filmEstDisponible(const Film& film) const;
	/**
	* Si le film n'est pas Restreint Dans le Pays et l'age de l'utilisateur est en bas de 16 ans, il retourne false
	* Si le fil n'est pas Restreint Dans le Pays et l'age de l'utilisateur est plus de 16 ans, il retourne vrai
	* Sinon il retourne faux.
	*/
	bool nbLimiteFilmsAtteint() const;
	/**
	* Verifier les deux conditions: film est disponible et l'utilisteur n'atteint pas la limite de le nombre de films gratuis
	*@return true si les deux conditions s'appliquent.
	*/
	bool regarderFilm(const Film& film);
	/**
	* Gets le nombre de films vus par l'utilisateur
	* @return le nombre de films vus par l'utilisateur
	*/
	unsigned int getNbFilmsVus() const;

	static constexpr unsigned int NB_FILMS_GRATUITS = 3;

private:
	std::string nom_;
	unsigned int age_;
	unsigned int nbFilmsVus_;
	bool estPremium_;
	Pays pays_;
};

#endif // UTILISATEUR_H