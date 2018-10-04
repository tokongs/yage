#include <FileReader.h>
namespace yage
{
DEFINE_LOGGERS(FileReader)
FileReader::FileReader(std::string root_dir)
{

    INIT_LOGGERS(FileReader);

    if (root_dir.empty())
    {
        m_root_dir = ROOT_DIR;
    }
    else
    {
        m_root_dir = root_dir;
    }
}

FileReader::~FileReader()
{
    FLUSH_LOGGERS(FileReader);
}

std::string FileReader::readAsString(std::string file_name)
{
    std::string path = file_name;
    CONSOLE_LOGGER(FileReader, info, "Atempting to read file to string, file name: " + file_name);
    FILE_LOGGER(FileReader, info, "Atempting to read file to string, file name: " + file_name);

    std::ifstream file;
    try{
    file.open(path.c_str(), std::ios::in);

    std::stringstream stream;
    stream << file.rdbuf();

    file.close();

    return stream.str();
    }catch(std::ifstream::failure e){
        CONSOLE_LOGGER(FileReader, error, "Failed to read file: " + file_name);
        FILE_LOGGER(FileReader, error, "Failed to read file: " + file_name);
    }

    CONSOLE_LOGGER(FileReader, info, "File read successfully");
    FILE_LOGGER(FileReader, info, "File read successfully");

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