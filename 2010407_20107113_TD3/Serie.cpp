// To do
//#include "Serie.h"
#include "../include/Serie.h"


// To do              Pointeur vers l'auteur du serie
Serie::Serie(Auteur* auteur): Media("unknown", 0, to_enum<Genre>(0), to_enum<Pays>(0), false, auteur, to_enum<TypeMedia>(0))
    // To do
{
}

// To do
Serie::Serie(const std::string& nom, unsigned int anneeDeSortie, Genre genre, Pays pays,
    bool estRestreintParAge, Auteur* auteur) : Media(nom, anneeDeSortie, genre, pays, estRestreintParAge, auteur, to_enum<TypeMedia>(0))
    // To do
{
}

// To do
Serie::Serie(const Serie& serie): Media(serie.nom_, serie.anneeDeSortie_, serie.genre_, serie.pays_, serie.estRestreintParAge_, serie.auteur_, serie.typeMedia_)
    // To do
{
    // To do
    for (size_t i = 0; i < serie.paysRestreints_.size(); i++)
    {
        paysRestreints_[i] = serie.paysRestreints_[i];
    }
    for (size_t i = 0; i < serie.saisons_.size(); i++)
    {
        saisons_.push_back(std::make_unique<Saison>(*serie.saisons_[i]));
    }
}

// To do
std::ostream& Serie::afficher(std::ostream& os) const
{
    // To do
    Media::afficher(os);

    return os;
}

// To do
std::unique_ptr<Media> Serie::clone() const
{
    // To do
    return std::make_unique<Media>(*this);
}