#include "GridTime.hpp"
#include "ITimeGrid.hpp"

GridTime::GridTime(PnlVect *datesVect)
    : ITimeGrid(eGridType::eGrid, NULL, NULL, datesVect) {};


