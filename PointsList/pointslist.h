#ifndef POINTSLIST_H
#define POINTSLIST_H

#include <iostream>

using namespace std;

struct PointsListItem {
    int X, Y;
    PointsListItem *next;
};

class PointsList {
private:
    PointsListItem *first;
    int size = 0;
    bool isCopy;
public:
    PointsList();
    PointsList(int length);
    PointsList(const PointsList&);
    ~PointsList();
    int length();
    static float distanceFromBegin(const PointsListItem item);
    void swap(PointsListItem *firstItem, PointsListItem *secondItem);
    void sortByDistance();
    void sortByAngle();
    static float angleFromOX(const PointsListItem item);
    void addPoint(int x, int y);
    PointsListItem *getFirst();
    PointsList operator*(const PointsList&) const;
    PointsList operator+(const PointsList&) const;
    PointsList operator-(const PointsList&) const;
    bool isEmpty();
    bool isInList (PointsListItem item) const;
    bool isInListForUser (int X, int Y) const;
    bool operator==(const PointsList&) const;
    bool operator!=(const PointsList&) const;
    bool operator>=(const PointsList&) const;
    bool operator<=(const PointsList&) const;
    operator double();
    friend ostream& operator << (ostream&, PointsList&);
};

#endif // POINTSLIST_H
