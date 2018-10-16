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

        for (auto it = m_elements.begin(); it != m_elements.end(); it++)
        {

            if (ImGui::BeginMenu(it->first.c_str()))
            {
                for (int i = 0; i < it->second.size(); i++)
                {
                    it->second[i]->constructFrame();
                }
                ImGui::EndMenu();
            }
        }

        ImGui::EndMainMenuBar();
    }
}

void MainMenu::addMenuItem(std::string menu, std::unique_ptr<MenuElement> element)
{
    if (m_elements.find(menu) == m_elements.end())
    {
        m_elements[menu] = std::vector<std::unique_ptr<MenuElement>>();
    }

    m_elements[menu].push_back(std::move(element));
}

} // namespace yage