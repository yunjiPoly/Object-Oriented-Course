////////////////////////////////////////////////////////////////////////////////
/// TD4 Hiver 2020.
/// \file		PivoterMatrice.h
/// \authors   Par Yun Ji Liao(2017113) et Zhao Long Lui(2010407)
/// \authors   Basé sur un squelette écrit par  Nabil Dabouz
////////////////////////////////////////////////////////////////////////////////

#ifndef PIVOTER_MATRICE_H
#define PIVOTER_MATRICE_H

#include "def.h"

template <class M> class PivoterMatrice {
public:
	/**
	 * @brief constructeur par défaut de la classe
	 */
	PivoterMatrice();
	/**
	 * @brief constructeur par paramètre de la classe
	 */
	PivoterMatrice(M* matrice);
	/**
	 * @brief déconstructeur par paramètre de la classe
	 */
	~PivoterMatrice() = default;
	/**
	*@param direction de la rotation de la matrice
	 *@brief la méthode permet defaire une rotation d’une matrice d’un angle 𝜃
	 */
	void pivoterMatrice(Direction direction);

private:
	/**
	 * @brief trouver les coordonnées du point par rapport au centre de la matrice
	 * @param coords les coordonnées du point originales
	 */
	Coordonnees changerCoordonneesCentreMatrice(Coordonnees coords) const;
	/**
	 * @brief revenir au système précédent, trouver les coordonnées du point par
	 * rapport au premier élément de la matrice
	 * @param coords les coordonnées du point originales
	 */
	Coordonnees recupererCoordonnees(Coordonnees coords) const;
	M* matrice_;
};


template <class M> inline PivoterMatrice<M>::PivoterMatrice() {
	matrice_ = nullptr;
}

template <class M>
inline PivoterMatrice<M>::PivoterMatrice(M* matrice) : matrice_(matrice) {}

template <class M>
inline Coordonnees
PivoterMatrice<M>::changerCoordonneesCentreMatrice(Coordonnees coords) const {
	int facteur;
	facteur = matrice_->getHeight() / 2;
	return { coords.x - facteur, coords.y - facteur };

}

template <class M>
inline Coordonnees
PivoterMatrice<M>::recupererCoordonnees(Coordonnees coords) const {

	int facteur;
	facteur = matrice_->getHeight() / 2;
	return { coords.x + facteur, coords.y + facteur };

}

template <class M> inline void PivoterMatrice<M>::pivoterMatrice(Direction direction) {
	std::unique_ptr<M> temp = matrice_->clone();
	Coordonnees cooOG = { 0, 0 };
	Coordonnees cooTemp = { 0, 0 };
	int direct = static_cast<int>(direction);
	int gauche = static_cast<int>(Direction::Left);
	int droite = static_cast<int>(Direction::Right);
	for (int i = 0; i < matrice_->getHeight(); i++)
	{
		for (int j = 0; j < matrice_->getWidth(); j++)
		{
			cooOG = changerCoordonneesCentreMatrice({ i, j });
			if (gauche == direct)
			{
				cooTemp.x = -cooOG.y;
				cooTemp.y = cooOG.x;
			}
			if (droite == direct)
			{
				cooTemp.x = cooOG.y;
				cooTemp.y = -cooOG.x;
			}
			cooTemp = recupererCoordonnees(cooTemp);
			matrice_->ajouterElement(temp->operator()(cooTemp.y, cooTemp.x), j, i);
		}
	}
}

#endif
