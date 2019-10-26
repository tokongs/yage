#include "SceneManager.h"

namespace yage{

    Scene* SceneManager::mCurrentScene = nullptr;
    void SceneManager::Init() {

    }

    void SceneManager::SetScene(Scene* scene){
        mCurrentScene = scene;
    }

    Scene* SceneManager::GetCurrentScene() {
        return mCurrentScene;
    }
}