#include "Program.h"

namespace yage {
    Program::Program(Ref<Shader> vs, Ref<Shader> fs)
            : mVertexShader(vs), mFragmentShader(fs) {
        mGlObjectId = glCreateProgram();
        YAGE_INFO("Created program with id: " + std::to_string(mGlObjectId));
        attachShaders();
    }

    Program::~Program() {
        YAGE_INFO("Deleting program with id: " + std::to_string(mGlObjectId));
        glDeleteProgram(mGlObjectId);
    }

    void Program::activate() {
        glUseProgram(mGlObjectId);
        enableInts();
        enableFloats();
        enableVec2s();
        enableVec3s();
        enableVec4s();
        enableMat4s();
    }

    void Program::enableInts() {
        for(auto it : mInts){
            int loc = glGetUniformLocation(mGlObjectId, it.first.c_str());
            if(loc != -1){
                glUniform1i(loc, it.second);
            }
        }
    }


    void Program::enableFloats() {
        for(auto it : mFloats){
            int loc = glGetUniformLocation(mGlObjectId, it.first.c_str());
            if(loc != -1){
                glUniform1f(loc, it.second);
            }
        }
    }


    void Program::enableVec2s() {
        for(auto it : mVec2s){
            int loc = glGetUniformLocation(mGlObjectId, it.first.c_str());
            if(loc != -1){
                glUniform2f(loc, it.second.x, it.second.y);
            }
        }
    }

    void Program::enableVec3s() {
        for(auto it : mVec3s){
            int loc = glGetUniformLocation(mGlObjectId, it.first.c_str());
            if(loc != -1){
                glUniform3f(loc, it.second.x, it.second.y, it.second.z);
            }
        }
    }

    void Program::enableVec4s() {
        for(auto it : mVec4s){
            int loc = glGetUniformLocation(mGlObjectId, it.first.c_str());
            if(loc != -1){
                glUniform4f(loc, it.second.x, it.second.y, it.second.z, it.second.w);
            }
        }
    }

    void Program::enableMat4s() {
        for(auto it : mMat4s){
            int loc = glGetUniformLocation(mGlObjectId, it.first.c_str());
            if(loc != -1){
                glUniformMatrix4fv(loc, 1, GL_FALSE, &it.second[0][0]);
            }
        }
    }

    void Program::attachShaders() {
        YAGE_INFO("Linking VertexShader" + mVertexShader->getName() + " to program " + std::to_string(mGlObjectId));
        glAttachShader(mGlObjectId, mVertexShader->getGLObjectId());
        glLinkProgram(mGlObjectId);
        YAGE_INFO("Linking FragmentShader" + mFragmentShader->getName() + " to program " + std::to_string(mGlObjectId));
        glAttachShader(mGlObjectId, mFragmentShader->getGLObjectId());
        glLinkProgram(mGlObjectId);

        GLint success;
        char info_log[512];

        glGetProgramiv(mGlObjectId, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(mGlObjectId, 512, NULL, info_log);
            YAGE_ERROR(info_log);
            return;
        } else {
            YAGE_INFO("Shader linking successful.");
        }

    }


    void Program::setInt(std::string name, int value) {
        mInts[name] = value;
    }

    void Program::setFloat(std::string name, float value) {
        mFloats[name] = value;
    }

    void Program::setVec2(std::string name, glm::vec2 value) {
        mVec2s[name] = value;
    }

    void Program::setVec3(std::string name, glm::vec3 value) {
        mVec3s[name] = value;
    }

    void Program::setVec4(std::string name, glm::vec4 value) {
        mVec4s[name] = value;
    }

    void Program::setMat4(std::string name, glm::mat4 value) {
        mMat4s[name] = value;
    }
} // namespace yage