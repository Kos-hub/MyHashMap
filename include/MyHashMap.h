#pragma once
#include <cstddef>
#include <type_traits>
#include <typeinfo>
#include <stdio.h>
#include <string>
template <class K, class V> class MyHashMap
{
public:
    MyHashMap();
    ~MyHashMap();

    void Add(K key, V value);
    V Get(K key);
private:
    V* _values;
    int size = 5;


    int HashValue(K key);

};

template <class K, class V>
MyHashMap<K, V>::MyHashMap()
{
    printf("Creating MyHashMap... with type %s and %s\n", typeid(K).name(), typeid(V).name());
    _values = new V[size]{};
}

template <class K, class V> 
MyHashMap<K, V>::~MyHashMap()
{
    printf("Deleting MyHashMap... with type %s and %s\n", typeid(K).name(), typeid(V).name());
    delete[] _values;
}


template <class K, class V>
void MyHashMap<K, V>::Add(K key, V value)
{
    printf("Adding values...\n");

    int index = HashValue(key);

    printf("Calculated Index is: %i\n", index);

    if (index >= 0 && index < size)
    {
        _values[index] = value;
    }
    else
    {
        printf("Calculated index is out of bounds\n");
    }
}

template <class K, class V>
V MyHashMap<K, V>::Get(K key)
{
    int index = HashValue(key);

    if (index >= 0 && index < size)
    {
        return _values[index];
    }
    else
    {
        printf("Index out of bounds\n");
        return NULL;
    }
}

template <class K, class V>
int MyHashMap<K, V>::HashValue(K key)
{
    std::string keyStr;
    if constexpr (std::is_arithmetic<K>::value)
    {
        keyStr = std::to_string(key);
    }
    else if constexpr (std::is_same<K, std::string>::value)
    {
        keyStr = key;
    }
    else
    {
        printf("Unsupported conversion");
    }

    int hashVal = 0;
    for(const auto& c: keyStr)
    {
        hashVal += c;
    }

    printf("Hashed value is: %i\n", hashVal % 5);
    return hashVal % 5;
}
