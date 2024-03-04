////////////////////////////////////////////////////////////////////////////////
/// TD1 Hiver 2020.
/// \file    Gestionnaire.cpp
/// \authors   Par Yun Ji Liao(2017113) et Zhao Long Lui(2010407)
/// \authors   Basé sur un squelette écrit par Simon Gauvin
////////////////////////////////////////////////////////////////////////////////

// TODO: Inclure la définition de la classe appropriée
#include "Utilisateur.h"

// TODO: Constructeur utilisant la liste d'initialisation
Utilisateur::Utilisateur(const std::string& nom, unsigned int age, bool estPremium, Pays pays) : nom_(nom), age_(age), nbFilmsVus_(0), estPremium_(estPremium), pays_(pays) {}

//! Méthode qui retourne si le film est disponible pour un utilisateur.
//! \param film Le film à évaluer.
//! \return Un bool représentant si un film est disponible à l'utilisateur.
bool Utilisateur::filmEstDisponible(const Film& film) const
{
	static constexpr unsigned int AGE_MINIMUM_POUR_FILMS_RESTREINTS = 16;

	// TODO
	// Vérifier que le film n'est pas restreint dans le pays de l'utilisateur
	// Vérifier que l'utilisateur a l'âge approprié pour regarder le film (s'il est est restreint
	// pour les moins de 16 ans).

	if (!film.estRestreintDansPays(pays_)) {
		if (film.estRestreintParAge() && AGE_MINIMUM_POUR_FILMS_RESTREINTS <= age_) {
			return true;
		}
		else if (!film.estRestreintParAge()) {
			return true;
		}
		else
			return false;
	}
	else
		return false;
}


// TODO nbLimiteFilmsAtteint() const
// Retourner si l'utilisateur a atteint la limite de films qu'il peut regarder
// Si un utilisateur est premium, il n'y a pas de limite
// Si un utilisateur n'est pas premium, il peut regarder au maximum NB_FILMS_GRATUITS
bool Utilisateur::nbLimiteFilmsAtteint() const {
	if (getNbFilmsVus() >= NB_FILMS_GRATUITS && !estPremium_) {
		return true;
	}
	else if (estPremium_)
		return false;

}
// TODO regarderFilm(const Film& film)
// Vérifier que l'utilisateur n'a pas atteint la limite de films qu'il peut regarder
// Vérifier que le film est disponnible dans le pays de l'utilisateur
// Si ces deux conditions sont remplies, incrémenter nbFilmsVus_ et retourner true
// Sinon, retourner false
bool Utilisateur::regarderFilm(const Film& film) {
	if (!nbLimiteFilmsAtteint() && filmEstDisponible(film)) {
		nbFilmsVus_++;
		return true;
	}
	return false;
}
// TODO getNbFilmsVus() const: Retourner le nombre de films vus
unsigned int Utilisateur::getNbFilmsVus() const {
	return nbFilmsVus_;
}