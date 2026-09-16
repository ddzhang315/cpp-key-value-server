#ifndef KEYVALUESTORE_H
#define KEYVALUESTORE_H

#include <unordered_map>
#include <string>
#include <optional>
#include <cstddef>
#include <mutex>


class KeyValueStore{

private:
    std::unordered_map<std::string,std::string> store;
    mutable std::mutex mtx;

public:
    void set(const std::string& key, const std::string& value);
    std::optional<std::string> get(const std::string& key) const;
    bool remove(const std::string& key);
    bool contains(const std::string& key) const;
    std::size_t size() const;
};

#endif