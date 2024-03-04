////////////////////////////////////////////////////////////////////////////////
/// TD4 Hiver 2020.
/// \file		pixel.cpp
/// \authors   Par Yun Ji Liao(2017113) et Zhao Long Lui(2010407)
/// \authors   Basé sur un squelette écrit par  Nabil Dabouz
////////////////////////////////////////////////////////////////////////////////
#include "Pixel.h"

/**
 * @brief constructeur par défaut de la classe
 */
Pixel::Pixel() : rouge_(0), vert_(0), bleu_(0) {}
/**
 * @brief constructeur par paramètres de la classe
 * @param rouge, l'élément R du pixel, entre 0 -> 255
 * @param vert, l'élément G du pixel, entre 0 -> 255
 * @param bleu, l'élément B du pixel, entre 0 -> 255
 */
Pixel::Pixel(uint8_t rouge, uint8_t vert, uint8_t bleu)
	: rouge_(rouge), vert_(vert), bleu_(bleu) {}
/**
 * operator = permet de remplacer les couleurs par les couleurs de pixel dans le parametre.
 */
void Pixel::operator=(const Pixel& pixel) {
	rouge_ = pixel.rouge_;
	bleu_ = pixel.bleu_;
	vert_ = pixel.vert_;
}
/**
 * @brief fixer l'attribut rouge_ du pixel oar le parametre
 */
void Pixel::setRouge(int rouge) {
	rouge_ = rouge > 255 ? 255 : 0;
	rouge_ = 0 <= rouge && rouge <= 255 ? rouge : rouge_;
}
/**
*@brief fixer l'attribut vert_ du pixel oar le parametre
*/
void Pixel::setVert(int vert) {
	vert_ = vert > 255 ? 255 : 0;
	vert_ = 0 <= vert && vert <= 255 ? vert : vert_;
}
/**
*@brief fixer l'attribut bleu_ du pixel oar le parametre
*/
void Pixel::setBleu(int bleu) {
	bleu_ = bleu > 255 ? 255 : 0;
	bleu_ = 0 <= bleu && bleu <= 255 ? bleu : bleu_;
}
/**
 * @brief retourn l'attribut rouge_ du pixel
 * @return rouge_ du type uint8_t
 */
uint8_t Pixel::getRouge() const { return rouge_; }
/**
 * @brief retourn l'attribut vert_ du pixel
 * @return vert_ du type uint8_t
 */
uint8_t Pixel::getVert() const { return vert_; }
/**
 * @brief retourn l'attribut bleu_ du pixel
 * @return bleu_ du type uint8_t
 */
uint8_t Pixel::getBleu() const { return bleu_; }
/**
 * Operator << qui permet d'afficher le pixel
 */
std::ostream& operator<<(std::ostream& os, Pixel pixel) {
	// TO DO
	os << std::hex << std::uppercase;
	os << '#' << std::setfill('0') << std::setw(2) << int(pixel.getRouge()) << ' ' << std::setfill('0') << std::setw(2) << int(pixel.getVert()) << ' ' << std::setfill('0') << std::setw(2) << int(pixel.getBleu());
	return os;
}
/**
 * Operator << qui permet de lire le pixel
 */
std::istream& operator>>(std::istream& is, Pixel& pixel) {
	int rouge, vert, bleu;
	if ((is >> rouge >> vert >> bleu)) {
		pixel.setRouge(rouge);
		pixel.setVert(vert);
		pixel.setBleu(bleu);
	}
	return is;
}