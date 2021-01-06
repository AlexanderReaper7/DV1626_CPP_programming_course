#ifndef MEDIA
#define MEDIA
#include <string>

class Media {
    public:
    virtual std::string prettyPrint() const = 0;
    virtual bool operator==(const Media& rhs) const = default;
};
#endif