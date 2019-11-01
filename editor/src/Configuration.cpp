#include "Configuration.h"

boost::program_options::options_description Configuration::cmd_options_desc("Allowed command line options");
boost::program_options::options_description Configuration::config_file_options_desc("Available config options");
boost::program_options::variables_map Configuration::cmd_variable_map;
boost::program_options::variables_map Configuration::config_file_variable_map;

void Configuration::Load(int argc, char **argv) {
    cmd_options_desc.add_options()
        ("config-file", boost::program_options::value<std::string>() , "Configuration file to load on startup");
    boost::program_options::store(boost::program_options::parse_command_line(argc, argv, cmd_options_desc), cmd_variable_map);
    boost::program_options::notify(cmd_variable_map);
    if(cmd_variable_map.count("config-file")){
        config_file_options_desc.add_options()
                ("assetDir", boost::program_options::value<std::string>() , "Directory to load assets from");
        try {
            std::ifstream config_file(cmd_variable_map["config-file"].as<std::string>());
            boost::program_options::store(boost::program_options::parse_config_file(config_file, config_file_options_desc), config_file_variable_map);
            boost::program_options::notify(config_file_variable_map);
            if(config_file_variable_map.count("assetDir")){
                std::cout << config_file_variable_map["assetDir"].as<std::string>() << std::endl;
            }
        }
        catch(std::exception& e){
            std::cout << e.what() << std::endl;
        }
    }
}

std::string Configuration::getConfigFilePath() {
    if(cmd_variable_map.count("config-file"))
        return cmd_variable_map["config-file"].as<std::string>();

    return nullptr;
}

std::string Configuration::getAssetsFolderPath() {
    if(config_file_variable_map.count("assetDir"))
        return config_file_variable_map["assetDir"].as<std::string>();

    return "";
}