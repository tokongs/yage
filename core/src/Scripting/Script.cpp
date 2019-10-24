/*
#include "Script.h"

namespace yage{
    Script::Script(int id, std::string name, std::string file_path)
    : Resource(id, name, file_path)
    {
        m_engine = asCreateScriptEngine();
        if(!m_engine){
            YAGE_ERROR("Failed to create script engine for script with Resource id: " + m_id);
            return;
        }

        m_engine->SetMessageCallback(asMETHOD(Script, messageCallback), this, asCALL_THISCALL);

        m_context = m_engine->CreateContext();

        m_context->SetExceptionCallback(asMETHOD(Script, exceptionCallback), this, asCALL_THISCALL);

        RegisterStdString(m_engine);

        registerPrintFunctions(m_engine);
    }

    Script::~Script() {
        if(m_context){
            m_context->Release();
        }
        if(m_engine){
            m_engine->Release();
        }
    }

    bool Script::compile(std::string module_name, std::string script_content) {
        if(!m_engine){
            YAGE_ERROR("Can't compile script because engine is nullptr");
            return false;
        }
        asIScriptModule *module = m_engine->GetModule(module_name.data(), asGM_CREATE_IF_NOT_EXISTS);
        module->AddScriptSection(m_name.data(), script_content.data());

        int result = module->Build();
        if(result < 0){
            YAGE_ERROR("Failed to build Angelscript module: " + module_name);
            return false;
        }

        return true;
    }

    bool Script::execute(){
        m_context->Execute();
        return true;
    }

    void Script::messageCallback(const asSMessageInfo *msg, void *param) {
        switch(msg->type){
            case asMSGTYPE_WARNING:
                YAGE_WARN(msg->message);
                break;
            case asMSGTYPE_ERROR:
                YAGE_ERROR(msg->message);
                break;
            case asMSGTYPE_INFORMATION:
                YAGE_INFO(msg->message);
                break;
        }
    }

    void Script::exceptionCallback(asIScriptContext *ctx) {
        asIScriptEngine *engine = ctx->GetEngine();

        YAGE_ERROR("Exception in Angelscript: " + m_name);
        // Determine the exception that occurred
       YAGE_ERROR("desc: %s\n", ctx->GetExceptionString());

        // Determine the function where the exception occurred
        const asIScriptFunction *function = ctx->GetExceptionFunction();
        YAGE_ERROR("func: %s\n", function->GetDeclaration());
        YAGE_ERROR("modl: %s\n", function->GetModuleName());
        YAGE_ERROR("sect: %s\n", function->GetScriptSectionName());

        // Determine the line number where the exception occurred
        YAGE_ERROR("line: %d\n", ctx->GetExceptionLineNumber());

    }
}
 */