// To do
#include <iostream>
//#include "GestionnaireSaison.h"
#include "../include/GestionnaireSaisons.h" // a changer
#define moinsun -1
// To do
GestionnaireSaisons::~GestionnaireSaisons()
{
    // To do
    saisons_.clear();
}

// To do
GestionnaireSaisons& GestionnaireSaisons::operator+=(std::unique_ptr<Saison> saison)
{
    // To do
    int index = trouverIndexSaison(saison->getNumSaison());
    if (index == moinsun || saison == nullptr)
        return *this;

    for (size_t i = index; i < saisons_.size(); i++)
    {
        saisons_[i] = std::move(saisons_[i + 1]);
    }
    saisons_.pop_back();
    saisons_.push_back(std::move(saison));
    sort(saisons_.begin(), saisons_.end(), Saison::SortByNumSaison());
    return *this;
}

// To do
GestionnaireSaisons& GestionnaireSaisons::operator-=(const unsigned int numSaison)
{
    // To do
    int index = trouverIndexSaison(numSaison);
    if (index == moinsun)
        return *this;

    for (size_t i = index; i < saisons_.size(); i++)
    {
        saisons_[i] = std::move(saisons_[i + 1]);
    }
    saisons_.pop_back();
    return *this;
}

// To do
void GestionnaireSaisons::ajouterEpisode(const unsigned int numSaison,
                                         std::unique_ptr<Episode> episode)
{
    // To do
    int index = trouverIndexSaison(numSaison);
    saisons_[index]->operator+=(std::move(episode)); // not too sure
    saisons_[index]->setNbEpisodesmax(saisons_[index]->getNbEpisodes() + 1);
}

// To do
void GestionnaireSaisons::retirerEpisode(const unsigned int numSaison,
                                         const unsigned int numEpisode)
{
    // To do
    int index = trouverIndexSaison(numSaison);
    saisons_[index]->operator-=(numEpisode); // not too sure
    saisons_[index]->setNbEpisodesmax(saisons_[index]->getNbEpisodes() - 1);
}

/// To do
size_t GestionnaireSaisons::trouverIndexSaison(const unsigned int numSaison) const
{
    // To do
    for (size_t i = 0; i < saisons_.size(); i++)
    {
        if (saisons_[i]->getNumSaison() == numSaison) 
        {
            return i;
        }
    }
    return moinsun;
}

// To do
Saison* GestionnaireSaisons::getSaison(const unsigned int numSaison) const
{
    // To do
    int index = trouverIndexSaison(numSaison);
    return saisons_[index].get();
    
}

// To do
size_t GestionnaireSaisons::getNbSaisons() const
{
    // To do
    return saisons_.size();
}
