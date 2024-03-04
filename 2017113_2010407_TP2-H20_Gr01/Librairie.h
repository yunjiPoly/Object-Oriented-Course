#ifndef LIBRAIRIE_H
#define LIBRAIRIE_H

#include <memory>
#include "Film.h"
#include "GestionnaireAuteurs.h"
#include <vector>
/**
 *represente tous les informations de tous les films ainsi que leurs auteurs
 */
class Librairie
{
public:
    /* Constructeur par default de la classe Librairie
	*/
    Librairie();
    /*
	*constructeur par copie de la classe librairie
	*/
    Librairie(const Librairie&);
    /*
	destructeur de la classe Librairie
	*/
    ~Librairie();
    /*
	afficher les films de la liste de vecteur
	*/
    friend std::ostream& operator<<(std::ostream& stream,const Librairie& librairie);
    /**
     * Cette méthode cherche le film dans le tableau de film et retourne un pointeur vers le film
     * Retourner un pointeur nul si le film n’existe pas.
     */
    Film* chercherFilm(const std::string& nomFilm);
    /**Cette méthode lit le fichier. Interrompre la fonction et retourner false si
     *lireLigneFilm retourne false.De plus, elle doit s’assurer de supprimer les
     *vieux films avant de charger les films du fichier.
     */
    bool chargerFilmsDepuisFichier(const std::string& nomFichier,
                                   GestionnaireAuteurs& gestionnaireAuteurs);
    /**Cette méthode lit le fichier. Interrompre la fonction et retourner false si
     *lireLigneRestrictions retourne false. De plus, elle doit s’assurer de supprimer les
     *vieux films avant de charger les films du fichier.
     */
    bool chargerRestrictionsDepuisFichiers(const std::string& nomFichier);

	/*
	getter
	qui retourne le vecteur film
	*/
	const std::vector<std::unique_ptr<Film>>& getFilms() const;
    /*
	la methode enleve le nom du film dans la librairie
	*/
    Librairie& operator-=(const std::string& nomFilm);
    /*
	la methode ecrase le nom du film dans la librairie
	*/
    Librairie& operator=(const Librairie& librairie);
    /*  
	la methode ajoute le nom du film dans la librairie
    */
    Librairie& operator+=(Film* film);
    /*
	getter
	@return le nombre de film de la librairie
	*/
    std::size_t getNbFilms() const;

private:
    /*
	supprimer tous les films en clearing le vecteur*/
    void supprimerFilms();
    bool lireLigneRestrictions(const std::string& ligne);
    bool lireLigneFilm(const std::string& ligne, GestionnaireAuteurs& gestionnaireAuteurs);
    int trouverIndexFilm(const std::string& nomFilm) const;

    // Movies array
    std::vector<std::unique_ptr<Film>>films_;
};

#endif // LIBRAIRIE_H