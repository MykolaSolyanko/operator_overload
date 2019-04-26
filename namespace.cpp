#include <iostream>

namespace A {
  class Test {
    public:
      Test() {
       std::cout << __PRETTY_FUNCTION__ << std::endl;
      }
  };
}

namespace B {
  void print() {
    std::cout << __PRETTY_FUNCTION__ << std::endl;
  }
  class Test {
   public:
    Test() {
      print();
      std::cout << __PRETTY_FUNCTION__ << std::endl;
    }
  };
}

int main(int argc, char const *argv[]) {
    A::Test testA;
    //B::Test testB;
    using namespace B;
    Test testB;
    return 0;
}
