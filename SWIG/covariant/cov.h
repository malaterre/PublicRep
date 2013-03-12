struct A1
{
  virtual ~A1() {}
};

struct A2 : public A1
{
};

struct F1
{
  virtual A1 const & foo();
};

struct F2 : public F1
{
  virtual A2 const & foo();
};
