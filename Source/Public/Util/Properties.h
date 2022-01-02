// Copyright BattleDash. All Rights Reserved.

#pragma once

#include <Base/Platform.h>
#include <Base/String.h>
#include <Base/Log.h>

#include <map>
#include <sstream>

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
    template <typename T> MPP_API T GetValue(const String& key, T def) const
    {
        if (HasKey(key))
        {
            String input = m_properties.at(key);
            if (input == "true")
            {
                input = "1";
            }
            else if (input == "false")
            {
                input = "0";
            }
            T value;
            if (std::istringstream(input) >> value)
            {
                return value;
            }
            else
            {
                MPP_LOG(LogLevel::Error, "Failed to parse value for key: " + key);
                return def;
            }
        }
        return def;
    }

    MPP_API void SetValue(const String& key, const String& value);

  private:
    String m_filePath;
    std::map<String, String> m_properties;
    bool m_failedToLoad;
};
} // namespace mpp