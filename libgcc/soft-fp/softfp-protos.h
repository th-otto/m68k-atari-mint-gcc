#ifdef __FLT16_MANT_DIG__
#define LIBGCC_HAS_HF_MODE
#endif
#ifdef __FLT_MANT_DIG__
#define LIBGCC_HAS_SF_MODE
#endif
#ifdef __DBL_MANT_DIG__
#define LIBGCC_HAS_DF_MODE
#endif
#if defined(__LDBL_MANT_DIG__) && __DBL_MANT_DIG__ != __LDBL_MANT_DIG__
#define LIBGCC_HAS_XF_MODE
#endif
#if defined(__FLT128_MANT_DIG__) && (!defined(__LDBL_MANT_DIG__) || __FLT128_MANT_DIG__ != __LDBL_MANT_DIG__)
#define LIBGCC_HAS_TF_MODE
#endif

/*
 * half
 */
#ifdef LIBGCC_HAS_HF_MODE
CMPtype __unordhf2(_Float16 a, _Float16 b);
_Float16 __floatsihf (SItype a1);
_Float16 __floatdihf (DItype a1);
_Float16 __floatunsihf (USItype a1);
_Float16 __floatundihf (UDItype a1);
SItype __fixhfsi (_Float16 a1);
DItype __fixhfdi (_Float16 a1);
USItype __fixunshfsi (_Float16 a1);
UDItype __fixunshfdi (_Float16 a1);
_Float16 __addhf3 (_Float16 x1, _Float16 x2);
_Float16 __subhf3 (_Float16 x1, _Float16 x2);
_Float16 __mulhf3 (_Float16 x1, _Float16 x2);
_Float16 __divhf3 (_Float16 x1, _Float16 x2);
_Float16 __neghf2 (_Float16 x1);
CMPtype __cmphf2 (_Float16 x1, _Float16 x2);
CMPtype __eqhf2 (_Float16 x1, _Float16 x2);
CMPtype __nehf2 (_Float16 x1, _Float16 x2);
CMPtype __lthf2 (_Float16 x1, _Float16 x2);
CMPtype __lehf2 (_Float16 x1, _Float16 x2);
CMPtype __gthf2 (_Float16 x1, _Float16 x2);
CMPtype __gehf2 (_Float16 x1, _Float16 x2);

#ifdef LIBGCC_HAS_SF_MODE
float __extendhfsf2 (_Float16 a1);
#endif
#ifdef LIBGCC_HAS_DF_MODE
double __extendhfdf2 (_Float16 a1);
#endif
#ifdef LIBGCC_HAS_XF_MODE
long double __extendhfxf2 (_Float16 a1);
#endif
#ifdef LIBGCC_HAS_TF_MODE
_Float128  __extendhftf2 (_Float16 a1);
#endif
#endif

/*
 * single
 */
#ifdef LIBGCC_HAS_SF_MODE
CMPtype __unordsf2(float a, float b);
float __floatsisf (SItype a1);
float __floatdisf (DItype a1);
float __floatunsisf (USItype a1);
float __floatundisf (UDItype a1);
SItype __fixsfsi (float a1);
DItype __fixsfdi (float a1);
USItype __fixunssfsi (float a1);
UDItype __fixunssfdi (float a1);
float __addsf3 (float x1, float x2);
float __subsf3 (float x1, float x2);
float __mulsf3 (float x1, float x2);
float __divsf3 (float x1, float x2);
float __negsf2 (float x1);
CMPtype __cmpsf2 (float x1, float x2);
CMPtype __eqsf2 (float x1, float x2);
CMPtype __nesf2 (float x1, float x2);
CMPtype __ltsf2 (float x1, float x2);
CMPtype __lesf2 (float x1, float x2);
CMPtype __gtsf2 (float x1, float x2);
CMPtype __gesf2 (float x1, float x2);

#ifdef LIBGCC_HAS_HF_MODE
_Float16 __truncsfhf2 (float a1);
#endif
#ifdef LIBGCC_HAS_DF_MODE
double __extendsfdf2 (float a1);
#endif
#ifdef LIBGCC_HAS_XF_MODE
long double __extendsfxf2 (float a1);
#endif
#ifdef LIBGCC_HAS_TF_MODE
_Float128 __extendsftf2 (float a1);
#endif
#endif

/*
 * double
 */
#ifdef LIBGCC_HAS_DF_MODE
CMPtype __unorddf2(double a, double b);
double __floatsidf (SItype a1);
double __floatdidf (DItype a1);
double __floatunsidf (USItype a1);
double __floatundidf (UDItype a1);
SItype __fixdfsi (double a1);
DItype __fixdfdi (double a1);
USItype __fixunsdfsi (double a1);
UDItype __fixunsdfdi (double a1);
double __adddf3 (double x1, double x2);
double __subdf3 (double x1, double x2);
double __muldf3 (double x1, double x2);
double __divdf3 (double x1, double x2);
double __negdf2 (double x1);
CMPtype __cmpdf2 (double x1, double x2);
CMPtype __eqdf2 (double x1, double x2);
CMPtype __nedf2 (double x1, double x2);
CMPtype __ltdf2 (double x1, double x2);
CMPtype __ledf2 (double x1, double x2);
CMPtype __gtdf2 (double x1, double x2);
CMPtype __gedf2 (double x1, double x2);

#ifdef LIBGCC_HAS_HF_MODE
_Float16 __truncdfhf2 (double a1);
#endif
#ifdef LIBGCC_HAS_SF_MODE
float __truncdfsf2 (double a1);
#endif
#ifdef LIBGCC_HAS_XF_MODE
long double __extenddfxf2(double a1);
#endif
#ifdef LIBGCC_HAS_TF_MODE
_Float128 __extenddftf2(double a1);
#endif
#endif

/*
 * extended
 */
#ifdef LIBGCC_HAS_XF_MODE
CMPtype __unordxf2(long double a, long double b);
long double __floatsixf (SItype a1);
long double __floatdixf (DItype a1);
long double __floatunsixf (USItype a1);
long double __floatundixf (UDItype a1);
SItype __fixxfsi (long double a1);
DItype __fixxfdi (long double a1);
USItype __fixunsxfsi (long double a1);
UDItype __fixunsxfdi (long double a1);
long double __addxf3 (long double x1, long double x2);
long double __subxf3 (long double x1, long double x2);
long double __mulxf3 (long double x1, long double x2);
long double __divxf3 (long double x1, long double x2);
long double __negxf2 (long double x1);
CMPtype __cmpxf2 (long double x1, long double x2);
CMPtype __eqxf2 (long double x1, long double x2);
CMPtype __nexf2 (long double x1, long double x2);
CMPtype __ltxf2 (long double x1, long double x2);
CMPtype __lexf2 (long double x1, long double x2);
CMPtype __gtxf2 (long double x1, long double x2);
CMPtype __gexf2 (long double x1, long double x2);

#ifdef LIBGCC_HAS_HF_MODE
_Float16 __truncxfhf2 (long double a1);
#endif
#ifdef LIBGCC_HAS_SF_MODE
float __truncxfsf2 (long double a1);
#endif
#ifdef LIBGCC_HAS_DF_MODE
double __truncxfdf2 (long double a1);
#endif
#ifdef LIBGCC_HAS_TF_MODE
_Float128 __extendxftf2 (long double a1);
#endif
#endif

/*
 * quad
 */
#ifdef LIBGCC_HAS_TF_MODE
CMPtype __unordtf2(_Float128 a, _Float128 b);
_Float128 __floatsitf (SItype a1);
_Float128 __floatditf (DItype a1);
_Float128 __floatunsitf (USItype a1);
_Float128 __floatunditf (UDItype a1);
SItype __fixtfsi (_Float128 a1);
DItype __fixtfdi (_Float128 a1);
USItype __fixunstfsi (_Float128 a1);
UDItype __fixunstfdi (_Float128 a1);
_Float128 __addtf3 (_Float128 x1, _Float128 x2);
_Float128 __subtf3 (_Float128 x1, _Float128 x2);
_Float128 __multf3 (_Float128 x1, _Float128 x2);
_Float128 __divtf3 (_Float128 x1, _Float128 x2);
_Float128 __negtf2 (_Float128 x1);
CMPtype __cmptf2 (_Float128 x1, _Float128 x2);
CMPtype __eqtf2 (_Float128 x1, _Float128 x2);
CMPtype __netf2 (_Float128 x1, _Float128 x2);
CMPtype __lttf2 (_Float128 x1, _Float128 x2);
CMPtype __letf2 (_Float128 x1, _Float128 x2);
CMPtype __gttf2 (_Float128 x1, _Float128 x2);
CMPtype __getf2 (_Float128 x1, _Float128 x2);

#ifdef LIBGCC_HAS_HF_MODE
_Float16 __trunctfhf2 (_Float128 a1);
#endif
#ifdef LIBGCC_HAS_SF_MODE
float __trunctfsf2 (_Float128 a1);
#endif
#ifdef LIBGCC_HAS_DF_MODE
double __trunctfdf2 (_Float128 a1);
#endif
#ifdef LIBGCC_HAS_XF_MODE
long double __trunctfxf2 (_Float128 a1);
#endif
#endif
