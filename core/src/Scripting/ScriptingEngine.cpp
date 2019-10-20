#include "ScriptingEngine.h"
namespace yage{
    DEFINE_LOGGERS(ScriptingEngine);
ScriptingEngine::ScriptingEngine() {
    INIT_LOGGERS(ScriptingEngine);
    m_engine = asCreateScriptEngine();

    if(!m_engine->SetMessageCallback(asFUNCTION(as_message_callback), 0, asCALL_CDECL))
        LOG(ScriptingEngine, warn, "Failed to set AngelScript callback message");

    RegisterStdString(m_engine);

    //test
    m_engine->RegisterGlobalFunction("void print(const string &in)", asFUNCTION(print), asCALL_CDECL);
}

ScriptingEngine::~ScriptingEngine(){
    m_engine->ShutDownAndRelease();
}

void ScriptingEngine::addScript(std::string module, yage::ScriptPtr script) {
    CScriptBuilder builder;
    if(!builder.StartNewModule(m_engine, module.data()))
        LOG(ScriptingEngine, warn, "Failed to start new module");
    if(!builder.AddSectionFromMemory("", script->getContent().data()));
        LOG(ScriptingEngine, warn, "Failed to load script with id: " + script->getResourceId());
    if(!builder.BuildModule())
        LOG(ScriptingEngine, warn, "Failed to build module");

}

void ScriptingEngine::execute() {
    asIScriptModule *mod = m_engine->GetModule("MyModule");
    asIScriptFunction *func = mod->GetFunctionByDecl("void main()");
    if(func == 0){
        LOG(ScriptingEngine, error, "Script must have main funciton");
        return;
    }

    asIScriptContext *ctx = m_engine->CreateContext();
    ctx->Prepare(func);
    int r = ctx->Execute();
    if( r != asEXECUTION_FINISHED )
    {
        // The execution didn't complete as expected. Determine what happened.
        if( r == asEXECUTION_EXCEPTION )
        {
            // An exception occurred, let the script writer know what happened so it can be corrected.
            printf("An exception '%s' occurred. Please correct the code and try again.\n", ctx->GetExceptionString());
        }
    }

    ctx->Release();
}

void ScriptingEngine::as_message_callback(const asSMessageInfo *msg, void *param){
    if(msg->type == asMSGTYPE_WARNING)
        LOG(ScriptingEngine, warn, msg->message)
    if(msg->type == asMSGTYPE_ERROR)
        LOG(ScriptingEngine, error, msg->message)
}


}