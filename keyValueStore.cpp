#include "keyValueStore.h"

void KeyValueStore::set(const std::string& key, const std::string& value)
{
    std::lock_guard<std::mutex> lock(mtx);
    store[key]=value;
}

std::optional<std::string> KeyValueStore::get(const std::string& key) const
{
    std::lock_guard<std::mutex> lock(mtx);
    auto it = store.find(key);
    if(it != store.end())
    {
        return it->second;
    }

    return std::nullopt;
}

bool KeyValueStore::remove(const std::string& key)
{
    std::lock_guard<std::mutex> lock(mtx);
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
    std::lock_guard<std::mutex> lock(mtx);
    return store.find(key) != store.end();
}

std::size_t KeyValueStore::size() const
{
    std::lock_guard<std::mutex> lock(mtx);
    return store.size();
}
