#include <map>
#include <iomanip>
#include "MyList.h"

int main() {
    std::map<int, hard> sMap;
    
    for(int i = 0;i<11;i++)
    sMap.emplace(std::pair<int,hard>{i,{fibonacci(i),Fact(i)}});

    for(const auto& [i, v] : sMap)
        std::cout<< setiosflags(std::ios::left)<< std::setw(2)<<i<<" "<<v<<std::endl;


    auto hMap = std::map<int, hard, std::less<int>, _allocator<std::pair<const int, hard>,10>>{};
    for(int i = 0;i<11;i++)
    hMap.emplace(std::piecewise_construct,
                 std::forward_as_tuple(i),
                 std::forward_as_tuple(fibonacci(i),Fact(i)));

    for(const auto& [i, v]: hMap)
        std::cout<< setiosflags(std::ios::left)<< std::setw(2)<<i<<" "<<v<<std::endl;


    List<hard,_allocator<hard,10>> lst;
    for(int i = 0;i<11;i++)
        lst.Emplace(hard{fibonacci(i),Fact(i)});

    //std::cout<<lst<<std::endl;
    for(auto it: lst)
        std::cout<<it<<std::endl;

    return 0;
}