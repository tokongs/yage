#include <Shader.h>

namespace yage {
    Shader::Shader(std::string vsCode, std::string fsCode) {



        // vertex Shader

        mGlVertexShaderId = glCreateShader(GL_VERTEX_SHADER);
        mGlFragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
        mGlProgramId = glCreateProgram();
        compileGLShader(mGlVertexShaderId, vsCode);
        compileGLShader(mGlFragmentShaderId, fsCode);
        linkGlShaders(mGlVertexShaderId);
        linkGlShaders(mGlFragmentShaderId);
    }

    Shader::~Shader() {
        YAGE_INFO("Deleting vertex shader with id: " + std::to_string(mGlVertexShaderId));
        glDeleteShader(mGlVertexShaderId);
        YAGE_INFO("Deleting fragment shader with id: " + std::to_string(mGlFragmentShaderId));
        glDeleteShader(mGlFragmentShaderId);
        YAGE_INFO("Deleting shader program with id: " + std::to_string(mGlProgramId));
        glDeleteShader(mGlProgramId);
    }

    void Shader::compileGLShader(unsigned int id, std::string code) {
        YAGE_INFO("Compiling OpenGL vertex shader");
        const char *c_code = code.c_str();
        int success;
        char info_log[512];
        glShaderSource(id, 1, &c_code, NULL);
        glCompileShader(mGlVertexShaderId);
        // print compile errors if any
        glGetShaderiv(mGlVertexShaderId, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(mGlVertexShaderId, 512, NULL, info_log);
            YAGE_ERROR(info_log);
            return;
        };
        YAGE_INFO("Shader successfully complied with id: " + std::to_string(id));
    }

    void Shader::linkGlShaders(unsigned int shaderId) {
        YAGE_INFO("Linking shader({}) with program({})", shaderId, mGlProgramId);
        glAttachShader(mGlProgramId, shaderId);
        glLinkProgram(mGlProgramId);

        GLint success;
        char info_log[512];

        glGetProgramiv(mGlProgramId, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(mGlProgramId, 512, NULL, info_log);
            YAGE_ERROR(info_log);
            return;
        } else {
            YAGE_INFO("Shader linking successful.");
        }

    }

    void Shader::activate() {
        glUseProgram(mGlProgramId);
        enableInts();
        enableFloats();
        enableVec2s();
        enableVec3s();
        enableVec4s();
        enableMat4s();
    }

    void Shader::enableInts() {
        for (auto it : mInts) {
            int loc = glGetUniformLocation(mGlProgramId, it.first.c_str());
            if (loc != -1) {
                glUniform1i(loc, it.second);
            }
        }
    }


    void Shader::enableFloats() {
        for (auto it : mFloats) {
            int loc = glGetUniformLocation(mGlProgramId, it.first.c_str());
            if (loc != -1) {
                glUniform1f(loc, it.second);
            }
        }
    }


    void Shader::enableVec2s() {
        for (auto it : mVec2s) {
            int loc = glGetUniformLocation(mGlProgramId, it.first.c_str());
            if (loc != -1) {
                glUniform2f(loc, it.second.x, it.second.y);
            }
        }
    }

    void Shader::enableVec3s() {
        for (auto it : mVec3s) {
            int loc = glGetUniformLocation(mGlProgramId, it.first.c_str());
            if (loc != -1) {
                glUniform3f(loc, it.second.x, it.second.y, it.second.z);
            }
        }
    }

    void Shader::enableVec4s() {
        for (auto it : mVec4s) {
            int loc = glGetUniformLocation(mGlProgramId, it.first.c_str());
            if (loc != -1) {
                glUniform4f(loc, it.second.x, it.second.y, it.second.z, it.second.w);
            }
        }
    }

    void Shader::enableMat4s() {
        for (auto it : mMat4s) {
            int loc = glGetUniformLocation(mGlProgramId, it.first.c_str());
            if (loc != -1) {
                glUniformMatrix4fv(loc, 1, GL_FALSE, &it.second[0][0]);
            }
        }
    }


    void Shader::setInt(std::string name, int value) {
        mInts[name] = value;
    }

    void Shader::setFloat(std::string name, float value) {
        mFloats[name] = value;
    }

    void Shader::setVec2(std::string name, glm::vec2 value) {
        mVec2s[name] = value;
    }

    void Shader::setVec3(std::string name, glm::vec3 value) {
        mVec3s[name] = value;
    }

    void Shader::setVec4(std::string name, glm::vec4 value) {
        mVec4s[name] = value;
    }

    void Shader::setMat4(std::string name, glm::mat4 value) {
        mMat4s[name] = value;
    }

    int Shader::getGlProgramId() {
        return mGlProgramId;
    }
} // namespace yage