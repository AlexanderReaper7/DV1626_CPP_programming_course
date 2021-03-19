#include "Vinyl.hpp"

Track::Track(const std::string& name, const Time& length):length_(length) {
    name_ = name;
}
const std::string& Track::getName() const {
    return name_;
}
const Time& Track::getLength() const {
    return length_;
}
bool Track::operator==(const Track& rhs) const {
    return name_ == rhs.name_ &&
     length_ == rhs.length_;
};
bool Track::operator!=(const Track& rhs) const {
    return !(*this == rhs);
}

Vinyl::Vinyl(const std::string& title, VinylTypes type, int year, const std::string& artist, const Time& runtime):runtime_(runtime){
    title_ = title;
    type_ = type;
    year_ = year;
    artist_ = artist;
}

Vinyl::~Vinyl() {}

void Vinyl::addTrack(const Track& track){
    tracks_.push_back(track);
}
int Vinyl::getYear() const {
    return year_;
}
VinylTypes Vinyl::getType() const {
    return type_;
}
const std::string& Vinyl::getArtist() const {
    return artist_;
}
const Time& Vinyl::getRuntime() const {
    return runtime_;
}
const std::vector<Track>& Vinyl::getTracks() const {
    return tracks_;
}
std::string Vinyl::prettyPrint() const {
    std::string trackText = "\n Tracks:";
    if (!tracks_.empty()) {
        trackText += "\n";
    }
    else {
        trackText += " None";
    }
    for (int i = 0; i < tracks_.size(); i++)
    {
        trackText += "  " + tracks_[i].getName() + " " + tracks_[i].getLength().print() + "\n";
    }
    return "Vinyl: " + title_ + " " + std::to_string(year_) + " " + std::to_string(static_cast<int>(type_)) + " " + artist_ + " " + runtime_.print() + " " + trackText;
}
bool Vinyl::operator==(const Vinyl& rhs) const {
    return year_ == rhs.year_ &&
     type_ == rhs.type_ &&
     artist_ == rhs.artist_ &&
     runtime_ == rhs.runtime_ &&
     title_ == rhs.title_ &&
     tracks_ == rhs.tracks_;
}
bool Vinyl::operator!=(const Vinyl& rhs) const {
    return !(*this == rhs);
}
