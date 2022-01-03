// Copyright BattleDash. All Rights Reserved.

#include <Util/PropertiesFormat.h>

#include <ctime>
#include <fstream>

namespace mpp
{
Properties::Properties(const String& filePath) : m_filePath(filePath), m_failedToLoad(false), m_dirty(false)
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
        String line;
        while (std::getline(file, line))
        {
            if (line.rfind("#", 0) == 0)
            {
                m_comments.push_back(line.substr(1));
            }
            else
            {
                m_properties.insert(std::make_pair(line.substr(0, line.find('=')), line.substr(line.find('=') + 1)));
            }
        }
        file.close();
        return true;
    }
    return false;
}

bool Properties::Save() const
{
    if (!m_dirty)
    {
        return false;
    }
    std::ofstream file(m_filePath.c_str());
    if (file.is_open())
    {
        for (const String& comment : m_comments)
        {
            file << "#" << comment << std::endl;
        }
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
    m_dirty = true;
}

void Properties::AddComment(const String& comment)
{
    m_comments.push_back(comment);
    m_dirty = true;
}

std::vector<String> Properties::GetComments() const
{
    return m_comments;
}
} // namespace mpp