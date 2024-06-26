#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include <algorithm>

struct Bitfield {
    u_int value:5 = 0;

};

std::ostream& operator<<(std::ostream& out, const Bitfield& b) {
        out << b.value << '\n';
        return out;
    }

int main(){

Bitfield b;
std::cout << b.value << " " << sizeof(b) << '\n';

for (int i = 0; i < 10; ++i){
    ++b.value;
    std::cout << b;
}

   return 0;
}