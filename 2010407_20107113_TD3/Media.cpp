//#include "Media.h"
#include "../include/Media.h"
#include <fstream>
#include <iomanip>
#include <sstream>
#include <iostream>

namespace
{
    //! Fonction qui convertit le enum Media::Genre en string
    //! \param genre    Le genre à convertir
    //! \return         Le string qui représente le enum
    const std::string& getGenreString(Media::Genre genre)
    {
        static const std::string NOMS_GENRES[] = {"Action",
                                                  "Aventure",
                                                  "Comedie",
                                                  "Horreur",
                                                  "Romance"};

        auto index = enum_value(genre);
        assert(valid_as_enum<Media::Genre>(index));
        return NOMS_GENRES[index];
    }

    //! Fonction qui convertit le enum Pays en string
    //! \param pays     Le pays à convertir
    //! \return         Le string qui représente le enum
    const std::string& getPaysString(Pays pays)
    {
        static const std::string NOMS_PAYS[] = {"Bresil",
                                                "Canada",
                                                "Chine",
                                                "EtatsUnis",
                                                "France",
                                                "Japon",
                                                "RoyaumeUni",
                                                "Russie",
                                                "Mexique"};
        auto index = enum_value(pays);
        assert(valid_as_enum<Pays>(index));
        return NOMS_PAYS[index];
    }
} // namespace

Media::Media(Auteur* auteur, Media::TypeMedia typeMedia) : nom_("unknown"), anneeDeSortie_(0), genre_(to_enum<Genre>(0)), pays_(to_enum<Pays>(0)), estRestreintParAge_(0), auteur_(auteur), typeMedia_(typeMedia), paysRestreints_(std::vector<Pays>(0))
{
}


Media::Media(const std::string& nom, unsigned int anneeDeSortie, Genre genre, Pays pays,
    bool estRestreintParAge, Auteur* auteur, Media::TypeMedia typeMedia) : nom_(nom), anneeDeSortie_(anneeDeSortie), genre_(genre), pays_(pays), estRestreintParAge_(estRestreintParAge), auteur_(auteur), typeMedia_(typeMedia), paysRestreints_(std::vector<Pays>(0))
{
}


Media::Media(const Media& serie)
{
    nom_ = serie.nom_;
    anneeDeSortie_ = serie.anneeDeSortie_;
    genre_ = serie.genre_;
    pays_ = serie.pays_;
    estRestreintParAge_ = serie.estRestreintParAge_;
    auteur_ = serie.auteur_;
    typeMedia_ = serie.typeMedia_;
    for (size_t i = 0; i < serie.paysRestreints_.size(); i++)
    {
        paysRestreints_[i] = serie.paysRestreints_[i];
    }
}


// To do
Media::~Media()
{
    // To do
    nom_ = "unknown";
    anneeDeSortie_ = 0;
    genre_ = to_enum<Genre>(0);
    pays_ = to_enum<Pays>(0);
    estRestreintParAge_ = 0;
    auteur_ = nullptr;
    typeMedia_ = to_enum<TypeMedia>(0);
    paysRestreints_.clear();
}

// To do
//! Méthode qui ajoute un pays à liste des pays restreints du film
//! \param pays Pays à ajouter à la liste
void Media::ajouterPaysRestreint(Pays pays)
{
    // To do
    paysRestreints_.push_back(pays);
}

// To do
//! Méthode qui supprime les pays restreints
void Media::supprimerPaysRestreints()
{
    // To do
    paysRestreints_.clear();
}

// To do
//! Méthode qui retourne si un pays est dans la liste des pays restreints du film
//! \param pays Le pays à chercher dans la liste des pays restreints
//! \return     Un bool représentant si le pays se trouve dans la liste des pays restreints
bool Media::estRestreintDansPays(Pays pays) const
{
    // To do
    for (std::size_t i = 0; i < paysRestreints_.size(); i++)
    {
        if (paysRestreints_[i] == pays)
        {
            return true;
        }
    }
    return false;
}

// To do
// Méthode qui retourne si le film est restreint aux moins de 16 ans
// \return Un bool représentant si le film est restreint aux moins de 16 ans
bool Media::estRestreintParAge() const
{
    return estRestreintParAge_;
}

// To do
//! opérateur qui affiche le film
//! \param os Le stream dans lequel afficher
//! \param Film le film que l'on veut afficher
std::ostream& Media::afficher(std::ostream& os) const
{
    // To do
    os << nom_ << "\n\tDate de sortie: " << anneeDeSortie_
        << "\n\tGenre: " << getGenreString(genre_) << "\n\tAuteur: " << auteur_->getNom()
        << "\n\tPays: " << getPaysString(pays_)
        << (paysRestreints_.size() == 0 ? "\n\tAucun pays restreint." : "\n\tPays restreints:");

    for (std::size_t i = 0; i < paysRestreints_.size(); i++)
    {
        os << "\n\t\t" << getPaysString(paysRestreints_[i]);
    }
    os << '\n';

    return os;
}

// To do
std::ostream& operator<<(std::ostream& os, const Media& media)
{
    // To do
    return media.afficher(os);;
}

Auteur* Media::getAuteur()
{
    return auteur_;
}

// To do
// Méthode qui retourne le genre du film
// \return Le genre du film
Media::Genre Media::getGenre() const
{
    // To do
    return genre_;
}

// To do
// Méthode qui retourne le nom du film
// \return Le nom du film
const std::string& Media::getNom() const
{
    // To do
    return nom_;
}

// To do
Media::TypeMedia Media::getTypeMedia() const
{
    // To do
    return typeMedia_;
}

// To do
std::istream& Media::lire(std::istream& is)
{
    // To do
    std::string ligne;
    std::getline(is, ligne);
    std::istringstream stream(ligne);
    int media, genre, pays;
    stream >> media >> *auteur_ >> std::quoted(nom_) >> anneeDeSortie_ >> genre >> pays >> estRestreintParAge_;
    typeMedia_ = to_enum<Media::TypeMedia>(media);
    genre_ = to_enum<Genre>(genre);
    pays_ = to_enum<Pays>(pays);

    return is;
}

// To do
std::istream& operator>>(std::istream& is, Media& media)
{ 
    return media.lire(is);;
}

// To do
std::unique_ptr<Media> Media::clone() const
{
    // To do
    return std::make_unique<Media>(*this);
}