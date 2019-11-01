#pragma once
#include "Resource.h"
#include <sol/sol.hpp>
#include "Scripting/ScriptAPI.h"
namespace yage {
class Script : public Resource {
public:
    Script(std::string content);

    ~Script();

    void onCreate();
    void onUpdate();
    sol::state* getLuaState();
    std::string getContent();
    void setContent(std::string content);
private:
    std::string mContent;
    sol::state *mLuaState = nullptr;
    bool mCreated = false;
    bool mValid = true;
};
}
