#ifndef BOOK
#define BOOK
#include "Media.hpp"
class Book : Media {
    std::string title_;
    std::string author_;
    std::string isbn_;
    int pages_;
    int edition_;
    public:
    Book(const std::string& title, const std::string& author, const std::string& isbn, int pages, int edition);
    const std::string& getTitle() const ;
    const std::string& getAuthor() const ;
    const std::string& getIsbn() const ;
    int getPages() const ;
    int getEdition() const ;
    bool operator==(const Book& rhs) const = default;
    std::string prettyPrint() const override;
};
#endif