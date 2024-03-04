////////////////////////////////////////////////////////////////////////////////
/// TD2 Hiver 2020.
/// \file    Librairie.cpp
/// \authors   Par Yun Ji Liao(2017113) et Zhao Long Lui(2010407)
/// \authors   Basé sur un squelette écrit par Simon Gauvin
////////////////////////////////////////////////////////////////////////////////

#include "Librairie.h"
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <vector>
#include "debogageMemoire.h"
#include "typesafe_enum.h"
namespace
{
    constexpr std::size_t CAPACITE_FILMS_INITIALE = 2;
    constexpr int FILM_INEXSISTANT = -1;
} // namespace
Librairie::Librairie()
{
}

//! Constructeur de la classe Librairie
Librairie ::Librairie(const Librairie& librairie)
{
    for (int i = 0; i < librairie.films_.size(); i++)
    {
        films_.push_back(std::make_unique<Film>(*librairie.films_[i]));
    }
}

//! Destructeur de la classe Librairie
Librairie::~Librairie()
{
    supprimerFilms();
}

const std::vector<std::unique_ptr<Film>>& Librairie::getFilms() const
{
   return films_;
}

//! Méthode qui ajoute un film à la liste des films
//! \param film Le film alloué dynamiquement à ajouter à la liste. La classe devient propriétaire du
//!             film.

Librairie& Librairie::operator+=(Film* film)
{
    if (film == nullptr)
    {
        return *this;
    }
    films_.push_back(std::move(std::make_unique<Film>(*film)));
    return *this;
}
Librairie& Librairie::operator-=(const std::string& nomFilm)
{
    int indexFilm = trouverIndexFilm(nomFilm);
    if (indexFilm == FILM_INEXSISTANT)
    {
        return* this;
    }
    size_t max = films_.size() - 1;
    for (size_t i = indexFilm; i < max; i++)
    {
        films_[i] = std::move(films_[i + 1]);
    }
    films_.pop_back();
    return *this;
}
Librairie& Librairie::operator=(const Librairie& librairie)
{
    if (this != &librairie)
    {
        for (int i = 0; i < librairie.films_.size(); i++)
        {
            films_.push_back(std::make_unique<Film>(*librairie.films_[i]));
        }
    }
    return *this;
}
//! Méthode qui retourne un film comportant le même nom que celui envoyé en paramètre
//! \param nomFilm Le nom du film à chercher
//! \return        Un pointeur vers le film. Nullptr si le film n'existe pas
Film* Librairie::chercherFilm(const std::string& nomFilm)
{
    int indexFilm = trouverIndexFilm(nomFilm);
    if (indexFilm == FILM_INEXSISTANT)
    {
        return nullptr;
    }
    return films_[indexFilm].get();
}

//! Méthode qui charge les films à partir d'un fichier.
//! \param nomFichier           Le nom du fichier à lire.
//! \param gestionnaireAuteurs  Le gestionnaire des auteurs. Nécessaire pour associer un film à un
//! auteur.
//! \return                     Un bool représentant si le chargement a été un succès.
bool Librairie::chargerFilmsDepuisFichier(const std::string& nomFichier,
                                          GestionnaireAuteurs& gestionnaireAuteurs)
{
    std::ifstream fichier(nomFichier);
    if (fichier)
    {
        // Supprimers les vieux films avant de lire les nouveaux
        supprimerFilms();

        std::string ligne;
        while (std::getline(fichier, ligne))
        {
            if (lireLigneFilm(ligne, gestionnaireAuteurs) == false)
            {
                return false;
            }
        }
        return true;
    }
    std::cerr << "Le fichier " << nomFichier
              << " n'existe pas. Assurez vous de le mettre au bon endroit.\n";
    return false;
}

//! Méthode qui charge les restrictions des films à partir d'un fichier.
//! \param nomFichier           Le nom du fichier à lire.
//! \return                     Un bool représentant si le chargement a été un succès.
bool Librairie::chargerRestrictionsDepuisFichiers(const std::string& nomFichier)
{
    std::ifstream fichier(nomFichier);
    if (fichier)
    {
        for (std::size_t i = 0; i < films_.size(); i++)
        {
            films_[i]->supprimerPaysRestreints();
        }
        std::string ligne;
        while (std::getline(fichier, ligne))
        {
            if (lireLigneRestrictions(ligne) == false)
            {
                return false;
            }
        }
        return true;
    }
    std::cerr << "Le fichier " << nomFichier
              << " n'existe pas. Assurez vous de le mettre au bon endroit.\n";
    return false;
}

std::ostream& operator<<(std::ostream& stream, const Librairie& librairie)
{
    for (std::size_t i = 0; i < librairie.films_.size(); i++)
    {
        stream << *librairie.films_[i];
        stream << '\n';
    }
    return stream;
}

//! Méthode qui retourne le nombre de films
//! \return Le nombre de films
std::size_t Librairie::getNbFilms() const
{
    return films_.size();
}

//! Méthode qui supprime tous les films
void Librairie::supprimerFilms()
{
    films_.clear();
}

//! Méthode qui ajoute les restrictions d'un film avec un string
//! \param ligne Le string comportant les restrictions du film
//! \return      Un bool représentant si l'opération est un succès
bool Librairie::lireLigneRestrictions(const std::string& ligne)
{
    std::istringstream stream(ligne);
    std::string nomFilm;
    // Pour extraire tout ce qui se trouve entre "" dans un stream,
    // il faut faire stream >> std::quoted(variable)
    if (stream >> std::quoted(nomFilm))
    {
        Film* film = chercherFilm(nomFilm);
        if (film == nullptr)
        {
            // Film n'existe pas
            return false;
        }

        int paysValeurEnum;
        while (stream >> paysValeurEnum)
        {
            film->ajouterPaysRestreint(to_enum<Pays>(paysValeurEnum));
        }
        return true;
    }
    return false;
}

//! Méthode qui ajoute un film avec un string comportant les attributs du film
//! \param ligne                Le string comportant les attributs du film
//! \param gestionnaireAuteurs  Le gestionnaire des auteurs. Nécessaire pour associer un film à un
//!                             auteur.
//! \return                     Un bool représentant si l'opération est un succès
bool Librairie::lireLigneFilm(const std::string& ligne, GestionnaireAuteurs& gestionnaireAuteurs)
{
    std::istringstream stream(ligne);
    std::string nomFilm;
    unsigned int anneeSortie;
    int genreValeurEnum;
    int paysValeurEnum;
    bool estRestreintParAge;
    std::string nomAuteur;

    // Pour extraire tout ce qui se trouve entre "" dans un stream,
    // il faut faire stream >> std::quoted(variable)

    if (stream >> std::quoted(nomFilm) >> anneeSortie >> genreValeurEnum >> paysValeurEnum >>
        estRestreintParAge >> std::quoted(nomAuteur))
    {
        Auteur* auteur = gestionnaireAuteurs.chercherAuteur(nomAuteur);
        if (auteur == nullptr)
        {
            // Auteur non existant
            return false;
        }
        auteur->setNbFilms(auteur->getNbFilms() + 1);
        Film* film = new Film(nomFilm,
                              anneeSortie,
                              to_enum<Film::Genre>(genreValeurEnum),
                              to_enum<Pays>(paysValeurEnum),
                              estRestreintParAge,
                              auteur);

        *this += film;
        return true;
    }
    return false;
}

//! Méthode qui retourne l'index d'un film en cherchant son nom
//! \param nomFilm Le nom du film à trouver
//! \return        L'index du film. Retourne -1 si le film n'existe pas
int Librairie::trouverIndexFilm(const std::string& nomFilm) const
{
    for (int i = 0; i < films_.size(); i++)
    {
        if (films_[i]->getNom() == nomFilm)
        {
            return i;
        }
    }
    return FILM_INEXSISTANT;
}
