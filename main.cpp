#include <iostream>
#include "keyValueStore.h"
#include <cassert>


int main()
{
    std::cout<< "C++ Key Value Server" << std::endl;

    KeyValueStore kv;
    kv.set("fruit","apple");

    assert(kv.contains("fruit"));
    assert(kv.size()==1);

    auto result = kv.get("fruit");
    assert(result.has_value());
    assert(*result == "apple");

    kv.set("vegetable","cabbage");
    assert(kv.size()==2);

    kv.set("fruit","mango");
    assert(kv.size()==2);
    auto updated = kv.get("fruit");
    assert(updated.has_value());
    assert(*updated == "mango");

    assert(!kv.remove("water"));

    assert(kv.remove("fruit"));
    assert(!kv.contains("fruit"));
    assert(kv.size()==1);


    return 0;
}