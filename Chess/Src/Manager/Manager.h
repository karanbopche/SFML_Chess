#pragma once
#include <string_view>
#include <exception>
#include "Config.h"
#include <SFML/System/NonCopyable.hpp>

template<typename Item, const std::string_view& configSection>
class Manager : private sf::NonCopyable
{
public:

    Manager(const Manager&) = delete;
    Manager(const Manager&&) = delete;
    Manager operator=(const Manager&) = delete;
    virtual ~Manager() = default;

    static Manager* GetInstance();
    const Item& GetItem(const std::string& key);
    void RemoveItem(const std::string& key);
protected:
    Manager();
    std::map<std::string, Item> ItemMap;
    std::map<std::string, std::string> keyFileMap;
};


template<typename Item, const std::string_view& configSection>
Manager<Item, configSection>::Manager()
{
    auto section = Config::GetInstance()->GetSection(std::string(configSection));
    for(auto [key, value] : section)
    {
        this->keyFileMap[key] = value;
    }
}

template<typename Item, const std::string_view& configSection>
Manager<Item, configSection>* Manager<Item, configSection>::GetInstance()
{
    static Manager ManagerInstance;
    return &ManagerInstance;
}

template<typename Item, const std::string_view& configSection>
const Item& Manager<Item, configSection>::GetItem(const std::string& key)
{
    if(this->ItemMap.count(key))
        return this->ItemMap.at(key);

    if(this->keyFileMap.count(key) == 0)
        throw std::invalid_argument(key);
    this->ItemMap[key].loadFromFile(this->keyFileMap.at(key));
    this->ItemMap[key].setSmooth(true);
    return this->ItemMap[key];
}

template<typename Item, const std::string_view& configSection>
void Manager<Item, configSection>::RemoveItem(const std::string& key)
{
    auto itr = this->ItemMap.find(key);
    if(itr != this->ItemMap.end())
        this->ItemMap.erase(itr);
}