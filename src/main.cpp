#include <stdio.h>
#include <string>
#include "MyHashMap.h"

int main()
{
    MyHashMap<std::string, int> MyHashMap;

    MyHashMap.Add("a", 10);

    auto value = MyHashMap.Get("a");

    printf("Value from map is: %i\n", value);

    printf("Program ending...\n");
    return 0;
}
