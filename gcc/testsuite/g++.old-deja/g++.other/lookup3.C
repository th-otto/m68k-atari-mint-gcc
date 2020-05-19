// { dg-do run  }
// Test to make sure that the use of __typeof__ in WIFEXITED works.

int main ()
{
  int stat_loc = 0;
  (__extension__
   ({
     union
     {
       __typeof__ (stat_loc) ___in;
       int 		__i;
     } __u;
     __u.___in = (stat_loc);
     __u.__i;
   })
   );
}
