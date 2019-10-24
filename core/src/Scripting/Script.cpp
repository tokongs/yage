
#include "Script.h"

namespace yage{
    Script::Script(int id, std::string name, std::string file_path, std::string content)
    : Resource(id, name, file_path), m_content(content)
    {

    }

    Script::~Script() {

    }

    void Script::setContent(std::string content) {
        m_content = content;
    }

    std::string Script::getContent() {
        return m_content;
    }

}
