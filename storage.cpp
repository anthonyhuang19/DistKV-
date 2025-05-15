#include "storage.h"
#include<unordered_map>
#include<mutex>
using namespace std;

std::unordered_map<std::string,std::string> storage;
std::mutex store_mutex;

// store the value in storage -> exactly hashing map
void set_value(const std::string & key, const std::string & value)
{
    std::lock_guard<std::mutex> lock(store_mutex); // preventing from race condition
    storage[key]= value;
}

// getting the value by using key
std::string get_value(const std::string & key)
{
    std::lock_guard<std::mutex> lock(store_mutex);
    if(storage.find(key) != storage.end())
    {
        return storage[key] +"\n";
    }
    else
    {
        return "Not Found\n";
    }
}