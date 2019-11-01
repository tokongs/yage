#include <Logger.h>
#include "Script.h"

namespace yage {
    Script::Script(std::string content) {

        mLuaState = new sol::state();
        OpenLuaLibs(mLuaState);
        SetupInputAPI(mLuaState);
        SetupGameObjectsAPI(mLuaState);
        SetupSceneAPI(mLuaState);
        SetupMathAPI(mLuaState);

        mContent = content;
        mLuaState->script(content);
    }

    Script::~Script() {
        if(mLuaState){
            delete mLuaState;
            mLuaState = nullptr;
        }
    }

    void Script::onCreate() {
        if (!mValid)
            return;
        sol::function func = (*mLuaState)["OnCreate"];
        func();
        mCreated = true;
    }

    void Script::onUpdate() {
        if (!mValid)
            return;
        if (!mCreated)
            onCreate();
        (*mLuaState)["OnUpdate"]();

    }

    sol::state* Script::getLuaState(){
        return mLuaState;
    }


    void Script::setContent(std::string content) {
        mContent = content;
    }

    std::string Script::getContent() {
        return mContent;
    }

}
