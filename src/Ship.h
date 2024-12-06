#pragma once

#include <vector>
#include <algorithm>
#include <stdexcept>

enum Orientation {
    Horizontal,
    Vertical
};

enum SegmentStatus
{
    Undamaged = 2,
    Damaged = 1,
    Destroyed = 0
};

class Ship {
private:
    unsigned short length;
    Orientation orientation;
    std::vector<SegmentStatus> segments;

public:
    Ship(unsigned short length, Orientation orientation);
    unsigned short getLength() const;
    Orientation getOrientation() const;
    SegmentStatus getSegmentStatus(unsigned short index) const;
    void takeDamage(unsigned short segmentIndex, int damage);
    bool isDestroyed() const;
    friend std::istream& operator>>(std::istream& is, Ship& ship);
    friend std::ostream& operator<<(std::ostream& os, Ship& ship);
};
