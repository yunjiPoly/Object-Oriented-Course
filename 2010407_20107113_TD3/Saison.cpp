//#include "Saison.h"
#include <iostream>
#include "../include/Saison.h" // a changer
#define moinsun -1

Saison::Saison() :numSaison_(0), nbEpisodesmax_(0), episodes_(std::vector<std::unique_ptr<Episode>>())
{
}

Saison::Saison(unsigned int numSaison, unsigned int nbEpisodemax) : numSaison_(numSaison), nbEpisodesmax_(nbEpisodemax), episodes_(std::vector<std::unique_ptr<Episode>>())
{
}

Saison::Saison(const Saison& saison)
{
	for (size_t i = 0; i < saison.episodes_.size(); i++)
	{
		episodes_.push_back(std::make_unique<Episode>(*saison.episodes_[i]));
	}
	numSaison_ = saison.numSaison_;
	nbEpisodesmax_ = saison.nbEpisodesmax_;
}

Saison::~Saison()
{
	episodes_.clear();
}

Saison& Saison::operator+=(std::unique_ptr<Episode> episode)
{
	int index = trouverIndexEpisode(episode->getNumEpisode());
	if (index == moinsun || episode == nullptr) 
		return *this;

	for (size_t i = index; i < nbEpisodesmax_; i++)
	{
		episodes_[i] = std::move(episodes_[i + 1]);
	}
	episodes_.pop_back();
	episodes_.push_back(std::move(episode));
	sort(episodes_.begin(), episodes_.end(), Episode::SortByNumEpisode());
	return *this;
}

Saison& Saison::operator-=(unsigned int numEpisode)
{
	int tp3 = trouverIndexEpisode(numEpisode);
	if (tp3 == moinsun)
		return *this;

	for (size_t i = tp3; i < nbEpisodesmax_; i++)
	{
		episodes_[i] = std::move(episodes_[i + 1]);
	}
	episodes_.pop_back();
	return *this;
}

bool operator==(unsigned int numSaison, Saison& saison) 
{
	if (saison.numSaison_ == numSaison) {
		return true;
	}
	return false;
}

bool Saison::operator==(unsigned int numSaison)
{
	if (numSaison_ == numSaison) {
		return true;
	}
	return false;
}

std::ostream& operator<<(std::ostream& os, const Saison& saison)
{
	for (size_t i = 0; i < saison.episodes_.size(); i++)
	{

		os << "Episode" << *saison.episodes_[i];
		os << '\n';
	}
	os << "numSaison:" << saison.numSaison_ << "NbEpisodemax:" << saison.nbEpisodesmax_;
	return os;
}


std::istream& operator>>(std::istream& is, Saison& saison)
{
	is >> saison.numSaison_ >> saison.nbEpisodesmax_;
	return is;

}

unsigned int Saison::getNumSaison() const
{
	return numSaison_;
}

size_t Saison::getNbEpisodes() const
{
	return nbEpisodesmax_;
}

size_t Saison::trouverIndexEpisode(unsigned int numEpisode)
{
	for (size_t i = 0; i < episodes_.size(); i++)
	{
		if (episodes_[i]->getNumEpisode() == numEpisode)
		{
			return i;
		}
	}
	return moinsun;
}

void Saison::setNbEpisodesmax(unsigned int nbEpisodesmax)
{
	nbEpisodesmax_ = nbEpisodesmax;
}