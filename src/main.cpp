#include <map>
#include "MyList.h"

struct hard;

using compare_type = std::common_type<int, std::int64_t>::type;
using custom_map = std::map<int, std::int64_t, std::less<compare_type>, logging_allocator<std::pair<int, std::int64_t>>>;

using hard_map = std::map<int, hard, std::less<int>, logging_allocator<std::pair<const int, hard>>>;

struct hard {
    int i;
    double d;

    hard(int i, double d) : i(i), d(d) { /*std::cout << __PRETTY_FUNCTION__ << std::endl;*/ };

    hard(const hard &)
     { /*std::cout << __PRETTY_FUNCTION__ << std::endl;*/ };

     hard(hard &&) noexcept
    { /*std::cout << __PRETTY_FUNCTION__ << std::endl;*/ };

    ~hard() { /*std::cout << __PRETTY_FUNCTION__ << std::endl;*/ };
};


int main(/*int, char *[]*/) {
//custom_map mp;
// hard_map hm;

//   for (int i = 0; i < 11; i++)
//   {
//     hm.emplace(std::piecewise_construct, 
//                std::forward_as_tuple(i), 
//                std::forward_as_tuple(i+100, i*i*i));
//   }

//   for(const auto& it : hm)
//   {
//     std::cout<< it.first << " " << it.second.i <<" "<<it.second.d << std::endl;
//   }
 
//     auto v = std::vector<hard, logging_allocator<hard>>{};
// //    v.reserve(5);
//     for (size_t i = 0; i < 11; ++i) {
//         v.emplace_back(i, i);
//         std::cout << "---" << std::endl;
//     }

//     for (auto i: v) {
//         std::cout << i.i<< " " << std::endl;
//     }

//    auto m = std::map<int, int, std::less<int>, logging_allocator<std::pair<const int, int>>>{};
//    for (size_t i = 0; i < 5; ++i) {
//        m.emplace(i, i);
//        std::cout << "---" << std::endl;
//    }

//    auto h = std::map<int, hard, std::less<int>, logging_allocator<std::pair<const int, hard>>>{};
//    for (size_t i = 0; i < 5; ++i) {
//     //    h.emplace(i, hard(i, i));
//     h.emplace(std::piecewise_construct, 
//               std::forward_as_tuple(i), 
//               std::forward_as_tuple(i, i));
//        std::cout <<"---"<< std::endl;
//    }

    return 0;
}


/*
h.emplace(std::piecewise_construct, std::forward_as_tuple(i), std::forward_as_tuple(i, i));
*/
