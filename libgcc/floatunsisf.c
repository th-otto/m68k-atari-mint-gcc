#include "elf-alias.h"

/* Public domain.  */
typedef int SItype __attribute__ ((mode (SI)));
typedef unsigned int USItype __attribute__ ((mode (SI)));
typedef float SFtype __attribute__ ((mode (SF)));

SFtype
__floatunsisf (USItype u)
{
  SItype s = (SItype) u;
  if (s < 0)
    {
      /* As in expand_float, compute (u & 1) | (u >> 1) to ensure
	 correct rounding if a nonzero bit is shifted out.  */
      return (SFtype) 2.0 * (SFtype) (SItype) ((u & 1) | (u >> 1));
    }
  else
    return (SFtype) s;
}
ELF_ALIAS(__floatunsisf)
