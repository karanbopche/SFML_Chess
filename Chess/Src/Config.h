#pragma once

#include <map>
#include <string>

class Config
{
public:
    using Section = std::map<std::string, std::string>;

    static const Config *GetInstance();
    inline const std::string &GetConfigString(const std::string &section, const std::string &key) const { return this->configuration.at(section).at(key); }
    inline int GetConfigInt(const std::string &section, const std::string &key) const { return std::stoi(this->configuration.at(section).at(key)); }
    inline float GetConfigFloat(const std::string &section, const std::string &key) const { return std::stof(this->configuration.at(section).at(key)); }
    inline const Section &GetSection(const std::string &section) const { return this->configuration.at(section); }
    bool IsKeyvalid(const std::string &section, const std::string &key) const;

protected:
    Config();

    std::map<std::string, Section> configuration;
};