// { dg-options "-std=gnu++20" }
// { dg-do run { target c++20 } }
// { dg-timeout-factor 2 }

#include <chrono>
#include <format>
#include <testsuite_hooks.h>

void
test01()
{
  using std::format;
  using namespace std::chrono;

  auto st = sys_days{2000y/January/1};
  auto tt = clock_cast<tai_clock>(st);

  auto s = format("{0:%F %T %Z} == {1:%F %T %Z}", st, tt);
  VERIFY( s == "2000-01-01 00:00:00 UTC == 2000-01-01 00:00:32 TAI" );
}

int main()
{
  test01();
}
