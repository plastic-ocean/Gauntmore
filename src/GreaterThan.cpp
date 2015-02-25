#include "GreaterThan.h"
bool GreaterThan::operator()(pathNode &a, pathNode &b ) {
    return a.getCost() > b.getCost(); 
}