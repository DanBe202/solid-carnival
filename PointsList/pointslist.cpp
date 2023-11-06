#include "pointslist.h"
#include <math.h>

PointsList::PointsList() {
    this->first = NULL;
    this->isCopy = false;
    this->size = 0;
}

PointsList::PointsList(int length) {
    this->first = new PointsListItem;
    this->first->next = NULL;
    this->isCopy = false;
    this->size = length;
    for (int i = 0; i < this->size; ++i) {
        PointsListItem *item = new PointsListItem;
        cout << "Input X: ";
        cin >> item->X;
        cout << "Input Y: ";
        cin >> item->Y;
        if (i == 0) {
            this->first = item;
        } else {
            item->next = this->first;
            this->first = item;
        }
    }
}

PointsList::PointsList(const PointsList &list) {
    this->first = NULL;
    this->isCopy = true;
    this->size = list.size;
    PointsListItem *item = list.first;
    while(item!=NULL){
        PointsListItem *copyItem = new PointsListItem;
        copyItem->next = NULL;
        copyItem->X = item->X;
        copyItem->Y = item->Y;
        if (!this->first) {
            this->first = copyItem;
        } else {
            copyItem->next = this->first;
            this->first = copyItem;
        }
        item = item->next;
    }

}

PointsList::~PointsList() {
    while (this->first != NULL) {
        PointsListItem *item = this->first;
        this->first = item->next;
        delete item;
    }
}

int PointsList::length() {
    return this->size;
}

float PointsList::distanceFromBegin(PointsListItem item) {
    float distance = sqrt(pow(item.X, 2) + pow(item.Y, 2));
    return distance;
}

void PointsList::swap(PointsListItem *firstItem, PointsListItem *secondItem) {
    int tempX = firstItem->X;
    int tempY = firstItem->Y;
    firstItem->X = secondItem->X;
    firstItem->Y = secondItem->Y;
    secondItem->X = tempX;
    secondItem->Y = tempY;
}

void PointsList::sortByDistance() {
    PointsListItem *firstItem = this->first;
    PointsListItem *secondItem = NULL;

    if(this->first == NULL) {
        return;
    }
    else {
        while(firstItem != NULL) {
            secondItem = firstItem->next;
            while(secondItem != NULL) {
                if(distanceFromBegin(*firstItem) > distanceFromBegin(*secondItem)) {
                    swap(firstItem, secondItem);
                }
                secondItem = secondItem->next;
            }
            firstItem = firstItem->next;
        }
    }
}

float PointsList::angleFromOX(const PointsListItem item) {
    if (item.X == 0 && item.Y == 0) {
        return 0;
    }
    if (item.X == 0) {
        return 90;
    }
    if (item.Y == 0) {
        return 0;
    }
    return atan(abs(item.Y) / abs(item.X)) * (180/M_PI);
}

void PointsList::sortByAngle() {
    PointsListItem *firstItem = this->first;
    PointsListItem *secondItem = NULL;

    if(this->first == NULL) {
        return;
    }
    else {
        while(firstItem != NULL) {
            secondItem = firstItem->next;
            while(secondItem != NULL) {
                if(angleFromOX(*firstItem) > angleFromOX(*secondItem)) {
                    swap(firstItem, secondItem);
                }
                secondItem = secondItem->next;
            }
            firstItem = firstItem->next;
        }
    }
}

void PointsList::addPoint(int x, int y) {
    PointsListItem *item = new PointsListItem;
    item->X = x;
    item->Y = y;
    if (!this->first) {
        this->first = item;
        this->first->next = NULL;
    } else {
        item->next = this->first;
        this->first = item;
    }
    ++this->size;
}

PointsList PointsList::operator* (const PointsList &list) const {
    PointsList newList;
    int firstLength = list.size;
    PointsListItem* firstList=list.first;
    while(firstLength != 0) {
        int secondLength = this->size;
        PointsListItem* secondList = first;
        while(secondLength != 0) {
            if((firstList->X) == (secondList->X) && (firstList->Y) == (secondList->Y)) {
                PointsListItem *item = new PointsListItem;
                item->X = secondList->X;
                item->Y = secondList->Y;
                item->next = newList.first;
                newList.first = item;
                ++newList.size;
            }
            secondList = secondList->next;
            --secondLength;
        }
        firstList=firstList->next;
        --firstLength;
    }
    if (newList.isEmpty()) {
        newList.first = new PointsListItem;
    }
    return newList;
}

PointsListItem *PointsList::getFirst() {
    return this->first;
}

PointsList PointsList::operator+ (const PointsList &list) const {
    PointsList newList;
    int firstLength = list.size;
    PointsListItem* firstList=list.first;
    while(firstLength != 0) {
        PointsListItem *item = new PointsListItem;
        item->X = firstList->X;
        item->Y = firstList->Y;
        item->next = newList.first;
        newList.first = item;
        ++newList.size;
        firstList=firstList->next;
        --firstLength;
    }
    int secondLength = this->size;
    PointsListItem* secondList = this->first;
    while(secondLength != 0) {
        PointsListItem *item = new PointsListItem;
        item->X = secondList->X;
        item->Y = secondList->Y;
        item->next = newList.first;
        newList.first = item;
        ++newList.size;
        secondList = secondList->next;
        --secondLength;
    }
    return newList;
}

PointsList PointsList::operator- (const PointsList &list) const {
    PointsList newList;
    int firstLength = this->size;
    PointsListItem* firstList = this->first;
    while(firstLength != 0) {
        bool toInsert = true;
        int secondLength = list.size;
        PointsListItem* secondList = list.first;
        while(secondLength != 0) {
            if((firstList->X) == (secondList->X) && (firstList->Y) == (secondList->Y)) {
                toInsert = false;
            }
            secondList = secondList->next;
            --secondLength;
        }
        if(toInsert == true) {
            PointsListItem *item = new PointsListItem;
            item->X = firstList->X;
            item->Y = firstList->Y;
            item->next = newList.first;
            newList.first = item;
            ++newList.size;
        }
        firstList=firstList->next;
        --firstLength;
    }
    return newList;
}

bool PointsList::isInList (PointsListItem item) const {
    PointsListItem *listItem = this->first;
    do {
        if (item.X == listItem->X && item.Y == listItem->Y) {
            return true;
        }
        listItem = listItem->next;
    } while (listItem != NULL);
    return false;
}

bool PointsList::isInListForUser(int X, int Y) const {
    PointsListItem *listItem = this->first;
    do {
        if (X == listItem->X && Y == listItem->Y) {
            return true;
        }
        listItem = listItem->next;
    } while (listItem != NULL);
    return false;
}

bool PointsList::isEmpty() {
    if (!this->first) {
        return true;
    }
    return false;
}

bool PointsList::operator<= (const PointsList &list) const {
    PointsListItem *item = this->first;
    if (list.size < this->size) {
        return false;
    }
    if (this->size == 0) {
        return true;
    }
    while (item != NULL) {
        if(!list.isInList(*item)) {
            return false;
        }
        item = item->next;
    }
    return true;
}
bool PointsList::operator>= (const PointsList &list) const {
    return list<=(*this);
}

bool PointsList::operator== (const PointsList &list) const {
    if (list.size != this->size) {
        return false;
    }
    return (*this) <= list;
}
bool PointsList::operator!= (const PointsList &list) const {
    return !((*this) == list);
}

PointsList::operator double() {
    return this->length();
}

ostream& operator<< (ostream &os, PointsList &list) {
    PointsListItem *item = list.first;
    os << "Your points are:" << endl;
    if (list.isEmpty()) {
        os << "List is empty" << endl;
        return os;
    }
    for (int i = 0; i < list.size; ++i) {
        os << i + 1 << "(" << item->X << "," << item->Y << ")" << endl;
        item = item->next;
    }
    return os;
}
