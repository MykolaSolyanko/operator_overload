#include <iostream>

class Int {
 public:
  /*explicit*/ Int(int value = 0) : value(value) {
  }
  int GetValue() {
    return value;
  }
  Int& operator+= (const Int& rhl) {
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    value += rhl.value;
    return *this;
  }

  Int& operator-= (const Int& rhl) {
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    value -= rhl.value;
    return *this;
  }

  Int& operator++ () {
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    ++value;
    return *this;
  }

  const Int operator++ (int unused) {
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    Int tmp = *this;
    ++value;
    return tmp;
  }

/*  const Int operator+ (const Int& rhl) {
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    Int tmp = *this;
    return tmp += rhl;
  }
*/

/*  const Int operator- (const Int& rhl) {
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    Int tmp = *this;
    return tmp -= rhl;
  }
*/
 private:
  int value;
};

const Int operator+ (const Int& lvl, const Int& rhl) {
  std::cout << __PRETTY_FUNCTION__ << std::endl;
  Int tmp = lvl;
  return tmp += rhl;
}

const Int operator- (const Int& lvl, const Int& rhl) {
  std::cout << __PRETTY_FUNCTION__ << std::endl;
  Int tmp = lvl;
  return tmp -= rhl;
}

int main(int argc, char const *argv[]) {
  Int int1{};
  Int int2{2};
  std::cout << "=====Init state=====" << std::endl;
  std::cout << int1.GetValue() << std::endl;
  std::cout << int2.GetValue() << std::endl;
  int1 += int2;
  int1 = int1 + 1; /*int1 = operator+(int1, Int(1));*/
  std::cout << "=====After adding value=====" << std::endl;
  std::cout << int1.GetValue() << std::endl;
  std::cout << int2.GetValue() << std::endl;

  int1 = int1 - int2;
  std::cout << "=====After sub value=====" << std::endl;
  std::cout << int1.GetValue() << std::endl;
  std::cout << int2.GetValue() << std::endl;


  ++int1;

  Int tmp = int1++;
  std::cout << "=====After increment pre and pos value=====" << std::endl;
  std::cout << int1.GetValue() << std::endl;
  std::cout << tmp.GetValue() << std::endl;

  return 0;
}
