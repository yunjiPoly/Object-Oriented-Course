////////////////////////////////////////////////////////////////////////////////
/// TD4 Hiver 2020.
/// \file		AgrandirMatrice.h
/// \authors   Par Yun Ji Liao(2017113) et Zhao Long Lui(2010407 
/// \authors   Basé sur un squelette écrit par  Nabil Dabouz
////////////////////////////////////////////////////////////////////////////////
#ifndef AGRANDIR_MATRICE_H
#define AGRANDIR_MATRICE_H

#include "def.h"

template <class M> class AgrandirMatrice {
public:
	/**
	 * @brief constructeur par défaut de la classe
	 */
	AgrandirMatrice();
	/**
	 * @brief constructeur par paramètre de la classe
	 */
	AgrandirMatrice(M* matrice);
	/**
	 * @brief déconstructeur par paramètre de la classe
	 */
	~AgrandirMatrice() = default;
	/**
	 * @brief trouver le point le plus proche du point (posX, posY) dans la matrice
	 * originale
	 * @param rapport, le rapport du redimensionnement de l'image
	 * @param posX, la colonne du point dans la nouvelle image
	 * @param posY, la ligne du point dans la nouvelle image
	 * @return coordonnées du point le plus proche
	 */
	Coordonnees trouverLePlusProcheVoisin(const unsigned int& rapport,
		size_t posY, size_t posX) const;
	/**
	 *@brief redimensionne l'image:Mettre à jour la largeur et la hauteur de la matrice.
	 *@param rapport, le rapport de redimensionnement de l'image
	 */
	void redimensionnerImage(const unsigned int& rapport);

private:
	M* matrice_;
};


template <class M> AgrandirMatrice<M>::AgrandirMatrice() {
	matrice_ = nullptr;
}
template <class M>
AgrandirMatrice<M>::AgrandirMatrice(M* matrice) : matrice_(matrice) {}

template <class M>
Coordonnees
AgrandirMatrice<M>::trouverLePlusProcheVoisin(const unsigned int& rapport,
	size_t posY, size_t posX) const {
	int X = static_cast<int>(posX) / rapport;
	int Y = static_cast<int>(posY) / rapport;
	return { X, Y};
}

template <class M> void AgrandirMatrice<M>::redimensionnerImage(const unsigned int& rapport) {
	std::unique_ptr<M> temp = matrice_->clone();
	matrice_->setHeight(matrice_->getHeight() * rapport);
	matrice_->setWidth(matrice_->getWidth() * rapport);

	for (int i = 0; i < matrice_->getHeight(); i++)
	{
		for (int j = 0; j < matrice_->getWidth(); j++)
		{
			Coordonnees coo = trouverLePlusProcheVoisin(rapport, j, i);
			matrice_->ajouterElement(temp->operator()(coo.y, coo.x), j, i);
		}
	}
}
#endif
