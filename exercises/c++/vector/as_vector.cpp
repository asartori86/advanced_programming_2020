#include <vector>
#include <iostream>
#include <memory>
#include <algorithm>
#include <utility>

template<typename T>
class Vector{
  std::unique_ptr<T[]> elem;
  std::size_t _size{};
  std::size_t _capacity{};

  void check_and_increase_capacity(){
    if(_capacity == 0)
      reserve(12); // reserve 8 elements
    else if (_size == _capacity)
      reserve(2*_capacity);
  }

  template <typename O>
  void _push_back(O&& x){
    check_and_increase_capacity();
    elem[_size] = std::forward<O>(x);
    ++_size;
  }

  
public:

  auto size() const { return _size; }
  auto capacity() const { return _capacity; }
  
  Vector() = default;
  ~Vector() = default;

  Vector(std::initializer_list<T> list): // pass by value
    elem{new T[list.size()]},
    _size{list.size()},
    _capacity{list.size()}{

    std::copy(list.begin(), list.end(), elem.get());
    
    // for(std::size_t i=0; i<list.size();++i)
    //   elem[i] = std::move(list[i]);
  }

  void reserve(const std::size_t n){
    if (_capacity < n){
      T* tmp {new T[n]};
    
      for(std::size_t i = 0; i < _size; ++i)
	tmp[i] = std::move(elem[i]);
      elem.reset(tmp);
      _capacity = n;
    }
    
  }
  
  void push_back(const T& x){
    _push_back(x);
  }

  void push_back(T&& x){
    _push_back(std::move(x));
  }

  auto& operator[](const std::size_t i){
    // pre-conditions: good point for assert
    return elem[i];
  }

 const auto& operator[](const std::size_t i) const{
    // pre-conditions: good point for assert
    return elem[i];
  }


  template <typename... Types> // variadic templates; packing
  void emplace_back(Types&&... args){  // unpack
    check_and_increase_capacity();
    elem[_size] = T{std::forward<Types>(args)...}; // T{}
    ++_size;
  }
  
  
  
};

template <typename T>
std::ostream& operator<<(std::ostream& os, const Vector<T>& x){
  os <<"capacity: " << x.capacity() << ", size: " << x.size() << "\n";
  for(auto i =0u; i < x.size(); ++i)
    os << x[i] << " ";
  os << std::endl;
  return os;
  
}

struct Foo{
  Foo(){std::cout << "foo ctor" << std::endl;}
};


int main(){

  Vector<Foo> vf{{},{}};
  // std::vector<Foo> vf{{},{}};
  vf.emplace_back();
  std::cout << vf.capacity() << std::endl;

  return 0;

  Vector<int> x{1,2,3,4};

  std::cout << x;

  x.push_back(3);

  std::cout << x;


  std::vector<std::pair<int,std::string>> vs;

  vs.push_back({4,"hello"}); // push_back takes 1 arg

  vs.emplace_back(4,"hello"); // 2 args
  
  // std::vector<int> v; // default ctor
  // v.reserve(128);
  // std::vector<int> v1(4,2);  // custom ctor 
  // std::vector<int> v2{4,2,4,5,6};  // std::initializer_list<T> // higher priority
 
  // for (const auto x : v1)
  //   std::cout << x << " ";
  // std::cout << std::endl;

  
  // for (const auto x : v2)
  //   std::cout << x << " ";
  // std::cout << std::endl;

}
