// http://www.swig.org/Doc2.0/Php.html#Php_nn2_6_4
class Ko {
public:
  static void threats();
};

// does not work:
struct base
{
  virtual void foo() = 0;
  static base * create_concrete(bool b = true);
};

struct concrete : public base
{
  void foo();
};

base * create_concrete_for_swig();
