#ifndef PS2GAME
#define PS2GAME
#include "Media.hpp"
class Ps2Game : Media {
    std::string title_;
    std::string studio_;
    int year_;
    public:
    Ps2Game(const std::string& title, const std::string& studio, int year);
    const std::string& getTitle() const ;
    const std::string& getStudio() const ;
    int getYear() const ;
    bool operator==(const Ps2Game& rhs) const = default;
    std::string prettyPrint() const override;
};
#endif