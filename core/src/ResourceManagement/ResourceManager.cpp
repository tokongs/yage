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
            rapidxml::xml_document<> document;
            document.parse<0>(fileConent.data());
            rapidxml::xml_node<> *node = document.first_node();

            auto typeIndex = xmlTypeToTypeIndex.find(node->name());
            if (typeIndex == xmlTypeToTypeIndex.end()) {
                YAGE_WARN("Failed to find mapping between xml node type({}) and loader type.", node->name())
                continue;
            }
            auto loader = mLoaders.find(typeIndex->second);
            if (loader == mLoaders.end()) {
                YAGE_WARN("Failed to find loader for resource of type {}.", node->name())
                continue;
            }

            YAGE_INFO("Start loading resource (name: {}, filePath: {})", node->name(), filePath);
            Resource *res = loader->second->load(fileConent);
            if (res) {
                int id = -1;
                if (mFreeIds.empty()) {
                    id = mCurrentId;
                    mCurrentId++;
                } else {
                    id = mFreeIds.top();
                }
                mIndices[res->getName()] = id;
                mLoadedResources[id] = Ref<Resource>(res);
                res->setId(id);
                res->setFilePath(filePath);
                YAGE_INFO("Finished loading resource (name: {}, id: {}, filePath: {}", node->name(), id, filePath);
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

    void ResourceManager::setResourceDir(std::string resource_dir) {
        FileReader reader;
        std::string resource_overview = reader.readAsString(resource_dir + "resource_overview");
        mResourceDir = resource_dir;

        if (resource_overview.empty()) {
            YAGE_WARN("Resource Overview File is empty");
        }
        buildFilePathMap(resource_overview);
    }

    void ResourceManager::buildFilePathMap(std::string resource_overview) {
        auto start_of_type = resource_overview.find_first_of('#');
        while (start_of_type != std::string::npos) {
            auto start_of_name = resource_overview.find_first_of(' ', start_of_type + 1) + 1;
            auto start_of_path = resource_overview.find_first_of(' ', start_of_name) + 1;
            auto end_of_path = resource_overview.find_first_of('\n', start_of_path) + 1;
            if (end_of_path == std::string::npos) {
                end_of_path = resource_overview.size();
            }

            std::string name = resource_overview.substr(start_of_name, start_of_path - start_of_name - 1);
            std::string path = resource_overview.substr(start_of_path, end_of_path - start_of_path - 1);

            path = mResourceDir + path;

            mFilePaths[name] = path;

            start_of_type = resource_overview.find_first_of('#', start_of_type + 1);
        }
    }

    std::unordered_map<int, Ref<Resource>> ResourceManager::getResourceMap() const {
        return mLoadedResources;
    }
} // namespace yage
