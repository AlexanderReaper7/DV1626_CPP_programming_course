#ifndef MEDIA_MANAGER
#define MEDIA_MANAGER
#include "Book.hpp"
#include "Ps2Game.hpp"
#include "Vinyl.hpp"

class MediaManager {
    public:
    MediaManager();
    void addMedia(Media* media);
    void addBook(const Book& book);
    void addVinyl(const Vinyl& vinyl);
    void addPs2Game(const Ps2Game& game);
    std::string printMedia() const ;
    std::vector<Book> getBooks() const ;
    std::vector<Vinyl> getVinyls() const ;
    std::vector<Ps2Game> getPs2Games() const ;
    bool operator==(const MediaManager& rhs) const = default;
};
#endif