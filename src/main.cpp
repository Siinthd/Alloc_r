#include <map>
#include <iomanip>
#include "MyList.h"
#include <list>

int fibonacci(int number)
{
    if (number == 0)
        return 0;
    if (number == 1)
        return 1;
    return fibonacci(number-1) + fibonacci(number-2);
}

double Fact(int x) 
{ 
    if (x==0)
    return 1;
    return x*Fact(x-1);
}

struct hard {
    int i;
    double d;

    hard() : i(0), d(0) { /*std::cout << __PRETTY_FUNCTION__ << std::endl;*/ };
    hard(int i, double d) : i(i), d(d) { /*std::cout << __PRETTY_FUNCTION__ << std::endl;*/ };
    hard & operator=(const hard &ob) = default;
    hard(const hard &)= default;
    hard(hard &&) noexcept= default;
    friend std::ostream& operator<<(std::ostream& os,const hard& t ){
        os<< setiosflags(std::ios::left)<< std::setw(2) <<t.i<<" -- "<<t.d;
        return os;
    }
};


int main() {

    List<hard,_allocator<hard,10>> lst;
    for(int i = 0;i<11;i++)
        lst.Emplace(hard{fibonacci(i),Fact(i)});
   std::cout<<lst<<std::endl;
    return 0;
}





// • создание экземпляра std::map<int, hard>
// • заполнение 10 элементами, где ключ это число от 0 до 9, а значение - соответствующие значению ключа факториал и число Фибоначчи
// • создание экземпляра std::map<int, hard> с новым аллокатором ограниченным 10 элементами
// • заполнение 10 элементами, где ключ это число от 0 до 9, а значение - аналогичные первому контейнеру
// • вывод на экран всех значений (ключ и значения разделены пробелами) хранящихся в контейнере
// + создание экземпляра своего контейнера для хранения hard
// • заполнение 10 значениями аналогичными первому контейнеру
// • создание экземпляра своего контейнера для хранения hard с новым аллокатором ограниченным 10 элементами
// • заполнение 10 значениями аналогичными первому контейнеру
// • вывод на экран всех значений хранящихся в контейнере


// hard(const hard &) и hard(hard &&) noexcept помечены как delete и реализована идеальная передача.
// +  Контейнер имеет публичный и приватный интерфейсы.
// Вывод данных контейнера через for-loop.
// + Реализованы копирующий и перемещающий конструкторы при совпадении типа аллокатора. В коде есть пример.
// + Реализованы копирующий и перемещающий конструкторы при отличающихся типах аллокатора. В коде есть пример.
// + Аллокатор может расширяться с шагом 10. В коде все циклы увеличены на 1, чтобы спровоцировать расширение.