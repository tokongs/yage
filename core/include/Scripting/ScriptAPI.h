#pragma once

#include <sol/sol.hpp>
#include "Input.h"
#include "GameObject.h"
#include "Scene.h"


namespace yage {

#define REGISTER_COMPONENT_TO_SCRIPTING_API(state, component) state->new_usertype<component>(#component, "new", sol::no_constructor, "mData", &component::mData); \
        (*state)["Get" #component] = &component::get##component

    void OpenLuaLibs(sol::state *luaState);

    void SetupInputAPI(sol::state *luaState);

    void SetupGameObjectsAPI(sol::state *luaState);

    void SetupSceneAPI(sol::state *luaState);

    void SetupMathAPI(sol::state *luaState);
}