//
// Created by Matthias Röll on 10.05.15.
//

#ifndef SWE_PROJEKT_LCCOORDINATE_H
#define SWE_PROJEKT_LCCOORDINATE_H

/**
 * Klasse zum Speichern von Koordinaten
 */
class LCCoordinate {

public:
#pragma mark Konstruktoren
/* ---------------------------------------------------------------------------------------------------------------- */

    LCCoordinate();
    LCCoordinate(int x, int y);

#pragma mark Setter & Getter
/* ---------------------------------------------------------------------------------------------------------------- */

    int x() const;
    void x(int x);

    int y() const;
    void y(int y);

#pragma mark Operator Overloading
/* ---------------------------------------------------------------------------------------------------------------- */

    /* Überladene Operatoren
     *
     * Die +,- Operatoren werden für relative Bewegungnen benötigt
     * Die Vergleichsoperatoren für die Bewegung des Lasers
     */

    LCCoordinate operator+(const LCCoordinate &right);
    LCCoordinate operator-(const LCCoordinate &right);

    bool operator==(const LCCoordinate & right);
    bool operator!=(const LCCoordinate & right);

private:
#pragma mark Member Variables
/* ---------------------------------------------------------------------------------------------------------------- */

    int _x; /**< X koordinate */
    int _y; /**< Y koordinate */
};


#endif //SWE_PROJEKT_LCCOORDINATE_H
