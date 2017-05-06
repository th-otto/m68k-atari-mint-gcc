gcc-4.6.4
=========

Patch to gcc for supporting "fastcall" on m68k target.

By default gcc pass all arguments on the stack for the m68k target, 
this is not always optimal when memory access is slow. This default
abi is from now an named the `cdecl` abi.

A new abi named `fastcall` has been added, where registers d0-d2, 
a0-a1 and fp0-fp2 are used to pass registers to functions when possible.
A third option is to use the `regparm` option to specify the number
of registers of each class to use.

At a minimum d0-d1, a0-a1, fp0-fp1 are clobbered by function calls.
Any further register potentially used for the arguments for the
functions abi is also clobbered, that is that d2 is also 
concidered clobbered for `fastcall`.

32 bit float are passed in registers when 68881 is not enabled, when
enabled fp0-fp2 are used for all floating point types.

All build-in libgcc functions use the `fastcall` abi, this means that
any library being used must also be rebuilt. This is most useful on
plain 68000 where short helper functions for 32bit int are frequently
called.

Only named arguments for variadic functions can use registers, all
unnamed arguments are always passed on the stack.

Examples
--------

    // a passed in d0
    // b passed in d1
    __attribute__((fastcall)) int foo(int a, int b);
    
    // a passed in d0
    // b passed in a0
    // c passed in d1
    __attribute__((fastcall)) int foo(float a, int *b, char c);

    // s passed in a0
    // rest on stack
    __attribute__((fastcall)) void printf(char *s, ...);

