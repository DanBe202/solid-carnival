#ifndef POINTSSET_H
#define POINTSSET_H

#include "PointsList/pointslist.h"

class PointsSet {
private:
    string name = "";
    PointsList *list;
public:
    PointsSet();
    PointsSet(string name);
    PointsSet(PointsList * list);
    PointsSet(const PointsSet&);
    //    ~PointsSet();
    void setName(string name);
    string getName();
    PointsList *getList();
    friend ostream& operator << (ostream&, PointsSet&);
};

#endif // POINTSSET_H
