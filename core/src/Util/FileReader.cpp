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
    YAGE_INFO("Atempting to read file {}", file_name);

    std::ifstream file;
    std::string result;
    try{
    file.open(path.c_str(), std::ios::in);

    std::stringstream stream;
    stream << file.rdbuf();

    file.close();

    result =  stream.str();
    }catch(std::ifstream::failure e){
        YAGE_ERROR("Failed to read file: " + file_name);
    }


    YAGE_INFO("Sucessfully read file {}", file_name)
    return result;
}

bool FileReader::fileExists(std::string file){
    std::ifstream f(file.c_str());
    return f.good();
}

void FileReader::changeRootDir(std::string dir)
{
    mRootDir = dir;
}

std::string FileReader::getRootDir()
{
    return mRootDir;
}

} // namespace yage