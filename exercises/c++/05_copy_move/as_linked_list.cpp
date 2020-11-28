#include <iostream>
#include <memory> // std::unique_ptr
#include <utility> // std::move

enum class Method{push_back, push_front};


template <typename T>
class List{

  struct node{
    std::unique_ptr<node> next;
    T value;
    explicit node(const T& x): value{x} {std::cout << "l-value\n";}          // copy ctor of T
    node(const T& x, node* p): next{p}, value{x} {std::cout << "l-value\n";}

    explicit node(T&& x): value{std::move(x)} {std::cout << "r-value" << std::endl;}
    node(T&& x, node* p): next{p}, value{std::move(x)} {std::cout << "r-value" << std::endl;}

    // node(const node& x): value{x.value}{
    //   if(x.next)
    // 	next.reset(new node{*(x->next)});
    // }
    
    explicit node(const std::unique_ptr<node>& x): value{x->value}{
      if(x->next)
	next.reset(new node{x->next});
    }
  };
  
  std::unique_ptr<node> head;
  node* tail;
  std::size_t _size;

  // forwarding ref
  template <typename O>
  void push_front(O&& x){ // forwarding ref. not r-value
    // auto tmp = new node{x, head.release()};
    // head.reset(tmp);

    // auto tmp = new node{x,head};
    // head.release();
    // head.reset(tmp);
    
    head.reset(new node{std::forward<O>(x),head.release()});
    

  }


  template <typename O>
  void push_back(O&& x){

    auto _node = new node{std::forward<O>(x)};
    auto tmp = head.get();
    if(!tmp){ // if tmp == nullptr
      // our list is empty
      head.reset(_node);
      return;
    }
    
    while(tmp->next)  // while tmp->next.get() != nullptr
      tmp = tmp->next.get();

    tmp->next.reset(_node);
    
  }

  template <typename O>
  void _insert(O&& x, const Method m);

public:
  List() = default;
  ~List() = default;

  // move semantics
  // List(List&& x): head{std::move(x.head)}, _size{x._size}{
  //   x._size=0;
  //   x.head.reset(nullptr);
  // }

    
  // List& operator=(List&& x){
  //   head = std::move(x.head);
  //   _size = std::move(x._size); 

  //   x._size=0;
  //   x.head.reset(nullptr);

  //   return *this; // a = b = c = std::move(x);
  // }

  List(List&&) = default;
  List& operator=(List&&) = default;
  
    
  List(const List& x): _size{x._size} {
    
    if(x.head)
      head.reset(new node{x.head});

    // auto tmp = x.head.get();
    // while(tmp){
    //   insert(tmp->value, Method::push_back);
    // tmp = tmp->next.get();
    // }
  }

  
  List& operator=(const List& x) {
    head.reset();
    auto tmp = x; // copy ctor
    *this = std::move(tmp); // move assignment
    return *this;    
  }
  
  void insert(const T& x, const Method m) { _insert(x, m); }
  void insert(T&& x, const Method m) { _insert(std::move(x), m); }

  // template <typename O>
  // void insert(O&& x, const Method m) { ... }

  
  friend
  std::ostream& operator<<(std::ostream& os, const List& x){
    auto tmp = x.head.get();
    os << "[" << x._size << "] ";
    while(tmp){
      os << tmp->value << " ";
      tmp = tmp->next.get();
    }
    os << std::endl;
    return os;
  }
  
};

// template <typename T>
// void List<T>::insert(const T& x, const Method m){
//   std::cout << "l-value insert\n";
//   switch(m){
//   case Method::push_back:
//     push_back(x);
//     break;
//   case Method::push_front:
//     push_front(x);
//     break;
//   default:
//     std::cerr << "unknown method" << std::endl;
//     break;
    
//   };
//   ++_size;

// }

template <typename T>
template <typename O>
void List<T>::_insert(O&& x, const Method m){
  std::cout << "forwarding insert" << std::endl;
  switch(m){
  case Method::push_back:
    push_back(std::forward<O>(x)); 
    break;
  case Method::push_front:
    push_front(std::forward<O>(x));
    break;
  default:
    std::cerr << "unknown method" << std::endl;
    break;
    
  };
  ++_size;

}


// template <typename T> // class first
// template <typename O> // templates of the method
// void List<T>::push_back(O&& x){
// ...
// }


template <typename T>
void my_swap(T& a, T& b){
  auto tmp = std::move(a);
  a = std::move(b); 
  b = std::move(tmp); 
}


int main(){
  List<int> l{};

  int a = 7;

  l.insert(a,Method::push_back);
  l.insert(1,Method::push_back);
  l.insert(5,Method::push_front);

  List<int> l2{l};

  l.insert(99,Method::push_front);
  l2.insert(877,Method::push_back);
  
  std::cout << l << "\n" << l2 << std::endl;

  // l = List<int>{}; // move assignment 
  // std::cout << l; // bug: undefined behavior, we shouldn't use l


  List <std::pair<int, double>> lp;
  lp.insert({4,3}, Method::push_back);
}

// {4,3} --> std::initializer_list
