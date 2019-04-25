# Перегрузука опрераторов
Перегрузка она имеет похожий смысл с перегрузкой функций. Т.е. иногда хочеться добавить некий смысл операции, или упростить ту или другую опрацию, спрятав ее за абстракцией. Или например придать осмысленый характер оперции который характерен для объкта. Начнем с того что со встроеными типа можно выполнять ряд операций, например сложение, вычитаение, и т.д. Но при создании пользовательского типа(это класс и структура), хотелось бы добавить также возможность выполнять над ними некие встроеные операции. Например если у нас есть две строки, то хотелось бы добавить возможность конкатенации строк. Или например, если есть у нас класс мартица, то хотелось бы применяя встренные операции придать этому классу матиматическую абстрацию, т.е. складывать матрицы, вычитать и т.д. Но по умолчанию как было сказано выше эта возможность добавлена только для вастроеных типов, а пользовательские типы лишены этой возможности. Это и логично, что такое встроеный тип, это объект который хранит только одно значение(и встроеные типы есть частью CPU). Тогда как пользовательский тип это составной тип с набора полей приметивных типов, и компилятор очевидно не знает как их складывать, да и не понимает есть ли в этом логика. То для этого в С++ и применяеться логика перегрузки операторов. Несколько замечаний по перегрузке.
1. Перегрузка не может быть применена для встроеных типов, она только применена для пользовательских типов.
2. Перегрузка должна быть семантически необходимой, например конкатенация строки это норм, а вот вычитание строки это полный бред. Поэтому есть смысл для класса строки использовать перегрузку оператора +, но нет смысла это делать для оператора -
3. Перегруженный оператор должен быть по смыслу, т.е. делать то что предпологает пвстроенный оператор. Например если вы перегрузили оператор плюс для матрицы, то он должен складывать матрицы а не умножать их. Т.е. не должен нести побочного эфекта.
Перегрузка оператора это та же функция, только эта функция может иметь сокращенную форму которая подставляеться компилятором. Делая для нас привычную форму выполнения встроенной операции.
Мы уже использовали с вами перегруженный оператор, компилятор когда мы создаем класс, по умолчанию добавляет в наш класс перегрузку оператора `=`. Это делаеться для возможности присваивать объекты между собой, это оператор по умолчанию просто бинарно копирует данные(поверхносное копирование). Пример
```cpp
#include <iostream>

class Test {
 public:
   Test& operator =(const Test&) {
     std::cout << __PRETTY_FUNCTION__ << std::endl;
     return *this;
   }
};

int main(int argc, char const *argv[]) {
  Test t1;
  Test t2;

  t1 = t2;
  t1.operator=(t2);
  return 0;
}

```

Т.е. с примера видно что оператор `=` для класса это просто функция.
Т.е. перегрузка операции всегда начинаеться с ключевого слова `operator` за которым следует какой оператор мы хотим перегружать. При чем между `operator` и самим оператором может стоять столь угодно пробелов. Компилятор таком образом позволяет нам писать сокращенную форму операции вместо вызова функции.
Перегрузка бывает двох типов для унарных операторов и для бинарных. Таже некоторые перегрузки операторов должны быть определенны как методы класса, тогда как другие могут быть определены как методы или как независимые функции.
Ок, давайте напишим класс Int(подобие класса в Java).
```cpp
#include <iostream>

class Int {
 public:
  Int(int value = 0) : value(value) {
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
  int1 = int1 + 1;
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


```

И вывод на экран
```
=====Init state=====
0
2
Int& Int::operator+=(const Int&)
const Int operator+(const Int&, const Int&)
Int& Int::operator+=(const Int&)
=====After adding value=====
3
2
const Int operator-(const Int&, const Int&)
Int& Int::operator-=(const Int&)
=====After sub value=====
1
2
Int& Int::operator++()
const Int Int::operator++(int)
=====After increment pre value=====
3
2
```

Как видим мы написали класс Int в котором добавили перегрузку следующих операторов `+, -, +=, -=, ++, --`. С примера видно что перегрузка оператора `+` реализована посредством уже готового перегруженого составного оператора `+=`. Т.е. это частая такая техника где один из операторов реализован посредством другого реализованого оператора, для избежания повторения кода. Но это только тогда когда например обычный оператор имеет аналогичный составной  оператор. Как в примере с оператором `+` и `-`, реализуються посредством составных операторв. И чаще такие операторы, не составные, делают как обычные функции, а не методами класса.
Но есть как я говорил ограничения на то что некоторые операторы должны быть объязательно определены как методы класса, а тогда как другие могут быть как методы класса так и обычные функции. Но есть еще категория операторов которые перегружать нельзя.

1. `= () [] -> ->*`, должны быть объязательно быть объявленны как методы класса, для того чтобы гарантировать что их левый операнды lvalue
2. `.	.*	::	?: sizeof` вы не можете перегрузить эти операторы
3. Все остальные делают как методы класса так и не зависимые функции. Но чаще есть некие тоже правилва(рекомендации)
  3.1. Все унарные операторы рекомендуеться писать как методы класса (++ --)
  3.2. `+= -= /= *= ^= &= |= %= >>= <<=` Все составные операторы также рекомендуеться писать как методы класса
  3.3. Остальные бинарные операторы, рекомендуеться писать как обычные функции.


Ок возращаясь к нашему примеру есть еще интересный момент, а именно
```cpp
  int1 = int1 + 1;
```

Т.е. мы к нашему классу прибавляем целочисленный литерал, вопрос как это возможно. Это возможно что у нас определен конструктор с одним параметром `int`, и тем самым мы неявно конвертируем `int` в наш класс `Int`. Т.е. на самом деле вызов будет таким
```cpp
/*int1 = operator+(int1, Int(1));*/
```

То если мы объявим наш пользовательский конструктор с ключевым словом `explicit`, то мы получим ошибку компиляции
```cpp
no known conversion for argument 2 from ‘int’ to ‘const Int&’
```

Ок, есть вопрос так а в чем разница в том чтобы объявить перегрузку оператора как метод класса, или как незвисимая функция. Разница в том что при объявлении как метода мы не сможем написать вот так
```cpp
int1 = 11 + int1;
```
Проблема в том что левым операндом должен быть объект класса, а у нас это целочисленный литерал. Ну если выполнить преобразование типов, т.е. выполнить так `Int(11)`, то все бы работало. Но если мы будем объявлять это как внешняя функция, то у нас произойдет неявное преобразование следующего вида
```cpp
operator+(Int(11), int1);
```
Ок как видите таким способом мы еще решили проблему комутативности оператора `+`. Т.е. не важно где ставить операнд слева или справа, результат тот же.

Но в С++ можно не только перегружать операторы, можно также перегружать операторы преобразования типа. Т.е. напримере если мы хотим чтобы наш класс Int преобразовывался в целочисленное значение, вместо написания разных фукций как у нас впримере `int GetValue()`, а возможность использовать наш объект где ожидаеться целочисленное значение, например для потока вывода, или присвоить целочисленной переменной. То для этого как рах и применяеться оператор преобразования типа. Давайте добавим в наш класс оператор преобразования нашего объекта к `int`.

```
operator int() const {
  return value;
}
```

Как видим с описания, перегрузка типа начинаеться с ключевого слова operator  и типа к которому мы хотим преобразовать наш класс, я думаю понятно почему нет возращаемого значения. Оператор преобразования типа чаще пишут как const.
Но если мы запустим наш код то получим ошибку следующего характера
```
Int.cpp:74:15: error: ambiguous overload for ‘operator+’ (operand types are ‘Int’ and ‘int’)
   int1 = int1 + 1; /*int1 = operator+(int1, Int(1));*/
          ~~~~~^~~
Int.cpp:74:15: note: candidate: operator+(int, int) <built-in>
Int.cpp:55:11: note: candidate: const Int operator+(const Int&, const Int&)
 const Int operator+ (const Int& lvl, const Int& rhl) {
           ^~~~~~~~
Int.cpp:75:13: error: ambiguous overload for ‘operator+’ (operand types are ‘int’ and ‘Int’)
   int1 = 11 + int1; /*int1 = operator+(11, int1);*/
          ~~~^~~~~~
Int.cpp:75:13: note: candidate: operator+(int, int) <built-in>
Int.cpp:55:11: note: candidate: const Int operator+(const Int&, const Int&)
 const Int operator+ (const Int& lvl, const Int& rhl) {
``` 

А проблема в этих строчках
```
  int1 = int1 + 1;
  int1 = 11 + int1;
```
Т.е. как видно с описания компилятор незнает преобразовать наш объект `int1` к целому числу(т.к. у нас есть теперь оператор преобразования типа) и применить для этого встроенный оператор сложения для целых чисел, или же преобразовать целое число к объекту класса, и вызвать перегруженный оператор `+`. Т.е. не однозначность. Это есть проблема неявного преобразования.
Но если мы добавим конструктор как `explicit`, это тоже не решит проблемы. Вывод с этого что надо быть осторожным с преобразованием, т.е. надо подумать что есть приоритетней, чтобы избежать неоднозначностей. Но решение ест, но оно не очень хорошо выглядит. Заключаеться в том чтобы добавить перегрузку оператора `=`.
```cpp
  Int& operator= (int value) {
    this->value = value;
    return *this;
  }

```

И выражение `11 + int1;` будет преобразовано в целое число и вызовется перегруженный оператор `=` с целочисленным аргументом.

Давайте еще расмотрим одну малоизвестной фиче, это **reference-qualified member functions**,  это возможность квалифицировать методы ссылкой. Т.е. простым словом мы указываем в каком контексте вызывать ту или иную функцию. Предположим у нас есть класс
```cpp
class Test {
  public:
    Test operator +(const Test& tst) {
      return *this;
    }
};

int main(int argc, char const *argv[]) {
    Test t;
    Test t2;
    Test new_tst = Test() + t2;
    return 0;
}

```

В котором мы можем складывать два объекта Test, как видим мы может вызывать оператор + для временного объекта, но например можно запретить вызов такого оператора для rvalue, а возможность вызова только для lvalue. Для этого и применяються ссылочные квалификаторы.
```cpp
class Test {
  public:
    Test operator +(const Test& tst) & {
      return *this;
    }
};

```

Как видим мы добавляем к сигнатуре функции параметр &, который говорит что этот метод будет вызываться только для lvalue.
Ссылочные квалификаторы могут применяться не только для операторов но и для функций.