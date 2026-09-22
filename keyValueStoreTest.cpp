#include "keyValueStore.h"
#include <cassert>
#include <iostream>

int main()
{
    KeyValueStore kv;
    assert(kv.size()==0);

    kv.set("name","Alice");
    std::optional<std::string> res1 = kv.get("name");
    assert(res1);
    assert(*res1=="Alice");        
    
    
    assert(kv.contains("name"));
    assert(kv.size()==1);

    kv.set("name","Larry");

    std::optional<std::string> res2 = kv.get("name");
    assert(res2);
    assert(*res2=="Larry");        
    

    assert(kv.remove("name"));
    assert(!kv.contains("name"));
    assert(!kv.remove("name"));

    std::optional<std::string> res3 = kv.get("name");
    assert(!res3);
    assert(kv.size()==0);
    std::cout<< "All tests passed \n";
    return 0;
}