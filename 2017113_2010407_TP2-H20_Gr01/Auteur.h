#ifndef AUTEUR_H
#define AUTEUR_H

#include <string>
/**
 *represente les informations de l'auteur d'un film
 */
class Auteur
{
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
    /**
	*Afficher l'auteur
	*/
    friend std::ostream& operator<<(std::ostream& stream, const Auteur& auteur);
    /**
     * Comparer le nom de l'auteur a un autre nom
	 @return true si les deux noms sont les memes.
     */
    bool operator==(std::string& nom) const;
    /**
     * Comparer un nom a le nom d'auteur
     @return true si les deux noms sont les memes.
     */
    friend bool operator==(std::string nom,const Auteur& auteur); 
	/**
     * Gets le nom de l'auteur
     * @return le nom de l'auteur
     */
    const std::string& getNom() const;
    /**
	/cest un getter
     @return l'annee de naissance de l'auteur
     */
    unsigned int getAnneeDeNaissance() const;
    /**
	/cest un getter
	@return le nombre de film de l'auteur
	*/
    unsigned int getNbFilms() const;
    /**
	/un setter qui permet de changer le nombre de film a un nombre dans le parametre
	*/
    void setNbFilms(unsigned int nbFilms);

private:
    std::string nom_;
    unsigned int anneeDeNaissance_;
    unsigned int nbFilms_;
};

#endif // AUTEUR_H