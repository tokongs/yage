#include "ResourceManager.h"

namespace yage {
    ResourceManager::ResourceManager() {
    }

    ResourceManager::~ResourceManager() {
    }

    void ResourceManager::loadAllResources() {

        std::vector<std::string> files = traverseDirectories(mResourceDir);
        FileReader reader;
        for (auto filePath : files) {
            std::string fileConent = reader.readAsString(filePath);
            pugi::xml_document doc;
            pugi::xml_parse_result result = doc.load_string(fileConent.c_str());
            if (result) {
                pugi::xml_node root = doc.first_child();
                mFilePaths[std::string(root.attribute("name").value())] = filePath;
            }
        }

        for (auto filePath: files) {
            std::string fileConent = reader.readAsString(filePath);
            pugi::xml_document doc;
            pugi::xml_parse_result result = doc.load_string(fileConent.c_str());
            if (result) {
                if (mLoadedResources.find(std::string(doc.first_child().attribute("name").value())) != mLoadedResources.end()) {
                    YAGE_INFO("Resource {} already loaded. SKipping...", doc.first_child().attribute("name").value());
                    continue;
                }
                loadResource(doc.first_child());
            }
        }
    }

    std::vector<std::string> ResourceManager::traverseDirectories(std::string baseDir) {
        std::vector<std::string> result;
        for (auto &entry : std::filesystem::directory_iterator(baseDir)) {
            if (entry.is_directory()) {
                std::vector<std::string> dirContents = traverseDirectories(entry.path());
                result.insert(result.end(), dirContents.begin(), dirContents.end());
            } else {
                if (entry.is_regular_file() && entry.path().extension() == ".xml") {
                    result.push_back(entry.path());
                }
            }
        }

        return result;
    }


    void ResourceManager::loadResource(pugi::xml_node root) {
        if (mLoadedResources.find(std::string(root.attribute("name").value())) != mLoadedResources.end()) {
            YAGE_INFO("Resource {} already loaded. SKipping...", root.attribute("name").value());
        }
        pugi::xml_node current = root.first_child();
        while (!current.empty()) {
            loadResource(current);
            current = current.next_sibling();
        }
        auto loader = mLoaders.find(root.name());
        if (loader == mLoaders.end()) {
            YAGE_WARN("Failed to find loader for resource of type {}.", root.attribute("name").value())
            return;
        }
        Resource *res = loader->second->load(mFilePaths[root.attribute("name").value()]);
        if (res) {
            int id = -1;
            if (mFreeIds.empty()) {
                id = mCurrentId;
                mCurrentId++;
            } else {
                id = mFreeIds.top();
            }

            mLoadedResources[root.attribute("name").value()] = Ref<Resource>(res);
            res->setId(id);
            res->setName(root.attribute("name").value());
            res->setFilePath(mFilePaths[root.attribute("name").value()]);
        }

    }

    void ResourceManager::registerResourceLoader(std::string resourceTypeName, ResourceLoader *loader) {
        if (!loader) {
            YAGE_ERROR("Trying to register nullptr as a resource loader");
            return;
        }

        mLoaders[resourceTypeName] = loader;
    }


    void ResourceManager::setResourceDir(std::string resource_dir) {
        mResourceDir = resource_dir;
    }

    std::unordered_map<std::string, Ref<Resource>> ResourceManager::getResourceMap() const {
        return mLoadedResources;
    }
} // namespace yage
