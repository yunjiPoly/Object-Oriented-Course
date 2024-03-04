
//#include "Film.h"
#include "../include/Film.h"

Film::Film(Auteur* auteur) : Media("unknown", 0, Genre::first_, Pays::first_, false, auteur, Media::TypeMedia::first_), duree_("unknow")

{
}


Film::Film(const std::string& nom, unsigned int anneeDeSortie, Genre genre, Pays pays,
    bool estRestreintParAge, Auteur* auteur, const std::string& duree) : Media(nom, anneeDeSortie, genre, pays, estRestreintParAge, auteur, Media::TypeMedia::first_), duree_(duree)

{
}


std::ostream& Film::afficher(std::ostream& os) const
{
    Media::afficher(os);
    os << duree_;
    
    return os;
}


std::istream& Film::lire(std::istream& is)
{

    Media::lire(is);
    is >> duree_;

    return is;
}


std::unique_ptr<Media> Film::clone() const
{
    return std::make_unique<Media>(*this);
}
