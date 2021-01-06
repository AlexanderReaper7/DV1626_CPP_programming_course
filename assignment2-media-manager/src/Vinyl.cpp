#include "Vinyl.hpp"

Track::Track(const std::string& name, const Time& length):length_(length) {
    name_ = std::string(name);
    length_ = Time(length);
}
const std::string& Track::getName() const {
    return name_;
}
const Time& Track::getLength() const {
    return length_;
}



Vinyl::Vinyl(const std::string& title, VinylTypes type, int year, const std::string& artist, const Time& runtime):runtime_(runtime){
    title_ = std::string(title);
    type_ = VinylTypes(type);
    year_ = year;
    artist_ = std::string(artist);
    runtime_ = Time(runtime.getChronoTime());
}
Vinyl::~Vinyl(){

}
void Vinyl::addTrack(const Track& track){

}
const std::string& Vinyl::getTitle() const {
    return title_;
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

}
