#include "GameBoard.h"


GameBoard::GameBoard(size_t height, size_t width)
    : height(height), width(width), board(height, std::vector<Cell>(width)) {}

GameBoard::GameBoard(const GameBoard& other)
    : height(other.height), width(other.width), board(other.board) {}

GameBoard::GameBoard(GameBoard&& other) noexcept
    : height(other.height), width(other.width), board(std::move(other.board)) {}

GameBoard& GameBoard::operator=(const GameBoard& other) {
    if (this != &other) {
        height = other.height;
        width = other.width;
        board = other.board;
    }
    return *this;
}

GameBoard& GameBoard::operator=(GameBoard&& other) {
    if (this != &other) {
        height = other.height;
        width = other.width;
        board = std::move(other.board);
    }
    return *this;
}

const Cell& GameBoard::operator()(size_t x, size_t y) {
    return board[y][x];
}

void GameBoard::placeShip(size_t x, size_t y, Ship& ship){
    checkShipCoords(x, y, ship);
    if (ship.getOrientation() == Orientation::Horizontal){
        for(size_t i = 0; i < ship.getLength(); i++){
            board[y][x + i].placeShipSegment(ship, i);
        }
    }
    else if (ship.getOrientation() == Orientation::Vertical){
        for(size_t i = 0; i < ship.getLength(); i++){
            board[y + i][x].placeShipSegment(ship, i);
        }
    }
}

void GameBoard::checkAttackCoords(size_t x, size_t y) const
{
    if (x >= width || y >= height){
        throw AttackCoordsException();
    }
}

void GameBoard::attackCell(size_t x, size_t y, int damage) {
    checkAttackCoords(x, y);
    if (board[y][x].isShip()) {
        board[y][x].attackShip(damage);
        if(board[y][x].getStatus() == ViewState::Unknown) {
            board[y][x].setStatus(ViewState::Ship);
        };
    }
    else {
        if (board[y][x].getStatus() == ViewState::Unknown) {
            board[y][x].setStatus(ViewState::Empty);
        }
    }
}

void GameBoard::checkShipCoords(size_t x, size_t y, Ship& ship) const {
    if (x >= width || y >= height) {
        throw ShipOutOfBoundsException();
    }
    size_t xi;
    size_t yi;
    if (ship.getOrientation() == Orientation::Vertical) {
        if ((y > height - ship.getLength()) || (height - ship.getLength() < 0)) {
            throw ShipOutOfBoundsException();
        }
        yi = y + ship.getLength();
        xi = x + 1;
    } else if (ship.getOrientation() == Orientation::Horizontal) {
        if ((x > width - ship.getLength()) || (width - ship.getLength() < 0)) {
            throw ShipOutOfBoundsException();
        }
        yi = y + 1;
        xi = x + ship.getLength();
    }

    size_t yStart = (y == 0) ? 0 : y - 1;
    size_t xStart = (x == 0) ? 0 : x - 1;
    size_t yEnd = std::min(yi, height - 1);
    size_t xEnd = std::min(xi, width - 1);

    for (size_t i = yStart; i <= yEnd; ++i) {
        for (size_t j = xStart; j <= xEnd; ++j) {
            if (board[i][j].isShip()) {
                throw ShipOverlapsException();
            }
        }
    }
}

bool GameBoard::isShip(size_t x, size_t y) const {
    if (x >= width || y >= height)
        return false;
    return (this->board[y][x].isShip());
}

size_t GameBoard::getHeight() const {
    return height;
}

size_t GameBoard::getWidth() const {
    return width;
}

std::ostream& operator<<(std::ostream& os, const GameBoard& board) {
    os << board.height << ' ' << board.width << '\n';

    for (size_t i = 0; i < board.height; ++i) {
        for (size_t j = 0; j < board.width; ++j) {
            os << board.board[i][j] << ' ';
        }
        os << '\n';
    }
    return os;
}

std::istream& operator>>(std::istream& is, GameBoard& board) {
    size_t height, width;
    is >> height >> width;

    board.height = height;
    board.width = width;
    board.board.resize(height, std::vector<Cell>(width));

    for (size_t i = 0; i < height; ++i) {
        for (size_t j = 0; j < width; ++j) {
            Cell cell;
            is >> cell; // Предполагается, что оператор>> для Cell уже реализован
            if (is.fail()) {
                throw std::ios_base::failure("Failed to read cell data");
            }
            board.board[i][j] = cell;
        }
    }
    return is;
}
