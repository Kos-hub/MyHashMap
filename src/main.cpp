#include <stdio.h>
#include <string>
#include "MyHashMap.h"

int main()
{
    MyHashMap<std::string, int> MyHashMap;

    MyHashMap.Add("a", 10);
    MyHashMap.Add("abc", 20);

    printf("Value from map is: %i\n", MyHashMap.Get("a"));
    printf("Value from map is: %i\n", MyHashMap.Get("abc"));

    printf("Program ending...\n");
    return 0;
}
