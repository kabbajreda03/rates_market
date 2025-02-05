#include <vector>
#include "ITimeGrid.hpp"
#include <string>
#include <stdexcept>

ITimeGrid::ITimeGrid(eGridType typeGrid, int stepDate, int stopDate, PnlVect* datesVect) :
     type(typeGrid), step(stepDate), stop(stopDate) {
      if (datesVect != NULL) {
        dates = pnl_vect_copy(datesVect);
      }
      else {
        dates = pnl_vect_create(stopDate / stepDate + 1);
        int currentStep = 0;
        int index = 0;
        while (currentStep <= stopDate) {
          LET(dates, index) = currentStep;
          currentStep += stepDate;
          index ++;
        }
      }
  }

int ITimeGrid::at(int index) const{
     if (index < 0 || index >= dates->size) {
       throw std::invalid_argument("index out of range");
     }
     return (int) GET(dates, index);
}

int ITimeGrid::len() const {
     return dates->size;
}

// Vérifier si une date existe à l'indice donné
bool ITimeGrid::has(int nDays) const {
    for (int i = 0; i < dates->size; i++) {
      int day = GET(dates, i);
      if (day == nDays) {
        return true;
      }
    }
    return false;
}

int ITimeGrid::getNextFirstIndex(int t) {
    int index = 0;
    while (index < len() and GET(dates, index) < t) {
      index++;
    }
    return index;
}

ITimeGrid::~ITimeGrid() {

}