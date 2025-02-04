#ifndef ITIMEGRID_HPP
#define ITIMEGRID_HPP

#include "pnl/pnl_vector.h"
// Enumération pour distinguer entre les différents types de grilles de temps
enum class eGridType {
    eFixed, // Grille avec un pas fixe
    eGrid   // Grille définie par une liste de dates précises
};

// Classe de base virtuelle pour gérer une grille de temps
class ITimeGrid {
public:

    // Type de la grille (Fixed ou Grid)
    eGridType type;

    // Vecteur qui contient les dates
    PnlVect* dates;
    int step;
    int stop;

    ITimeGrid(eGridType type, int step, int stopDate, PnlVect* dates=nullptr);
    virtual ~ITimeGrid();

    // Retourne la date à un index donné
    int at(int index) const;

    // Retourne le nombre d'éléments dans la grille
    int len() const;

    // Vérifie si une date existe à l'indice donné
    bool has(int nDays) const;

    int getNextFirstIndex(int t);

    ITimeGrid* CreateRealTimeGrid(ITimeGrid& theAbstTimeGrid);
};

#endif