// Copyright BattleDash. All Rights Reserved.

#include <Util/Properties.h>

#include <fstream>

namespace mpp
{
Properties::Properties(const String& filePath) : m_filePath(filePath)
{
    m_failedToLoad = !Load();
}

Properties::~Properties()
{
}

bool Properties::IsLoaded() const
{
    return !m_failedToLoad;
}

bool Properties::Load()
{
    std::ifstream file(m_filePath.c_str());
    if (file.is_open())
    {
        std::string line;
        while (std::getline(file, line))
        {
            m_properties.insert(std::make_pair(line.substr(0, line.find('=')), line.substr(line.find('=') + 1)));
        }
        file.close();
        return true;
    }
    return false;
}

bool Properties::Save() const
{
    std::ofstream file(m_filePath.c_str());
    if (file.is_open())
    {
        for (auto& property : m_properties)
        {
            file << property.first << "=" << property.second << std::endl;
        }
        file.close();
        return true;
    }
    return false;
}

bool Properties::HasKey(const String& key) const
{
    return m_properties.find(key) != m_properties.end();
}

void Properties::SetValue(const String& key, const String& value)
{
    m_properties[key] = value;
}
} // namespace mpp