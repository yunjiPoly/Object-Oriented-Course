#ifndef GESTIONNAIREAUTEURS_H
#define GESTIONNAIREAUTEURS_H

#include <string>
#include "Auteur.h"
/**
*represente tous les informations des auteurs existants
*/
class GestionnaireAuteurs
{
public:
	/**
	* inilialiser GestionnaireAuteur
	* c'est un constructeur
	*/
	GestionnaireAuteurs();
	/**
	* ajouter un auteur à la liste des auteurs
	* @return si c'est ajoute
	*/
	bool ajouterAuteur(const Auteur& auteur);
	/**
	* chercher un auteur à la liste des auteurs
	* @return si c'est trouve
	*/
	Auteur* chercherAuteur(const std::string& nomAuteur);
	/**
	* ouvrir le fichier, et envoyer le fichier à la
	* fonction lireLigneAuteur.Si une erreur se produit dans lireLigneAuteur,
	* interrompre la fonction et retourner false.Retourner true aucune erreur ne
	* s’est produite.
	*/

	bool chargerDepuisFichier(const std::string& nomFichier);

	void afficher(std::ostream& stream) const;
	/**
	* Gets le nombre de auteur
	* @return ca
	*/
	std::size_t getNbAuteurs() const;

	static constexpr std::size_t NB_AUTEURS_MAX = 16;

private:
	bool lireLigneAuteur(const std::string& ligne);

	Auteur auteurs_[NB_AUTEURS_MAX];
	std::size_t nbAuteurs_;
};

#endif // GESTIONNAIREAUTEURS_H