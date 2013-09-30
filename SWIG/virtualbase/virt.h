struct base
{
  virtual void foo() = 0;
  static base * create_concrete();
};

struct concrete : public base
{
  void foo();
};


