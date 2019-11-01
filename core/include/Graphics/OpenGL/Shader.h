
#pragma once

#include <GL/glew.h>
#include <string>
#include <iostream>
#include <memory>
#include "config.h"
#include "Resource.h"
#include "Logger.h"
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace yage {

    class Shader : public Resource {
    public:
        /**
           * @brief Creates and compiles a vertex and fragment shader
           *
           * @param vertexCode as a string
           * @param fragmentCode as a string
           */
        Shader(std::string vsCode, std::string fsCode);

        ~Shader();

        void activate();

        void setInt(std::string name, int value);

        void setFloat(std::string name, float value);

        void setVec2(std::string name, glm::vec2);

        void setVec3(std::string name, glm::vec3);

        void setVec4(std::string name, glm::vec4);

        void setMat4(std::string name, glm::mat4);

        int getGlProgramId();

    private:

        void compileGLShader(unsigned int id, std::string code);

        void linkGlShaders(unsigned int glShaderId);

        void enableInts();

        void enableFloats();

        void enableVec2s();

        void enableVec3s();

        void enableVec4s();

        void enableMat4s();

        std::unordered_map<std::string, int> mInts;
        std::unordered_map<std::string, int> mFloats;
        std::unordered_map<std::string, glm::vec2> mVec2s;
        std::unordered_map<std::string, glm::vec3> mVec3s;
        std::unordered_map<std::string, glm::vec4> mVec4s;
        std::unordered_map<std::string, glm::mat4> mMat4s;

        int mGlProgramId = -1;
        int mGlVertexShaderId = -1;
        int mGlFragmentShaderId = -1;
    };
} // namespace yage