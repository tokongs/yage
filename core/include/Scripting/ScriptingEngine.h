#pragma once
#include <angelscript.h>
#include <scriptstdstring/scriptstdstring.h>
#include <scriptbuilder/scriptbuilder.h>
#include <Script.h>
#include <config.h>
namespace yage{
class ScriptingEngine {
public:
    ScriptingEngine();
    ~ScriptingEngine();

    asIScriptEngine* getASEngine(){return m_engine;};

    void addScript(std::string module, ScriptPtr script);
    void execute();
private:
    asIScriptEngine *m_engine;
    std::vector<ScriptPtr> m_scripts;

    DECLARE_LOGGERS;

    static void as_message_callback(const asSMessageInfo *msg, void *param);
    static void print(std::string x) {std::cout << x << std::endl;};

};

}