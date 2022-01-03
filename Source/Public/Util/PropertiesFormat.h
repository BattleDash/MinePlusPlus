// Copyright BattleDash. All Rights Reserved.

#pragma once

#include <Base/Log.h>
#include <Base/Platform.h>
#include <Base/String.h>

#include <map>
#include <sstream>
#include <string>
#include <vector>

namespace mpp
{
class Properties
{
  public:
    MPP_API Properties(const String& filePath);
    MPP_API ~Properties();

    MPP_API bool IsLoaded() const;
    MPP_API bool Load();
    MPP_API bool Save() const;
    MPP_API bool HasKey(const String& key) const;
    MPP_API void SetValue(const String& key, const String& value);
    MPP_API void AddComment(const String& comment);
    MPP_API std::vector<String> GetComments() const;

    // Must be defined in the header, because it's templated.
    template <typename T> MPP_API T GetValue(const String& key, T def)
    {
        if (HasKey(key))
        {
            String input = m_properties.at(key);
            // NOTE: Strings will fail here if empty, and return def.
            T value;
            if (std::istringstream(input) >> std::boolalpha >> value)
            {
                return value;
            }
            else
            {
                return def;
            }
        }
        std::ostringstream oss;
        oss << std::boolalpha << def;
        SetValue(key, oss.str());
        return def;
    }

  private:
    String m_filePath;
    std::map<String, String> m_properties;
    std::vector<String> m_comments;
    bool m_failedToLoad;
    bool m_dirty;
};
} // namespace mpp