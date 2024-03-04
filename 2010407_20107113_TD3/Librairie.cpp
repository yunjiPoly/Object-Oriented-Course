//#include "Librairie.h"
#include "../include/Librairie.h"
#define moinsun -1


// To do
//! Constructeur de copie de la classe Librairie
Librairie::Librairie(const Librairie& librairie)
{
    // To do
    for (size_t i = 0; i < librairie.medias_.size(); i++)
    {
        medias_.push_back(std::make_unique<Media>(*librairie.medias_[i]));
    }
}

// To do
//! Operateur d'egalite qui assigne une librairie a une autre.
//! /param Librairie la librairie a copier.
Librairie& Librairie::operator=(const Librairie& librairie)
{
    // To do
    if (&librairie == this)
        return *this;

    medias_.clear();

    for (size_t i = 0; i < librairie.medias_.size(); i++)
    {
        medias_.push_back(std::make_unique<Media>(*librairie.medias_[i]));
    }

    return *this;
}

//! Destructeur de la classe Librairie
Librairie::~Librairie()
{
    medias_.clear();
}

// To do
//! Méthode qui retourne un film comportant le même nom que celui envoyé en paramètre
//! \param nomFilm Le nom du film à chercher
//! \return        Un pointeur vers le film. Nullptr si le film n'existe pas
Film* Librairie::chercherFilm(const std::string& nomFilm)
{
    // To do
    int index = trouverIndexMedia(nomFilm);
    if (chercherMedia(nomFilm, Media::TypeMedia::Film) == nullptr)
    {
        return nullptr;
    }
    return dynamic_cast<Film*>(medias_[index].get());
}

// Methode qui cherche le nom dans la parametre dans la liste de serie
// @return un pointeur le media si trouve 
// @return un pointeur null si pas trouve
Serie* Librairie::chercherSerie(const std::string& nomSerie)
{
    // To do
    int index = trouverIndexMedia(nomSerie);
    if (chercherMedia(nomSerie, Media::TypeMedia::Serie) == nullptr)
    {
        return nullptr;
    }
    return dynamic_cast<Serie*>(medias_[index].get());
}

//  méthode ajoute une saison à la série dont le nom est reçu en paramètre
void Librairie::ajouterSaison(const std::string& nomSerie, std::unique_ptr<Saison> saison)
{
    // To do
    int indexSerie = trouverIndexMedia(nomSerie);
    if (indexSerie == moinsun)
    {
        return;
    }
    if (medias_[indexSerie].get()->getTypeMedia() == Media::TypeMedia::Serie)
    {

        Serie* uneSerie = dynamic_cast<Serie*>(medias_[indexSerie].get());
        *uneSerie += move(saison);
    }
}

// La méthode retire une saison de la série dont le nom est reçu en paramètre
void Librairie::retirerSaison(const std::string& nomSerie, unsigned int numSaison)
{
    // To do
    int indexSerie = trouverIndexMedia(nomSerie);
    if (indexSerie == moinsun)
    {
        return;
    }
    if (medias_[indexSerie].get()->getTypeMedia() == Media::TypeMedia::Serie)
    {
        Serie* uneSerie = dynamic_cast<Serie*>(medias_[indexSerie].get());
        size_t max = uneSerie->getNbSaisons();
        *uneSerie -= numSaison;
    }
}

// La méthode ajoute un épisode à la saison de la série dont le nom et le numéro
//sont reçus en paramètre
void Librairie::ajouterEpisode(const std::string& nomSerie, unsigned int numSaison,
                               std::unique_ptr<Episode> episode)
{
    // To do
    int index = trouverIndexMedia(nomSerie);
    if (medias_[index].get()->getTypeMedia() == Media::TypeMedia::Serie)
    {
        dynamic_cast<GestionnaireSaisons*>(medias_[index].get())->ajouterEpisode(numSaison, move(episode));
    }
}


void Librairie::retirerEpisode(const std::string& nomSerie, unsigned int numSaison,
                               unsigned int numEpisode)
{
    // To do
    int index = trouverIndexMedia(nomSerie);
    if (medias_[index].get()->getTypeMedia() == Media::TypeMedia::Serie)
    {
        dynamic_cast<GestionnaireSaisons*>(medias_[index].get())->retirerEpisode(numSaison, numEpisode);
    }
}

//! Méthode qui charge les films à partir d'un fichier.
//! \param nomFichier           Le nom du fichier à lire.
//! \param gestionnaireAuteurs  Le gestionnaire des auteurs. Nécessaire pour associer un film à un
//! auteur.
//! \return                     Un bool représentant si le chargement a été un succès.
bool Librairie::chargerMediasDepuisFichier(const std::string& nomFichier,
                                           GestionnaireAuteurs& gestionnaireAuteurs)
{
    // To do
    std::ifstream fichier(nomFichier);
    if (fichier)
    {
        // Supprimer les vieux films avant de lire les nouveaux
        medias_.clear();

        std::string ligne;
        while (std::getline(fichier, ligne))
        {
            if (lireLigneMedia(ligne, gestionnaireAuteurs) == false)
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

//! Méthode qui charge les restrictions des series à partir d'un fichier.
//! \param nomFichier           Le nom du fichier à lire.
//! \return                     Un bool représentant si le chargement a été un succès.
bool Librairie::chargerRestrictionsDepuisFichiers(const std::string& nomFichier)
{
    std::ifstream fichier(nomFichier);
    if (fichier)
    {
        for (size_t i = 0; i < medias_.size(); i++)
            medias_[i]->supprimerPaysRestreints();

        std::string ligne;
        while (getline(fichier, ligne))
            if (!lireLigneRestrictions(ligne))
                return false;

        return true;
    }
    std::cerr << "Le fichier " << nomFichier
              << " n'existe pas. Assurez vous de le mettre au bon endroit.\n";
    return false;
}

// getter
// @returne le nombre de medias
size_t Librairie::getNbMedias() const
{
    // To do
    return medias_.size();
}

// operator << affiche la liste des medias
std::ostream& operator<<(std::ostream& os, const Librairie& librairie)
{
    // To do
    for (std::size_t i = 0; i < librairie.medias_.size(); i++)
    {
        os << *(librairie.medias_[i]) << std::endl;
    }

    return os;
}

// methode qui cherche l'index par le nom de media
// @return l'index si trouve 
size_t Librairie::trouverIndexMedia(const std::string& nomMedia) const
{
    // To do
    for (size_t i = 0; i < medias_.size(); i++)
    {
        if (medias_[i]->getNom() == nomMedia)
            return i;
    }
    return moinsun;
}

// methode ajouter un pointeur media au vector medias
Librairie& Librairie::operator+=(std::unique_ptr<Media> media)
{
    // To do
    if (media == nullptr)
    {
        return *this;
    }
    medias_.push_back(std::move(std::make_unique<Media>(media)));
}

// methode retire le medias de la liste s'elle la trouve
Librairie& Librairie::operator-=(const std::string& nomMedia)
{
    // To do
    for (size_t i = 0; i < medias_.size() - 1; i++)
    {
        if (medias_[i]->getNom() == nomMedia)
        {
            medias_[i] = std::move(medias_[i + 1]);
            medias_.pop_back();
            return *this;
        }
    }
    return *this;
}

// To do
Media* Librairie::chercherMedia(const std::string& nomMedia, Media::TypeMedia typeMedia)
{
    // To do
    int index = trouverIndexMedia(nomMedia);
    if (index != moinsun && medias_[index]->getTypeMedia() == typeMedia)
    {
        return medias_[index].get();
    }
    return nullptr;
}

// Méthode privée qui cherche un média dans la liste de media
bool Librairie::lireLigneRestrictions(const std::string& ligne)
{
    // To do
    std::istringstream stream(ligne);
    std::string nomFilm;
    int typMedia;
    // Pour extraire tout ce qui se trouve entre "" dans un stream,
    // il faut faire stream >> std::quoted(variable)
    if (stream >> typMedia >> std::quoted(nomFilm))
    {
        Media* media = chercherMedia(nomFilm, Media::TypeMedia::Film);
        if (media == nullptr)
        {
            // Film n'existe pas
            return false;
        }

        int paysValeurEnum;
        while (stream >> paysValeurEnum)
        {
            media->ajouterPaysRestreint(to_enum<Pays>(paysValeurEnum));
        }
        
        return true;
    }
    return false;
}

// To do
bool Librairie::lireLigneMedia(const std::string& ligne, GestionnaireAuteurs& gestionnaireAuteurs)
{
    lireLigneMediaFunction fonctionLireligne[] = {&Librairie::lireLigneFilm,
                                                  &Librairie::lireLigneSerie,
                                                  &Librairie::lireLigneSaison,
                                                  &Librairie::lireLigneEpisode};
    std::istringstream stream(ligne);
    int typeMediaValeurEnum;

    if (stream >> typeMediaValeurEnum)
        return invoke(fonctionLireligne[typeMediaValeurEnum], *this, stream, gestionnaireAuteurs);

    return false;
}

// To do
const std::vector<std::unique_ptr<Media>>& Librairie::getMedias() const
{
    // To do
    return medias_;
}

// To do
bool Librairie::lireLigneEpisode(std::istream& is, GestionnaireAuteurs&)
{
    // To do
    std::string ligne;
    std::istringstream stream(ligne);
    std::string nomEpisode;
    int typMedia;
    unsigned int numero;
    unsigned int numSaison;
    std::string duree;
    std::string nomDeLaSerie;

    std::getline(is, ligne);

    if (stream >> typMedia >> numero >> std::quoted(nomEpisode) >> duree >> std::quoted(duree) >> std::quoted(nomDeLaSerie) >> numSaison)
    {
        auto episode = std::make_unique<Episode>(numero, nomEpisode, duree);
        if (episode == nullptr)
        {
            // Auteur non existant
            return false;
        }

        ajouterEpisode(nomDeLaSerie, numSaison, std::make_unique<Episode>(episode));
        return true;
    }
    return false;

}

// To do
bool Librairie::lireLigneSaison(std::istream& is, GestionnaireAuteurs&)
{
    // To do
    std::string ligne;
    std::istringstream stream(ligne);
    std::string nomSaison;
    int typMedia;
    unsigned int numero;
    unsigned int nbEpisode;

    std::getline(is, ligne);

    if (stream >> typMedia >> numero >> nbEpisode >> std::quoted(nomSaison))
    {
        auto saison = std::make_unique<Saison>(numero, nbEpisode);
        if (saison == nullptr)
        {
            // Auteur non existant
            return false;
        }

        ajouterSaison(nomSaison, std::make_unique<Saison>(saison));
        return true;
    }
    return false;
}

// To do
bool Librairie::lireLigneSerie(std::istream& is, GestionnaireAuteurs& gestionnaireAuteurs)
{
    // To do
    std::string ligne;
    std::istringstream stream(ligne);
    std::string nomSerie;
    int typMedia;
    unsigned int anneeSortie;
    int genreValeurEnum;
    int paysValeurEnum;
    bool estRestreintParAge;
    std::string nomAuteur;

    std::getline(is, ligne);

    if (stream >> typMedia >> std::quoted(nomAuteur) >> std::quoted(nomSerie) >> anneeSortie >> genreValeurEnum >> paysValeurEnum >> estRestreintParAge)
    {
        Auteur* auteur = gestionnaireAuteurs.chercherAuteur(nomAuteur);
        if (auteur == nullptr)
        {
            // Auteur non existant
            return false;
        }
        auteur->setNbMedias(auteur->getNbMedias() + 1);
        std::unique_ptr<Serie> serie = std::make_unique<Serie>(nomSerie, anneeSortie, to_enum<Film::Genre>(genreValeurEnum), to_enum<Pays>(paysValeurEnum), estRestreintParAge, auteur);
        operator+=(std::move(serie));
        return true;
    }
    return false;
}

// To do
bool Librairie::lireLigneFilm(std::istream& is, GestionnaireAuteurs& gestionnaireAuteurs)
{
    // To do
    std::string ligne;
    std::istringstream stream(ligne);
    std::string nomFilme;
    int typMedia;
    unsigned int anneeSortie;
    int genreValeurEnum;
    int paysValeurEnum;
    bool estRestreintParAge;
    std::string nomAuteur;
    std::string duree;

    std::getline(is, ligne);

    if (stream >> typMedia >> std::quoted(nomAuteur) >> std::quoted(nomFilme) >> anneeSortie >> genreValeurEnum >> paysValeurEnum >> estRestreintParAge >> duree)
    {
        Auteur* auteur = gestionnaireAuteurs.chercherAuteur(nomAuteur);
        if (auteur == nullptr)
        {
            // Auteur non existant
            return false;
        }
        auteur->setNbMedias(auteur->getNbMedias() + 1);
        std::unique_ptr<Film> film = std::make_unique<Film>(nomFilme, anneeSortie, to_enum<Film::Genre>(genreValeurEnum), to_enum<Pays>(paysValeurEnum), estRestreintParAge, auteur, duree);
        operator+=(std::move(film));
        return true;
    }
    return false;
}

// To do
size_t Librairie::getNbFilms() const
{
    // To do
    int compteur = 0;
    for (size_t i = 0; i < medias_.size(); i++)
    {
        if (medias_[i]->getTypeMedia() == Media::TypeMedia::Film)
            compteur++;
    }
    return compteur;
}

// To do
size_t Librairie::getNbSeries() const
{
    // To do
    int compteur = 0;
    for (size_t i = 0; i < medias_.size(); i++)
    {
        if (medias_[i]->getTypeMedia() == Media::TypeMedia::Serie)
            compteur++;
    }
    return compteur;
}

// return le nombre de saison 
size_t Librairie::getNbSaisons(const std::string& nomSerie) const
{
    // To do
    int index = trouverIndexMedia(nomSerie);

    if (medias_[index]->getTypeMedia() == Media::TypeMedia::Saison && dynamic_cast<Serie*>(medias_[index].get()))
    {
        return dynamic_cast<Serie*>(medias_[index].get())->getNbSaisons();
    }

    return 0;
}

// return le nombre de episode
size_t Librairie::getNbEpisodes(const std::string& nomSerie, const unsigned int numSaison) const
{
    // To do
    int index = trouverIndexMedia(nomSerie);
    if (medias_[index]->getTypeMedia() == Media::TypeMedia::Episode && dynamic_cast<Saison*>(medias_[index].get()))
    {
        return dynamic_cast<Saison*>(medias_[index].get())->getNbEpisodes();
    }
    return 0;
}