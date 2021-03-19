#include "Book.hpp"
#include <iostream>
Book::Book(const std::string& title, const std::string& author, const std::string& isbn, int pages, int edition)
{
    title_ = title;
    author_ = author;
    isbn_ = isbn;
    pages_ = pages;
    edition_ = edition;
}
Book::~Book() {}

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

std::string Book::prettyPrint() const {
    return "Book: " + title_ + ", " + author_ + ", " + isbn_  + ", " + std::to_string(pages_) + ", " + std::to_string(edition_);
}

bool Book::operator==(const Book& rhs) const {
    return title_ == rhs.title_ &&
        author_ == rhs.author_ &&
        isbn_ == rhs.isbn_ &&
        pages_ == rhs.pages_ &&
        edition_ == rhs.edition_;
}
bool Book::operator!=(const Book& rhs) const {
    return !(*this == rhs);
}

