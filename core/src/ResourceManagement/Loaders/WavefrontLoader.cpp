#include "WavefrontLoader.h"

namespace yage
{
WavefrontLoader::WavefrontLoader()
{
}

WavefrontLoader::~WavefrontLoader()
{
}

VertexBufferPtr WavefrontLoader::loadWavefront(std::string file)
{
    VertexBufferDesc desc;
    desc.has_position = true;
    std::vector<glm::vec3> positions;



    //load positions
    std::size_t start_of_line = file.find("\nv ");
    std::size_t end_of_line = file.find_first_of('\n', start_of_line + 1);
    while (start_of_line != std::string::npos)
    {
        //v x y z
        std::size_t start_x = start_of_line + 2;
        std::size_t start_y = file.find_first_of(' ', start_x + 1);
        std::size_t start_z = file.find_first_of(' ', start_y + 1);

        glm::vec3 pos;
        std::string test = file.substr(start_x + 1, start_y - start_x - 2);
        pos.x = std::stof(file.substr(start_x + 1, start_y - start_x - 2));
        pos.y = std::stof(file.substr(start_y + 1, start_z - start_y - 2));
        if (end_of_line != std::string::npos)
        {
            pos.z = std::stof(file.substr(start_z + 1,
                                          end_of_line - start_y - 2));
        }
        else
        {
            pos.z = std::stof(file.substr(start_z + 1));
        }

        positions.push_back(pos);

        start_of_line = file.find("\nv ", start_of_line + 1);
        end_of_line = file.find_first_of('\n', start_of_line + 1);
    }

    return std::make_shared<VertexBuffer>(desc, std::vector<Vertex>());
}
} // namespace yage