#include <fstream>
#include "Config.h"


const Config* Config::GetInstance()
{
    static Config instance;
    return &instance;
}

Config::Config()
{
    std::ifstream file("Assets/Configurations/Settings.ini");
    std::string line;

    if(!file.is_open()){
        throw std::runtime_error("failed to open settings.ini");
    }

    std::string sectionName;
    while(std::getline(file, line))
    {
        const auto npos = std::string::npos;
        const auto startPos = line.find('[');
        const auto endPos = line.find(']');
        const auto splitPos = line.find('=');

        if(startPos != npos && endPos != npos){
            sectionName = line.substr(startPos+1, endPos-1);
        }
        else if(splitPos != npos){
            std::string key = line.substr(0, splitPos);
            std::string value = line.substr(splitPos+1);
            this->configuration[sectionName][key] = value;
        }
    }
}

bool Config::IsKeyvalid(const std::string& section, const std::string& key) const
{
    if(this->configuration.count(section) == 0 || this->configuration.at(section).count(key) == 0)
        return false;
    return true;
}
