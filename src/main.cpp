#include <map>
#include "MyList.h"
#include <list>
struct hard {
    int i;
    double d;
    

    hard() : i(0), d(0) { std::cout << __PRETTY_FUNCTION__ << std::endl; };
    hard(int i, double d) : i(i), d(d) { std::cout << __PRETTY_FUNCTION__ << std::endl; };
    hard & operator=(const hard &ob) = default;
    hard(const hard &)= default;
    hard(hard &&) noexcept= default;
    friend std::ostream& operator<<(std::ostream& os,const hard& t ){
        os<<t.i<<" -- "<<t.d;
        return os;
    }
};


int main(/*int, char *[]*/) {

    List<hard,_allocator<hard,25>> lst;
    for(int i = 0;i<25;i++)
        lst.Emplace(hard{i,i*i*i});

    List<hard,_allocator<hard,25>> lst2(lst);
    auto lst3 = std::move(lst);
    
   std::cout<<lst<<std::endl;
   std::cout<<lst2<<std::endl;
   std::cout<<lst3<<std::endl;
    return 0;
}
