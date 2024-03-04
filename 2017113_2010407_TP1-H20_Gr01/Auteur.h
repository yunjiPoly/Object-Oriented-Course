#ifndef AUTEUR_H
#define AUTEUR_H

#include <string>

class Auteur
{
	/**
	*represente les informations de l'auteur d'un film
	*/
public:
	/**
	 * inilialise l'auteur
	 * c'est un constructeur
	 */
	Auteur() = default;
	/**
	 * inilialise l'auteur avec des parametres
	 * c'est un constructeur
	 */
	Auteur(const std::string& nom, unsigned int anneeDeNaissance);
	void afficher(std::ostream& stream) const;
	/**
	* Gets le nom de l'auteur
	* @return le nom de l'auteur
	*/
	const std::string& getNom() const;
	/**
	* Gets l'annee de naissance de l'auteur
	* @return l'annee de naissance
	*/
	unsigned int getAnneeDeNaissance() const;
	/**
	* Gets le nombre de flms de l'auteur
	* @return le nb de flms de l'auteur.
	*/
	unsigned int getNbFilms() const;
	/**
	* <<set>> le nombre de films au nbfilms
	*/
	void setNbFilms(unsigned int nbFilms);

private:
	std::string nom_;
	unsigned int anneeDeNaissance_;
	unsigned int nbFilms_;
};

#endif // AUTEUR_H