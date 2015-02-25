namespace foo
{
  struct A0
    {
    virtual ~A0();
    };
}

namespace foo
{
  using namespace foo;
  struct A1
    {
    virtual ~A1();
    };
}
