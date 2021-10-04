#include <map>
#include "MyList.h"

struct hard {
    int i;
    double d;

    hard(int i, double d) : i(i), d(d) { std::cout << __PRETTY_FUNCTION__ << std::endl; };
    hard & operator=(const hard &ob) = default;
    hard(const hard &)
    { std::cout << __PRETTY_FUNCTION__ << std::endl; };

     hard(hard &&) noexcept
    { std::cout << __PRETTY_FUNCTION__ << std::endl; };

    ~hard() { std::cout << __PRETTY_FUNCTION__ << std::endl; };
    friend std::ostream& operator<<(std::ostream& os,const hard& t )
    {
        os<<t.i<<" -- "<<t.d;
        return os;
    }
};


int main(/*int, char *[]*/) {

    List<int> lst;
    for(int i = 0;i<25;i++)
        lst.Emplace(i*i*i);
    List<int> lst2(lst);
    List<int> lst3 = std::move(lst);

 //   std::cout<<lst<<std::endl;
  //  std::cout<<lst2<<std::endl;
 //   std::cout<<lst3<<std::endl;
    return 0;
}
