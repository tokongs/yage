#include "WavefrontLoader.h"

namespace yage {
    WavefrontLoader::WavefrontLoader() {
    }

    WavefrontLoader::~WavefrontLoader() {
    }

// TODO: make better. this is for testin purposes
    VertexBuffer *WavefrontLoader::loadWavefront(std::string filePath) {
        Assimp::Importer importer;

        YAGE_INFO("Loading wavefront from {}", filePath);

        const aiScene *scene = importer.ReadFile(filePath,
                                                 aiProcess_CalcTangentSpace|
                                                 aiProcess_Triangulate |
                                                 aiProcess_JoinIdenticalVertices);

        if (!scene) {
            YAGE_ERROR("Failed to load wavefront file with assimp: {}", importer.GetErrorString());
        }

        for (int x = 0; x < scene->mNumMeshes; x++) {
            aiMesh *mesh = scene->mMeshes[x];
            VertexBufferDesc desc;
            desc.hasPosition = true;
            if (mesh->HasNormals()) {
                desc.hasNormal = true;
            }
            if (mesh->HasTextureCoords(0)) {
                desc.hasTexCoord = true;
            }
            std::vector<Vertex> vertices;
            std::vector<unsigned int> indices;
            for(int i = 0; i < mesh->mNumVertices; i++){
                Vertex vertex;

                vertex.position.x = mesh->mVertices[i].x;
                vertex.position.y = mesh->mVertices[i].y;
                vertex.position.z = mesh->mVertices[i].z;
                if (mesh->HasNormals()) {
                    vertex.normal.x = mesh->mNormals[i].x;
                    vertex.normal.y = mesh->mNormals[i].y;
                    vertex.normal.z = mesh->mNormals[i].z;
                }

                if (mesh->HasTextureCoords(0)) {

                    vertex.texCoord.x = mesh->mTextureCoords[0][i].x;
                    vertex.texCoord.y = mesh->mTextureCoords[0][i].y;
                }
                vertices.push_back(vertex);

            }
            for (int i = 0; i < mesh->mNumFaces; i++) {
                indices.push_back(mesh->mFaces[i].mIndices[0]);
                indices.push_back(mesh->mFaces[i].mIndices[1]);
                indices.push_back(mesh->mFaces[i].mIndices[2]);
            }
            VertexBuffer *result = new VertexBuffer(desc, vertices, indices);
            return result;
        }

        return nullptr;
    }
} // namespace yage