#include "WavefrontLoader.h"

namespace yage
{
WavefrontLoader::WavefrontLoader()
{
}

WavefrontLoader::~WavefrontLoader()
{
}

// TODO: make better. this is for testin purposes
VertexBufferPtr WavefrontLoader::loadWavefront(std::string file)
{
    VertexBufferDesc desc;
    desc.has_position = true;
    std::vector<glm::vec3> positions;
    std::vector<Vertex> vertices;

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
    start_of_line = file.find("\nf ");
    end_of_line = file.find_first_of('\f', start_of_line + 1);

    while (start_of_line != std::string::npos)
    {
        //v x y z
        std::size_t start_1 = start_of_line + 2;
        std::size_t end_1 = file.find_first_of('/', start_1);
        std::size_t start_2 = file.find_first_of(' ', start_1 + 1);
        std::size_t end_2 = file.find_first_of('/', start_2);
        std::size_t start_3 = file.find_first_of(' ', start_2 + 1);
        std::size_t end_3 = file.find_first_of('/', start_3);

        int index_1 = std::stof(file.substr(start_1 + 1, end_1 - start_1 - 1));
        int index_2 = std::stof(file.substr(start_2 + 1, end_2 - start_2 - 1));
        int index_3 = std::stof(file.substr(start_3 + 1, end_3 - start_3 - 1));

        Vertex vert_1;
        vert_1.position.x = positions[index_1 - 1].x;
        vert_1.position.y = positions[index_1 - 1].y;
        vert_1.position.z = positions[index_1 - 1].z;

        Vertex vert_2;
        vert_2.position.x = positions[index_2 - 1].x;
        vert_2.position.y = positions[index_2 - 1].y;
        vert_2.position.z = positions[index_2 - 1].z;

        Vertex vert_3;
        vert_3.position.x = positions[index_3 - 1].x;
        vert_3.position.y = positions[index_3 - 1].y;
        vert_3.position.z = positions[index_3 - 1].z;

        vertices.push_back(vert_1);
        vertices.push_back(vert_2);
        vertices.push_back(vert_3);

        start_of_line = file.find("\nf ", start_of_line + 1);
        end_of_line = file.find_first_of('\n', start_of_line + 1);
    }

    return std::make_shared<VertexBuffer>(desc, vertices);
}
} // namespace yage