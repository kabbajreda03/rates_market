#include "FixedTime.hpp"

FixedTime::FixedTime(int step, int stopDate)
    : ITimeGrid(eGridType::eFixed, step, stopDate) {}
