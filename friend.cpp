#include <iostream>

class Test {
 public:
   Test(int a, int b) :a(a), b(b){}
 private:
   int a;
   int b;
   friend std::ostream& operator <<(std::ostream&, const Test&);
   friend class Friend;
};

class Friend {
  public:
   void inc_Test(Test& test) {
     ++test.a;
     ++test.b;
   }
};

std::ostream& operator <<(std::ostream& os, const Test& test) {
  os << test.a << " " << test.b << std::endl;
  return os;
}

int main(int argc, char const *argv[]) {
    Test t{1, 2};
    std::cout << t << std::endl;
    Friend().inc_Test(t);
    std::cout << t << std::endl;
    return 0;
}
