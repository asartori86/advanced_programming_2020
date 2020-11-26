#include <iostream>

template <typename T>
void print_sentinel(const T* a, const std::size_t l);

int main() {
  int a{8}, b{7};
  int* pi{&a};

  const int* pc{&a}; // const int   *pc
  // *pc = 7; 	// error
  a = 15;  // I can obviously change a
  pc = &b;

  int* const cp{&a};
  a = b;
  *cp = 33;
  // cp = &b;   // error

  const int* const cpc{&a};

  // *cpc = 0;  // error
  // cpc = &n;  // error
  a = 99;

  int aa[4]{};
  print_sentinel<int>(aa, 4);

  return 0;
}

template <typename T>
void print_sentinel(const T* a, const std::size_t l) {
  const T* const end{a + l}; // the sentinel
  for (; a != end; ++a)
    std::cout << *a << std::endl;
}
