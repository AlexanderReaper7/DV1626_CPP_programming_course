#include "Media.hpp"

const std::string& Media::getTitle() const {
    return title_;
};
bool Media::operator==(const Media& rhs) const {
    return prettyPrint() == rhs.prettyPrint();
};
bool Media::operator!=(const Media& rhs) const {
    return !(*this == rhs);
};
Media::~Media() {};
