//
// Created by Matthias Röll on 10.05.15.
//

#include "LCCoordinate.h"

#pragma mark Konstruktoren
/* ---------------------------------------------------------------------------------------------------------------- */

LCCoordinate::LCCoordinate() {
    _x = 0;
    _y = 0;
}
LCCoordinate::LCCoordinate(int x, int y) {
    _x = x;
    _y = y;
}

#pragma mark Setter & Getter
/* ---------------------------------------------------------------------------------------------------------------- */

int LCCoordinate::x() const {
    return _x;
}
void LCCoordinate::x(int x) {
    this->_x = x;
}

int LCCoordinate::y() const {
    return _y;
}
void LCCoordinate::y(int y) {
    this->_y = y;
}

#pragma mark Operator Overloading
/* ---------------------------------------------------------------------------------------------------------------- */

LCCoordinate LCCoordinate::operator+(const LCCoordinate &right) {
    LCCoordinate result;
    result.x(x() + right.x());
    result.y(y() + right.y());
    return result;
}
LCCoordinate LCCoordinate::operator-(const LCCoordinate &right) {
    LCCoordinate result;
    result.x(x() - right.x());
    result.y(y() - right.y());
    return result;
}

bool LCCoordinate::operator==(const LCCoordinate &right) {
    return (x() == right.x() && y() == right.y());
}

bool LCCoordinate::operator!=(const LCCoordinate &right) {
    return (x() != right.x() && y() != right.y());
}
