#ifndef GESTIONNAIREAUTEURS_H
#define GESTIONNAIREAUTEURS_H

#include <string>
#include "Auteur.h"
#include <vector>
/**
 *represente tous les informations des auteurs existants
 */
class GestionnaireAuteurs
{
public:
    /*
	*constructeur par default de la classe gestionnaireAuteur
	*/
    GestionnaireAuteurs();
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
	/*Afficher la liste de vecteur des auteurs
	\param stream Le stream dans lequel afficher
	*/
    friend std::ostream& operator<<(std::ostream& stream, GestionnaireAuteurs GestionnaireAuteurs);
	/*Ajouter auteur au liste de vecteur de auteur
	@return true si c'est ajouter
	*/
    bool operator+=(const Auteur& auteur);
	/*
	*getter
	*la fonction retourne le nombre de auteur dans la liste
	*/
    std::size_t getNbAuteurs() const;
    static constexpr std::size_t NB_AUTEURS_MAX = 16;

private:
    /*
     *Méthode qui ajoute un auteur avec un string
     */
    bool lireLigneAuteur(const std::string& ligne);
    std::vector<Auteur> auteurs_;
  
};

#endif // GESTIONNAIREAUTEURS_H