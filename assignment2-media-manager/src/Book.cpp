#include "Book.hpp"

Book::Book(const std::string& title, const std::string& author, const std::string& isbn, int pages, int edition)
{
    title_ = title;
    author_ = author;
    isbn_ = isbn;
    pages_ = pages;
    edition_ = edition;
}

// Book::~Book()
// {
// }

const std::string& Book::getTitle() const {
    return title_;
} 
const std::string& Book::getAuthor() const {
    return author_;
}
const std::string& Book::getIsbn() const {
    return isbn_;
}
int Book::getPages() const {
    return pages_;
}
int Book::getEdition() const {
    return edition_;
}
// std::string Book::prettyPrint() const {}
