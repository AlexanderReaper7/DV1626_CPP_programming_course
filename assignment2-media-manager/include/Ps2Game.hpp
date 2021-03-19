#ifndef PS2GAME
#define PS2GAME
#include "Media.hpp"
class Ps2Game final : public Media {
    std::string studio_;
    int year_;
    public:
    Ps2Game(const std::string& title, const std::string& studio, int year);
    ~Ps2Game() override;
    const std::string& getStudio() const ;
    int getYear() const ;
    std::string prettyPrint() const override;
    bool operator==(const Ps2Game& rhs) const;
    bool operator!=(const Ps2Game& rhs) const;
    using Media::operator==;
    using Media::operator!=;
};
#endif