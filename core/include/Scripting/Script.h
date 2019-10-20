#pragma once
#include "Resource.h"

namespace yage{
class Script : public Resource {
public:
    Script(std::string content);
    ~Script();

    std::string getContent(){return m_content;};
private:
    std::string m_content;
};
typedef std::shared_ptr<Script> ScriptPtr;

}