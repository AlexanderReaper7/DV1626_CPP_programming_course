#include "MediaManager.hpp"
#include <iostream>
//#include <typeinfo>

MediaManager::MediaManager(size_t size){
    m_media = new Media*[size];
    m_capacity = size;
    m_size = 0;
}
MediaManager::~MediaManager(){
    for (size_t i = 0; i < m_size; i++) { delete m_media[i]; }
    delete[] m_media;
}

void MediaManager::addMedia(Media* media){
    if (Book* book = dynamic_cast<Book*>(media)) { addBook(*book); }
    else if (Vinyl* book = dynamic_cast<Vinyl*>(media)) { addVinyl(*book); }
    else if (Ps2Game* book = dynamic_cast<Ps2Game*>(media)) { addPs2Game(*book); }
    else { throw "unknown media type"; }
}
void MediaManager::addBook(const Book& book){
    if (m_size == m_capacity) {grow();}
    m_media[m_size] = new Book(book);
    m_size++;
}
void MediaManager::addVinyl(const Vinyl& vinyl){
    if (m_size == m_capacity) {grow();}
    m_media[m_size] = new Vinyl(vinyl);
    m_size++;
}
void MediaManager::addPs2Game(const Ps2Game& game){
    if (m_size == m_capacity) {grow();}
    m_media[m_size] = new Ps2Game(game);
    m_size++;
}
std::string MediaManager::printMedia() const {
    std::string output;
    for (int i = 0; i < m_size; i++)
    {
        auto temp = m_media[i]->prettyPrint();
        output += temp + "\n";
    }
    
    return output;
}
std::vector<Book> MediaManager::getBooks() const {
    std::vector<Book> output;
    for (int i = 0; i < m_size; i++) {
        if (auto *const book = dynamic_cast<Book*>(m_media[i])) {
            output.push_back(*book);
        }
    }
    return output;
}

std::vector<Vinyl> MediaManager::getVinyls() const {
    std::vector<Vinyl> output;
    for (int i = 0; i < m_size; i++) {
        if (auto *const vinyl = dynamic_cast<Vinyl*>(m_media[i])) {
            output.push_back(*vinyl);
        }
    }
    return output;
}
std::vector<Ps2Game> MediaManager::getPs2Games() const {
    std::vector<Ps2Game> output;
    for (int i = 0; i < m_size; i++) {
        if (auto *const ps2Game = dynamic_cast<Ps2Game*>(m_media[i])) {
            output.push_back(*ps2Game);
        }
    }
    return output;
}
Media** MediaManager::getMedias() const {
    return m_media;
}
bool MediaManager::operator==(const MediaManager& rhs) const {
    if (m_size != rhs.m_size) { return false; }
    for (int i = 0; i < m_size; i++) {
        if (*(m_media[i]) != *(rhs.getMedias()[i])) {
            return false;
        }
    }
    return true;
}
bool MediaManager::operator!=(const MediaManager& rhs) const {
    return !(*this == rhs);
}

void MediaManager::grow()
{
    const int new_capacity = (int)(m_capacity * 2);
    Media** temp = new Media*[new_capacity];
    std::copy(m_media, m_media + m_capacity, temp);
    m_capacity = new_capacity;
    delete[ ] m_media;
    m_media = temp;
};
