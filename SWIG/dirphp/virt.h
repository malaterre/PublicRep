struct base
{
  virtual void foo();
};

struct concrete : public base
{
  virtual void foo();
};

base * create_concrete();
