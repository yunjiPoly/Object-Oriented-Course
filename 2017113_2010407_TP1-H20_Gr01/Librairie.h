#ifndef LIBRAIRIE_H
#define LIBRAIRIE_H

#include <memory>
#include "Film.h"
#include "GestionnaireAuteurs.h"
/**
*represente tous les informations de tous les films ainsi que leurs auteurs
*/
class Librairie
{
public:
	/**
	* inilialiser la librairie
	* c'est un constructeur
	*/
	Librairie();
	Librairie(const Librairie&) = delete;
	Librairie(Librairie&&) = delete;
	Librairie& operator=(const Librairie&) = delete;
	Librairie& operator=(Librairie&&) = delete;
	/**
	* supprimer la librairie dans le debut d'eviter les fuites de memoire en appelant la fonction supprimerFilms()
	* c'est un destructeur
	*/
	~Librairie();
	/**
	* ajouter un pointeur de film à la liste des films
	*/
	void ajouterFilm(Film* film);
	/**
	* retirer le film à la liste des films
	*/
	void retirerFilm(const std::string& nomFilm);
	/**
	* Cette méthode cherche le film dans le tableau de film et retourne un pointeur vers le film
	* Retourner un pointeur nul si le film n’existe pas.
	*/
	Film* chercherFilm(const std::string& nomFilm);
	/**Cette méthode lit le fichier. Interrompre la fonction et retourner false si
	*lireLigneFilm retourne false.Cette méthode doit s’assurer de supprimer les
	*vieux films avant de charger les films du fichier.
	*/
	bool chargerFilmsDepuisFichier(const std::string& nomFichier,
		GestionnaireAuteurs& gestionnaireAuteurs);
	/**Cette méthode lit le fichier. Interrompre la fonction et retourner false si
	*lireLigneRestrictions retourne false.Cette méthode doit s’assurer de supprimer les
	*vieux films avant de charger les films du fichier.
	*/
	bool chargerRestrictionsDepuisFichiers(const std::string& nomFichier);
	void afficher(std::ostream& stream) const;
	/**
	* Gets le nombre de films dans la librairie
	* @return le nombre de films
	*/
	std::size_t getNbFilms() const;

private:
	void supprimerFilms();
	bool lireLigneRestrictions(const std::string& ligne);
	bool lireLigneFilm(const std::string& ligne, GestionnaireAuteurs& gestionnaireAuteurs);
	int trouverIndexFilm(const std::string& nomFilm) const;

	// Movies array
	Film** films_;
	std::size_t nbFilms_;
	std::size_t capaciteFilms_;
};

#endif // LIBRAIRIE_H