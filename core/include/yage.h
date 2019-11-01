#pragma once
#include <GL/glew.h>
#include "config.h"
#include "Logger.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "MeshLoader.h"
#include "ShaderLoader.h"
#include "ScriptLoader.h"
#include "MaterialLoader.h"
#include "ScriptingEngine.h"
#include "TextureLoader.h"

namespace yage{
    class yage{
    public:
        static void InitYage();
        static void ShutdownYage();

    private:
        static MeshLoader *meshLoader;
        static ShaderLoader *shaderLoader;
        static ScriptLoader *scriptLoader;
        static MaterialLoader *materialLoader;
        static TextureLoader *textureLoader;
    };

}
