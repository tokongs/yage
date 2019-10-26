#include "MainMenu.h"

namespace yage
{
MainMenu::MainMenu()
{
}

MainMenu::~MainMenu()
{
}

void MainMenu::constructFrame(bool independent)
{
    if (ImGui::BeginMainMenuBar())
    {

        for (auto it = mElements.begin(); it != mElements.end(); it++)
        {

            if (ImGui::BeginMenu(it->first.c_str()))
            {
                for (int i = 0; i < it->second.size(); i++)
                {
                    (&it->second[i])->constructFrame();
                }
                ImGui::EndMenu();
            }
        }

        ImGui::EndMainMenuBar();
    }
}

void MainMenu::addMenuItem(std::string menu, MenuElement element)
{
    if (mElements.find(menu) == mElements.end())
    {
        mElements[menu] = std::vector<MenuElement>();
    }

    mElements[menu].push_back(element);
}

} // namespace yage