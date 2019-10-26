#pragma once
#include "Resource.h"
namespace yage {
class Script : public Resource {
public:
    Script();
    Script(std::string content);

    ~Script();

    std::string getContent();
    void setContent(std::string content);
private:
    std::string mContent;
};
}
