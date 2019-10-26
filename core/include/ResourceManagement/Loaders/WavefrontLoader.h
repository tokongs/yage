#pragma once
#include "config.h"
#include "string"
#include "VertexBuffer.h"
#include <vector>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

namespace yage{
    /**
     * @brief A loader for .obj wavefront files. 
     * 
     */
    class WavefrontLoader{
        public:
        WavefrontLoader();
        ~WavefrontLoader();

        /**
         * @brief Return a vertex buffer as a smart pointer
         * 
         * @param file Content of a wavefront file as a string
         * @return VertexBufferPtr 
         */
        VertexBuffer* loadWavefront(std::string file);
    };
}