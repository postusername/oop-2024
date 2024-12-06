#include "Ship.h"
#include <sstream>


Ship::Ship(unsigned short length, Orientation orientation, size_t x, size_t y)
    : length(length), orientation(orientation), segments(length, SegmentStatus::Undamaged),
    x(x), y(y) {}

unsigned short Ship::getLength() const {
    return this->length;
}

Orientation Ship::getOrientation() const {
    return this->orientation;
}

SegmentStatus Ship::getSegmentStatus(unsigned short index) const {
    return this->segments[index];
}

void Ship::takeDamage(unsigned short segment, int damage) {
    if (segment >= this->length) {
        throw std::out_of_range("Ship segment out of range");
    }
    int health = static_cast<int>(this->segments[segment])  - damage;

    if (health <= 0) {
        this->segments[segment] = SegmentStatus::Destroyed;
    } else {
        this->segments[segment] = (SegmentStatus)health;
    }
}

bool Ship::isDestroyed() const {
    return std::all_of(this->segments.begin(), this->segments.end(),
        [](SegmentStatus segment) -> bool { return segment == SegmentStatus::Destroyed; });
}

std::ostream& operator<<(std::ostream& os, Ship& ship) {
    os << ship.getLength() << ' ';
    os << (ship.getOrientation() == Horizontal ? "Horizontal" : "Vertical") << ' ';

    for (unsigned short i = 0; i < ship.getLength(); ++i) {
        os << static_cast<int>(ship.getSegmentStatus(i)) << ' ';
    }
    os << ship.x << ' ' << ship.y << '\n';

    return os;
}

std::istream& operator>>(std::istream& is, Ship& ship) {
    unsigned short length;
    std::string orientation;
    std::vector<SegmentStatus> segments;
    size_t x, y;

    is >> length;
    if (is.fail()) {
        throw std::runtime_error("Invalid format for Length");
    }
    ship = Ship(length, Horizontal, 0, 0); // Устанавливаем ориентацию по умолчанию

    is >> orientation;
    if (orientation == "Horizontal") {
        ship.orientation = Horizontal;
    } else if (orientation == "Vertical") {
        ship.orientation = Vertical;
    } else {
        throw std::runtime_error("Invalid format for Orientation");
    }

    unsigned short status;
    for (unsigned short i = 0; i < length; ++i) {
        is >> status;
        if (is.fail() || status > 2) {
            throw std::invalid_argument("Invalid segment status");
        }
        segments.push_back(static_cast<SegmentStatus>(status));
    }

    if (segments.size() != length) {
        throw std::runtime_error("Segment count does not match ship length");
    }
    ship.segments = segments;
    is >> ship.x >> ship.y;
    
    return is;
}
