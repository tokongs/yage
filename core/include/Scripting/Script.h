/*
#pragma once
#include "Resource.h"
#include "../../3rd_party/angelscript/angelscript/source/as_debug.h"
#include <scriptstdstring/scriptstdstring.h>
#include "IOAPI.h"
#include "Logger.h"
namespace yage{
class Script : public Resource {
public:
    Script(int id, std::string name, std::string file_path);

    ~Script();

    bool compile(std::string module_name, std::string script_content);
    bool execute();
    void messageCallback(const asSMessageInfo *msg, void *param);
    void exceptionCallback(asIScriptContext* context);

    std::string getContent(){return m_content;};
private:
    asIScriptEngine *m_engine;
    asIScriptContext *m_context;
    std::string m_content;
    std::string m_module_name;
};
typedef std::shared_ptr<Script> ScriptPtr;

}
 */