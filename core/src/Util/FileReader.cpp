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
}

std::string FileReader::readAsString(std::string file_name)
{
    std::string path = m_root_dir + file_name;
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