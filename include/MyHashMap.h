#pragma once
#include <algorithm>
#include <cstddef>
#include <type_traits>
#include <typeinfo>
#include <stdio.h>
#include <string>

template<class V>
struct Node
{
    std::string key;
    V value;
    next *Bucket

};
template <class K, class V> class MyHashMap
{
public:
    MyHashMap();
    ~MyHashMap();

    void Add(K key, V value);
    V Get(K key);
private:
    V* values;
    int size = 5;
    int currSize = 0;
    int capacity = 3;


    int HashValue(K key);
    int Rehash();

};

template <class K, class V>
MyHashMap<K, V>::MyHashMap()
{
    printf("Creating MyHashMap... with type %s and %s\n", typeid(K).name(), typeid(V).name());
    values = new V[size]{};
}

template <class K, class V> 
MyHashMap<K, V>::~MyHashMap()
{
    printf("Deleting MyHashMap... with type %s and %s\n", typeid(K).name(), typeid(V).name());
    delete[] values;
}


template <class K, class V>
void MyHashMap<K, V>::Add(K key, V value)
{
    printf("Adding values...\n");

    int index = HashValue(key);

    printf("Calculated Index is: %i\n", index);

    if (index >= 0 && index < size)
    {
        values[index] = value;
        currSize++;
    }
    else
    {
        printf("Calculated index is out of bounds\n");
    }

    if (currSize >= 2)
    {
        printf("Capacity has been reached. Reallocating...\n");
        size += 3;
        int* newValues = new int[size];
        capacity = size - 2;
        std::copy(values, values + (size - 3), newValues);

        delete[] values;

        values = newValues;
        printf("New capacity is: %i\n", capacity);
    }
}

template <class K, class V>
V MyHashMap<K, V>::Get(K key)
{
    int index = HashValue(key);

    if (index >= 0 && index < size)
    {
        return values[index];
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

    printf("Hashed value is: %i\n", hashVal % size);
    return hashVal % size;
}

template<class K, class V>
int MyHashMap<K, V>::Rehash()
{
    for (int i = 0; i < size; i++)
    {

    }

}
