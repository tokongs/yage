#include "SceneView.h"

namespace yage {
    SceneView::SceneView(Scene* scene)
    : mScene(scene){
       auto objects = scene->getGameObjects();
        for (auto it : objects) {

            mSelectedObjects[it->getId()] = false;
        }
    }

    void SceneView::constructFrame(bool independent) {
        if (!mOpen) {
            return;
        }

        ImGui::Begin(m_title.c_str(), &mOpen);


        auto objects = mScene->getGameObjects();
        if (mSelectedObjects.size() < objects.size()) {
            mSelectedObjects.clear();
            for (auto it : objects) {
                if (mSelectedObjects.find(it->getId()) == mSelectedObjects.end()) {
                    mSelectedObjects[it->getId()] = false;
                }
            }
        }
        for (auto it  : objects) {
            ImGui::Selectable(it->getName().c_str(), &(mSelectedObjects[it->getId()]));
            if (mSelectedObjects[it->getId()]) {
                GameObjectElement element(mScene->getGameObject(it->getId()));
                element.constructFrame(false);

            }
        }


        ImGui::End();

    } // namespace yage
}