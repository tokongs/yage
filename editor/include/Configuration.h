#pragma once

#include <string>
#include <fstream>
#include <iostream>
#include <boost/program_options.hpp>


class Configuration {

public:
    static void Load(int argc, char **argv);
    static std::string getConfigFilePath();
    static std::string getAssetsFolderPath();

private:
    static boost::program_options::options_description cmd_options_desc;
    static boost::program_options::options_description config_file_options_desc;
    static boost::program_options::variables_map cmd_variable_map;
    static boost::program_options::variables_map config_file_variable_map;
};
