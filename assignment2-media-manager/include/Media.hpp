#ifndef MEDIA
#define MEDIA
#include <string>

class Media {
    public:
    std::string title_;
    virtual std::string prettyPrint() const = 0;
    virtual const std::string& getTitle() const;
    bool operator==(const Media& rhs) const;
    bool operator!=(const Media& rhs) const;
    virtual ~Media();
};
#endif