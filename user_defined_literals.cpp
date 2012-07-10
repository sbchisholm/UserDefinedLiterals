#include <iostream>

// Working example of C++11 User-Defined Literals from Bjarne Stroustrup's
// Software Development for Infrastructure

// compiles with: g++ 4.7 using -std=c++0x

template<int M, int K, int S> struct Unit{
  enum{m=M, kg=K, s=S};
};

template<typename Unit>
struct Value {
  double val;
  explicit Value(double d): val(d){}
  explicit Value(): val(0){}

public:
  static constexpr int m() {return Unit::m;};
  static constexpr int kg() {return Unit::kg;};
  static constexpr int s() {return Unit::s;};
};

template<typename Unit>
std::ostream& operator<< (std::ostream &out, Value<Unit> &v)
{ out << v.val; return out; }

typedef Value<Unit<1, 0, 0>> Meter;
typedef Value<Unit<0, 0, 1>> Second;
typedef Value<Unit<0, 0, 2>> Second2;

typedef Value<Unit<1, 0, -1>> Speed;
typedef Value<Unit<1, 0, -2>> Acceleration;

Second  operator ""  _s(long double d) { return  Second(d); }
Second2 operator "" _s2(long double d) { return Second2(d); }
Meter   operator ""  _m(long double d) { return   Meter(d); }

template<class Value1, class Value2>
Value<Unit<Value1::m()  - Value2::m(), 
           Value1::kg() - Value2::kg(),
           Value1::s()  - Value2::s()>> operator / (Value1 v1, Value2 v2)
{
  return Value<Unit<Value1::m()  - Value2::m(), 
                    Value1::kg() - Value2::kg(),
                    Value1::s()  - Value2::s()>>(v1.val / v2.val);
}

int main()
{
  Speed sp = 10.0_m / 9.8_s;
  std::cout << sp << std::endl;
}



