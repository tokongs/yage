#pragma once
#include "Resource.h"
namespace yage {
class Script : public Resource {
public:
    Script(int id, std::string name, std::string file_path, std::string content);

    ~Script();

    std::string getContent();
    void setContent(std::string content);
private:
    std::string m_content;
};
typedef std::shared_ptr<Script> ScriptPtr;

}
