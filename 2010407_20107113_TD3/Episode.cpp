//#include "Episode.h"
#include <iostream>
#include "../include/Episode.h" // a changer

Episode::Episode() : nom_("unknown"), duree_("unknown"), numEpisode_(0)
{
}

Episode::Episode(unsigned int numEpisode, const std::string& nom, const std::string& duree) :
	nom_(nom), duree_(duree), numEpisode_(numEpisode)
{
}


bool Episode::operator==(unsigned int numEpisode)
{
	if (numEpisode_ == numEpisode)
	{
		return true;
	}
	return false;
	
}/*
L’opérateur permet d’afficher tous les attributs de l’épisode
o L’opérateur doit pouvoir être appelé en cascade.*/

bool operator==(unsigned int numEpisode, Episode& episode) 
{
	return (episode.numEpisode_ == numEpisode);
}

std::ostream& operator<<(std::ostream& os, const Episode& episode)
{
	os << "Nom: " << episode.nom_ << " duree: " << episode.duree_
		<< " | numEpisode " << episode.numEpisode_;
	return os;
	
}

/*
 L’opérateur permet d’initialiser tous les attributs de l’épisode
o L’opérateur doit pouvoir être appelé en cascade.*/

std::istream& operator>>(std::istream& is, Episode& episode)
{
	is >> episode.nom_ >> episode.duree_ >> episode.numEpisode_;

	return is;
}

unsigned int Episode::getNumEpisode() const
{
	return numEpisode_;
}

std::string Episode::getnom() const
{
	return nom_;
}

std::string Episode::getduree() const {
	return duree_;
}
