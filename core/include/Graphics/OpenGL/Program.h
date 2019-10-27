#pragma once

#include <GL/glew.h>
#include <memory>
#include <vector>
#include <unordered_map>
#include <string>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "config.h"
#include "Shader.h"
#include "Resource.h"
#include "ResourceManager.h"
#include "Logger.h"

namespace yage {
#define SHADER_VERTEX_POSITION_LOCATION = 0
#define SHADER_VERTEX_NORMAL_LOCATION = 1
#define SHADER_VERTEX_UV_POSITION = 2


/**
     * @brief Takes in shaders and links them to a program
     * 
     */
    class Program : public Resource {

    public:
        Program(Ref <Shader> vs, Ref <Shader> fs);

        ~Program();


        void attachShaders();

        void activate();

        void setInt(std::string name, int value);
        void setFloat(std::string name, float value);
        void setVec2(std::string name, glm::vec2);
        void setVec3(std::string name, glm::vec3);
        void setVec4(std::string name, glm::vec4);
        void setMat4(std::string name, glm::mat4);

    private:

        void enableInts();
        void enableFloats();
        void enableVec2s();
        void enableVec3s();
        void enableVec4s();
        void enableMat4s();

        unsigned int mGlObjectId;
        Ref <Shader> mVertexShader;
        Ref <Shader> mFragmentShader;
        std::unordered_map<std::string, int> mInts;
        std::unordered_map<std::string, int> mFloats;
        std::unordered_map<std::string, glm::vec2> mVec2s;
        std::unordered_map<std::string, glm::vec3> mVec3s;
        std::unordered_map<std::string, glm::vec4> mVec4s;
        std::unordered_map<std::string, glm::mat4> mMat4s;

    };
} // namespace yage