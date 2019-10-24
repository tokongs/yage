#include <FileReader.h>
namespace yage
{

FileReader::FileReader(std::string root_dir)
{

}

FileReader::~FileReader()
{
}

std::string FileReader::readAsString(std::string file_name)
{
    std::string path = file_name;
    YAGE_INFO("Atempting to read file to string, file name: " + file_name);
    YAGE_INFO("Atempting to read file to string, file name: " + file_name);

    std::ifstream file;
    try{
    file.open(path.c_str(), std::ios::in);

    std::stringstream stream;
    stream << file.rdbuf();

    file.close();

    return stream.str();
    }catch(std::ifstream::failure e){
        YAGE_ERROR("Failed to read file: " + file_name);
         YAGE_ERROR("Failed to read file: " + file_name);
    }

    YAGE_INFO("File read successfully");
    YAGE_INFO("File read successfully");

    return "";
}

bool FileReader::fileExists(std::string file){
    std::ifstream f(file.c_str());
    return f.good();
}

void FileReader::changeRootDir(std::string dir)
{
    m_root_dir = dir;
}

std::string FileReader::getRootDir()
{
    return m_root_dir;
}

} // namespace yage