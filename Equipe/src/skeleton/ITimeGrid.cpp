#include "ITimeGrid.hpp"
#include <iostream>

// Méthode pour obtenir une date dans la grille par son index
int ITimeGrid::at(int index) const {
    if (index < 0 || index >= timeGrid.size()) {
        throw std::out_of_range("Index out of range");
    }
    return timeGrid[index];
}

// Méthode pour obtenir la longueur de la grille de temps
int ITimeGrid::len() const {
    return timeGrid.size();
}

// Méthode pour vérifier si une date existe dans la grille
bool ITimeGrid::has(int nDays) const {
    for (int t : timeGrid) {
        if (t == nDays) {
            return true;
        }
    }
    return false;
}
