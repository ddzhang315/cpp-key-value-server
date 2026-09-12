#include "keyValueStore.h"

void KeyValueStore::set(const std::string& key, const std::string& value)
{
    store[key]=value;
}

std::optional<std::string> KeyValueStore::get(const std::string& key) const
{
    auto it = store.find(key);
    if(it != store.end())
    {
        return it->second;
    }

    return std::nullopt;
}

bool KeyValueStore::remove(const std::string& key)
{
    auto it = store.find(key);
    if(it != store.end())
    {
        store.erase(it);
        return true;
    }

    return false;
}

bool KeyValueStore::contains(const std::string& key) const
{
    return store.find(key) != store.end();
}

std::size_t KeyValueStore::size() const
{
    return store.size();
}
