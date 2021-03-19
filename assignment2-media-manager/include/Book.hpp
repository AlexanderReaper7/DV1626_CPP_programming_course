#ifndef BOOK
#define BOOK
#include "Media.hpp"
class Book final : public Media {
    std::string author_;
    std::string isbn_;
    int pages_;
    int edition_;
    public:
    Book(const std::string& title, const std::string& author, const std::string& isbn, int pages, int edition);
    ~Book() override;
    const std::string& getAuthor() const ;
    const std::string& getIsbn() const ;
    int getPages() const ;
    int getEdition() const ;
    std::string prettyPrint() const override;
    bool operator==(const Book& rhs) const;
    bool operator!=(const Book& rhs) const;
    using Media::operator==;
    using Media::operator!=;
};
#endif