#ifndef ITIMEGRID_HPP
#define ITIMEGRID_HPP

#include <vector>

class ITimeGrid {
public:
    std::vector<int> timeGrid;  // Liste des dates dans la grille de temps

    // Constructeur
    ITimeGrid(std::vector<int> grid) : timeGrid(grid) {}

    // Méthode pour obtenir une date dans la grille par son index
    int at(int index) const {
        if (index < 0 || index >= timeGrid.size()) {
            throw std::out_of_range("Index out of range");
        }
        return timeGrid[index];
    }

    // Méthode pour obtenir la longueur de la grille de temps
    int len() const {
        return timeGrid.size();
    }

    // Méthode pour vérifier si une date existe dans la grille
    bool has(int nDays) const {
        for (int t : timeGrid) {
            if (t == nDays) {
                return true;
            }
        }
        return false;
    }

    // Destructeur
    ~ITimeGrid() {}
};

#endif
