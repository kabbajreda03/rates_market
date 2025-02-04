#ifndef FIXED_HPP
#define FIXED_HPP

#include "ITimeGrid.hpp"

class FixedTime : public ITimeGrid {
public:
    // Constructeur pour une grille à pas fixe
    FixedTime(int step, int stopDate);
};

#endif