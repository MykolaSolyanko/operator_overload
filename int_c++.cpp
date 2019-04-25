class Test {
  public:
    Test operator +(const Test& tst) & {
      return *this;
    }
};

int main(int argc, char const *argv[]) {
    Test t;
    Test t2;
    Test new_tst = Test() + t2;
    return 0;
}
