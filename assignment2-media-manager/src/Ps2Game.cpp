#include "Ps2Game.hpp"


Ps2Game::Ps2Game(const std::string& title, const std::string& studio, int year){
    title_ = title;
    studio_ = studio;
    year_ = year;
}
Ps2Game::~Ps2Game() {}

const std::string& Ps2Game::getStudio() const {
    return studio_;
} 
int Ps2Game::getYear() const {
    return year_;
}
std::string Ps2Game::prettyPrint() const {
    return "PS2 game: " + title_ + " " + studio_ + " " + std::to_string(year_);
}
bool Ps2Game::operator==(const Ps2Game& rhs) const {
    return title_ == rhs.title_ &&
        studio_ == rhs.studio_ &&
        year_ == rhs.year_;
}
bool Ps2Game::operator!=(const Ps2Game& rhs) const {
    return !(*this == rhs);
}
