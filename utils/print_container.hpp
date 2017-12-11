#include <iostream>
#include <map>

template <typename T1, typename T2>
void print(std::map<T1, T2> container)
{
    int i = 0;
    for (const auto& obj : container)
    {
        std::cout << i++ << " : " << obj.first << " : " << obj.second << std::endl;
    }
}

template <typename T>
void print(T container)
{
    int i = 0;
    for (const auto& obj : container)
    {
        std::cout << i++ << " : " << obj <<std::endl;
    }
}
