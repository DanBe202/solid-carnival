#include "pointsset.h"

PointsSet::PointsSet() {
    this->name = "";
    this->list = new PointsList;
}

PointsSet::PointsSet(string name) {
    this->name = name;
    this->list = new PointsList;
}

PointsSet::PointsSet(PointsList *list) {
    cout << "Input a name for this set: ";
    cin >> this->name;
    this->list = list;
}

PointsSet::PointsSet(const PointsSet &set) {
    this->name = set.name;
//    PointsList copyList(*set.list);
    this->list = new PointsList(*(set.list));
}

void PointsSet::setName(string name) {
    this->name = name;
}

string PointsSet::getName() {
    return this->name;
}

PointsList *PointsSet::getList() {
    return this->list;
}

ostream& operator << (ostream& out, PointsSet &set) {
    out << "Set name: " << set.name;
    out << *set.list;
    return out;
}
