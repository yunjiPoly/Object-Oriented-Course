#ifndef FILM_H
#define FILM_H

#include <memory>
#include <string>
#include "Auteur.h"
#include "Pays.h"
#include<vector>
class Film
{
public:
    enum class Genre
    {
        Action,
        Aventure,
        Comedie,
        Horreur,
        Romance,
        first_ = Action,
        last_ = Romance
    };
    /**
     * inilialiser le  film
     * c'est un constructeur
     */
    Film() = default;
    /**
     * inilialiser le  film avec parametres
     * c'est un constructeur
     */
    Film(const std::string& nom, unsigned int anneeDeSortie, Genre genre, Pays pays,
         bool estRestreintParAge, Auteur* auteur);
    /**
     * ajouter un pays à la liste des pays restreint
     * @return si c'est ajoute
     */
    void ajouterPaysRestreint(Pays pays);
    /**
     * mettre le nombre de pays restreint à 0
     */
    void supprimerPaysRestreints();
    /**
	* cherche si le pays est dans la pays restreint
	@return si c'est trouve
	*/
    bool estRestreintDansPays(Pays pays) const;
    /**
	* get le genre du film
	@return le genre du film
	*/
    Genre getGenre() const;
    /**
    @return true si le film est restein par age sinon return false
    */
    bool estRestreintParAge() const;
    /**
    * get le nom du film
    @return le nom du film
    */
    const std::string& getNom() const;
    /**
    * get les informations de l'auteur du film
    @return les informations de l'auteur du film
    */
    Auteur* getAuteur();
    /*
	Afficher l'information du film
	*/
	friend std::ostream& operator<<(std::ostream& stream, const Film& film);
    /*
	un destructeur qui detruit la classe de film
	*/
	 ~Film();

private:
    // Attributs
    std::string nom_;
    unsigned int anneeDeSortie_;
    Genre genre_;
    Pays pays_;
    bool estRestreintParAge_;
    Auteur* auteur_;
    std::vector<Pays> paysrestreint_;
};

#endif // FILM_H