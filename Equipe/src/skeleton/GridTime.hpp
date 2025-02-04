#ifndef GRID_HPP
#define GRID_HPP

#include "ITimeGrid.hpp"

class GridTime : public ITimeGrid {
public:
    // Constructeur pour une grille définie par une liste de dates
    GridTime(PnlVect* datesVect);
};

#endif