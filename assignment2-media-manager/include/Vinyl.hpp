#ifndef VINYL
#define VINYL
#include "Media.hpp"
#include "Time.hpp"
#include <vector>

class Track {
    std::string name_;
    Time length_;
    public:
    Track(const std::string& name, const Time& length);
    const std::string& getName() const ;
    const Time& getLength() const ;
    bool operator==(const Track& rhs) const = default;
};

enum class VinylTypes{
    LONG_PLAY,
    EXTENDED_PLAY,
};

class Vinyl : Media {
    std::string title_;
    int year_;
    VinylTypes type_;
    std::string artist_;
    Time runtime_;
    std::vector<Track> tracks_;
    public:
    Vinyl(const std::string& title, VinylTypes type, int year, const std::string& artist, const Time& runtime);
    void addTrack(const Track& track);
    const std::string& getTitle() const;
    int getYear() const;
    VinylTypes getType() const;
    const std::string& getArtist() const;
    const Time& getRuntime() const;
    const std::vector<Track>& getTracks() const;
    bool operator==(const Vinyl& rhs) const = default;
    std::string prettyPrint() const override;
};
#endif