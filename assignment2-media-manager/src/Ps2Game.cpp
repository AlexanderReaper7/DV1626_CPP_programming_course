#include "Ps2Game.hpp"


Ps2Game::Ps2Game(const std::string& title, const std::string& studio, int year){
    title_ = title;
    studio_ = studio;
    year_ = year;
}

const std::string& Ps2Game::getTitle() const {
    return title_;
}
const std::string& Ps2Game::getStudio() const {
    return studio_;
} 
int Ps2Game::getYear() const {
    return year_;
}
// std::string Ps2Game::prettyPrint() const {}
