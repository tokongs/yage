
#include <Logger.h>
#include "Script.h"

namespace yage{
    Script::Script() {

    }

    Script::Script(std::string content)
    : mContent(content)
    {
    }

    Script::~Script() {

    }

    void Script::setContent(std::string content) {
        mContent = content;
    }

    std::string Script::getContent() {
        return mContent;
    }

}
