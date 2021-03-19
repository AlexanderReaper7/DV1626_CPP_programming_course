#ifndef MEDIA_MANAGER
#define MEDIA_MANAGER
#include "Book.hpp"
#include "Ps2Game.hpp"
#include "Vinyl.hpp"
class MediaManager {
    Media** m_media;
    int m_size;
    int m_capacity;
    public:
    MediaManager(size_t size);
    ~MediaManager();
    void addMedia(Media* media);
    void addBook(const Book& book);
    void addVinyl(const Vinyl& vinyl);
    void addPs2Game(const Ps2Game& game);
    std::string printMedia() const ;
    std::vector<Book> getBooks() const ;
    std::vector<Vinyl> getVinyls() const ;
    std::vector<Ps2Game> getPs2Games() const ;
    Media** getMedias() const ;
    bool operator==(const MediaManager& rhs) const;
    bool operator!=(const MediaManager& rhs) const;
    void grow();

};
#endif