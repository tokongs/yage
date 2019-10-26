#pragma once
#include "Scene.h"

namespace yage{

class SceneManager{
public:
    static void Init();

    static void SetScene(Scene* scene);
    static Scene* GetCurrentScene();

private:
    static Scene* mCurrentScene;
};
}