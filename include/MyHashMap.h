#pragma once
#include <type_traits>
#include <typeinfo>
#include <stdio.h>
#include <string>

template<class K, class V>
struct Node
{
    K key;
    V value;
    Node* next;
    bool init = false;
};

template <class K, class V> class MyHashMap
{
public:
    MyHashMap();
    ~MyHashMap();

    void Add(K key, V value);
    V Get(K key);
private:
    Node<K, V>* values;

    int* sizes;
    int sizeIdx = 2;

    int capacity;
    int currSize = 0;


    int HashValue(K key);
    int Rehash();

    void GenerateSizes();
};

template <class K, class V>
MyHashMap<K, V>::MyHashMap()
{
    printf("Creating MyHashMap... with type %s and %s\n", typeid(K).name(), typeid(V).name());
    sizes = new int[10];
    GenerateSizes();

    values = new Node<K, V>[sizes[sizeIdx]]{};
    capacity = sizes[sizeIdx] - 2; 
}

template <class K, class V> 
MyHashMap<K, V>::~MyHashMap()
{
    printf("Deleting MyHashMap... with type %s and %s\n", typeid(K).name(), typeid(V).name());
    delete[] values;
    delete[] sizes;
}


template <class K, class V>
void MyHashMap<K, V>::Add(K key, V value)
{
    // Hash the key first. We need to know if it's a collision or not
    int index = HashValue(key);

    Node<K, V> node = Node<K, V>{key, value, nullptr, true};

    if (values[index].init)
    {
        values[index].next = node.next;

        return;
    }

    if (index >= 0 && index < sizes[sizeIdx])
    {
        values[index] = node;
        currSize++;
    }
    else
    {
        printf("Calculated index is out of bounds\n");
    }

    if (currSize >= capacity)
    {
        printf("Capacity has been reached. Reallocating...\n");

        sizeIdx++;
        Node<K, V>* newValues = new Node<K, V>[sizeIdx];
        capacity = sizes[sizeIdx] - 2;

        std::copy(values, values + sizes[sizeIdx - 1], newValues);

        delete[] values;

        values = newValues;
        printf("New capacity is: %i\n", capacity);
    }
}

template <class K, class V>
V MyHashMap<K, V>::Get(K key)
{
    int index = HashValue(key);

    if (index >= 0 && index < sizes[sizeIdx])
    {
        return values[index].value;
    }
    else
    {
        printf("Index out of bounds\n");
        return V{};
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

    unsigned long hash = 5381;
    for (const char& c : keyStr)
    {
        hash = ((hash << 5) + hash) + c;
    }

    return hash % sizes[sizeIdx];
}


template<class K, class V>
int MyHashMap<K, V>::Rehash()
{

    return 0;
}

template<class K, class V>
void MyHashMap<K, V>::GenerateSizes()
{
    bool* isComposite = new bool[31]{};

    for (int i = 2; i*i <= 31; i++)
    {
        bool current = isComposite[i];

        if (current)
        {
            continue;
        }

        for (int j = i * i; j <= 31; j += i)
        {
            isComposite[j] = true;
        }
    }


    int idx = 0;
    for (int i = 2; i <= 31; i++)
    {
        if (!isComposite[i])
        {
            if (idx >= 0 && idx < 10)
            {
                sizes[idx] = i;
                idx++;
            }
        }
    }

}

