////////////////////////////////////////////////////////////////////////////////
/// TD4 Hiver 2020.
/// \file		Matrice.h
/// \authors   Par Yun Ji Liao(2017113) et Zhao Long Lui(2010407)
/// \authors   Basé sur un squelette écrit par  Nabil Dabouz
////////////////////////////////////////////////////////////////////////////////
#ifndef MATRICE_H
#define MATRICE_H

#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <vector>

template <typename T> class Matrice {

public:
	/**
	* @brief constructeur par défaut de la classe
	*/
	Matrice();
	/**
	* @brief deconstructeur par défaut de la classe
	*/
	~Matrice() = default;
	/**
	*@return l’élément se trouvant à la ligne posY et la colonne posX du tableau elements_.
	*/
	T operator()(const size_t& posY, const size_t& posX) const;
	/*
	*Charge la matrice à partir du fichier passé en paramètre. 
	*/
	bool chargerDepuisFichier(const std::string& nomFichier);
	/*
	*La méthode lit l’élément à partir de la chaine de caractères elementFichier puis l’ajoute dans la matrice
	*Retourne vrai si la lecture est faite.
	*/
	bool lireElement(const std::string& elementFichier, const size_t& posY,
		const size_t& posX);
	/**
	*La méthode ajoute l’élément passé en paramètre dans la position correspondante.
	*Retourne true si l’ajout a été effectué.	
	*/
	bool ajouterElement(T element, const size_t& posY, const size_t& posX);
	/**
	*Retourne un pointeur unique de la matrice vers une copie de la matrice.
	*/
	std::unique_ptr<Matrice<T>> clone() const;
	/**
	*@brief fixer l'attribut height_ du pixel oar le parametre
	*/
	void setHeight(size_t height);
	/**
	*@brief fixer l'attribut width_ du pixel oar le parametre
	*/
	void setWidth(size_t width);
	/**
	 * @brief retourne le nombre de lignes de la matrice
	 * @return l'attribut height_ de l'objet
	 */
	size_t getHeight() const;
	/**
	* @brief retourne le nombre de colonne de la matrice
	* @return l'attribut width_ de l'objet
	*/
	size_t getWidth() const;

private:
	std::vector<std::vector<T>> elements_;
	size_t height_;
	size_t width_;
};

namespace
{
	static constexpr int CAPACITE_MATRICE = 100;
}


template <typename T> inline Matrice<T>::Matrice() : elements_(CAPACITE_MATRICE, std::vector<T>(CAPACITE_MATRICE)), height_(0), width_(0) {
}

template <typename T> inline size_t Matrice<T>::getHeight() const {
	return height_;
}

template <typename T> inline size_t Matrice<T>::getWidth() const {
	return width_;
}


template <typename T> T Matrice<T>::operator()(const size_t& posY, const size_t& posX) const {
	if (posY > height_ || posX > width_)
	{
		return T();
	}
	return elements_[posY][posX];
}

template <typename T> bool Matrice<T>::ajouterElement(T element, const size_t& posY, const size_t& posX) {
	if (posY <= CAPACITE_MATRICE && posX <= CAPACITE_MATRICE && posY >= 0 && posX >= 0) {
		elements_[posY][posX] = element;
		return true;
	}
	return false;
}

template <typename T> bool Matrice<T>::lireElement(const std::string& elementFichier, const size_t& posY, const size_t& posX) {
	std::istringstream stream(elementFichier);
	T element;
	if (stream >> element)
	{
		return ajouterElement(element, posY, posX);
	}
	return false;
}

template <typename T> bool Matrice<T>::chargerDepuisFichier(const std::string& nomFichier) {
	std::ifstream stream(nomFichier);
	std::string element;
	int posX = 0;
	int posY = 0;
	if (stream) {
		while (std::getline(stream, element)) {
			if (element == "L") {
				height_ = ++posY;
				posX = 0;
			}
			else
			{
				width_ = ++posX;
				//width_ = ++posX > width_ ? posX : width_;
				if (!lireElement(element, posY - 1, posX - 1))
					return false;
			}
		}
		return true;
	}
	return false;
}

template <typename T> std::unique_ptr<Matrice<T>> Matrice<T>::clone() const {
	return std::make_unique<Matrice<T>>(*this);
}

template <typename T> void Matrice<T>::setHeight(size_t height) {
	height_ = height == CAPACITE_MATRICE + 10 ? CAPACITE_MATRICE : height;
}

template <typename T> void Matrice<T>::setWidth(size_t width) {
	width_ = width;
}
#endif
