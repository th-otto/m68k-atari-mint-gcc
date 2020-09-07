/* C code produced by gperf version 3.1 */
/* Command-line: gperf -L C -F ', 0, 0' -p -j1 -g -o -t -N is_reserved_word -k'1,4,7,$' ../../../gcc/cp/gxx.gperf  */

#if !((' ' == 32) && ('!' == 33) && ('"' == 34) && ('#' == 35) \
      && ('%' == 37) && ('&' == 38) && ('\'' == 39) && ('(' == 40) \
      && (')' == 41) && ('*' == 42) && ('+' == 43) && (',' == 44) \
      && ('-' == 45) && ('.' == 46) && ('/' == 47) && ('0' == 48) \
      && ('1' == 49) && ('2' == 50) && ('3' == 51) && ('4' == 52) \
      && ('5' == 53) && ('6' == 54) && ('7' == 55) && ('8' == 56) \
      && ('9' == 57) && (':' == 58) && (';' == 59) && ('<' == 60) \
      && ('=' == 61) && ('>' == 62) && ('?' == 63) && ('A' == 65) \
      && ('B' == 66) && ('C' == 67) && ('D' == 68) && ('E' == 69) \
      && ('F' == 70) && ('G' == 71) && ('H' == 72) && ('I' == 73) \
      && ('J' == 74) && ('K' == 75) && ('L' == 76) && ('M' == 77) \
      && ('N' == 78) && ('O' == 79) && ('P' == 80) && ('Q' == 81) \
      && ('R' == 82) && ('S' == 83) && ('T' == 84) && ('U' == 85) \
      && ('V' == 86) && ('W' == 87) && ('X' == 88) && ('Y' == 89) \
      && ('Z' == 90) && ('[' == 91) && ('\\' == 92) && (']' == 93) \
      && ('^' == 94) && ('_' == 95) && ('a' == 97) && ('b' == 98) \
      && ('c' == 99) && ('d' == 100) && ('e' == 101) && ('f' == 102) \
      && ('g' == 103) && ('h' == 104) && ('i' == 105) && ('j' == 106) \
      && ('k' == 107) && ('l' == 108) && ('m' == 109) && ('n' == 110) \
      && ('o' == 111) && ('p' == 112) && ('q' == 113) && ('r' == 114) \
      && ('s' == 115) && ('t' == 116) && ('u' == 117) && ('v' == 118) \
      && ('w' == 119) && ('x' == 120) && ('y' == 121) && ('z' == 122) \
      && ('{' == 123) && ('|' == 124) && ('}' == 125) && ('~' == 126))
/* The character set is not based on ISO-646.  */
error "gperf generated tables don't work with this execution character set. Please report a bug to <bug-gperf@gnu.org>."
#endif

#line 1 "../../../gcc/cp/gxx.gperf"

/* Command-line: gperf -L KR-C -F ', 0, 0' -p -j1 -g -o -t -N is_reserved_word -k1,4,$,7 gplus.gperf  */
#line 4 "../../../gcc/cp/gxx.gperf"
struct resword { const char *name; short token; enum rid rid;};

#define TOTAL_KEYWORDS 106
#define MIN_WORD_LENGTH 2
#define MAX_WORD_LENGTH 16
#define MIN_HASH_VALUE 4
#define MAX_HASH_VALUE 163
/* maximum key range = 160, duplicates = 0 */

#ifdef __GNUC__
__inline
#else
#ifdef __cplusplus
inline
#endif
#endif
static unsigned int
hash (str, len)
     register const char *str;
     register size_t len;
{
  static unsigned char asso_values[] =
    {
      164, 164, 164, 164, 164, 164, 164, 164, 164, 164,
      164, 164, 164, 164, 164, 164, 164, 164, 164, 164,
      164, 164, 164, 164, 164, 164, 164, 164, 164, 164,
      164, 164, 164, 164, 164, 164, 164, 164, 164, 164,
      164, 164, 164, 164, 164, 164, 164, 164, 164, 164,
      164, 164, 164, 164, 164, 164, 164, 164, 164, 164,
      164, 164, 164, 164, 164, 164, 164, 164, 164, 164,
      164, 164, 164, 164, 164, 164, 164, 164, 164, 164,
      164, 164, 164, 164, 164, 164, 164, 164, 164, 164,
      164, 164, 164, 164, 164,   0, 164,  44,  58,  15,
       55,   0,  24,  23,  25,   2, 164,   4,  26,  75,
       36,  11,  40,  74,  14,  23,   1,  45,  45,  90,
       50,  50, 164, 164, 164, 164, 164, 164, 164, 164,
      164, 164, 164, 164, 164, 164, 164, 164, 164, 164,
      164, 164, 164, 164, 164, 164, 164, 164, 164, 164,
      164, 164, 164, 164, 164, 164, 164, 164, 164, 164,
      164, 164, 164, 164, 164, 164, 164, 164, 164, 164,
      164, 164, 164, 164, 164, 164, 164, 164, 164, 164,
      164, 164, 164, 164, 164, 164, 164, 164, 164, 164,
      164, 164, 164, 164, 164, 164, 164, 164, 164, 164,
      164, 164, 164, 164, 164, 164, 164, 164, 164, 164,
      164, 164, 164, 164, 164, 164, 164, 164, 164, 164,
      164, 164, 164, 164, 164, 164, 164, 164, 164, 164,
      164, 164, 164, 164, 164, 164, 164, 164, 164, 164,
      164, 164, 164, 164, 164, 164, 164, 164, 164, 164,
      164, 164, 164, 164, 164, 164
    };
  register unsigned int hval = len;

  switch (hval)
    {
      default:
        hval += asso_values[(unsigned char)str[6]];
      /*FALLTHROUGH*/
      case 6:
      case 5:
      case 4:
        hval += asso_values[(unsigned char)str[3]];
      /*FALLTHROUGH*/
      case 3:
      case 2:
      case 1:
        hval += asso_values[(unsigned char)str[0]];
        break;
    }
  return hval + asso_values[(unsigned char)str[len - 1]];
}

struct resword *
is_reserved_word (str, len)
     register const char *str;
     register size_t len;
{
  static struct resword wordlist[] =
    {
      {"", 0, 0}, {"", 0, 0}, {"", 0, 0}, {"", 0, 0},
#line 57 "../../../gcc/cp/gxx.gperf"
      {"else", ELSE, NORID,},
#line 97 "../../../gcc/cp/gxx.gperf"
      {"true", CXX_TRUE, NORID,},
#line 69 "../../../gcc/cp/gxx.gperf"
      {"int", TYPESPEC, RID_INT,},
      {"", 0, 0},
#line 24 "../../../gcc/cp/gxx.gperf"
      {"__real__", REALPART, NORID},
      {"", 0, 0},
#line 68 "../../../gcc/cp/gxx.gperf"
      {"inline", SCSPEC, RID_INLINE,},
      {"", 0, 0},
#line 29 "../../../gcc/cp/gxx.gperf"
      {"__signed__", TYPESPEC, RID_SIGNED},
      {"", 0, 0},
#line 10 "../../../gcc/cp/gxx.gperf"
      {"__attribute", ATTRIBUTE, NORID},
      {"", 0, 0},
#line 11 "../../../gcc/cp/gxx.gperf"
      {"__attribute__", ATTRIBUTE, NORID},
      {"", 0, 0},
#line 60 "../../../gcc/cp/gxx.gperf"
      {"export", SCSPEC, RID_EXPORT,},
#line 44 "../../../gcc/cp/gxx.gperf"
      {"case", CASE, NORID,},
#line 14 "../../../gcc/cp/gxx.gperf"
      {"__const", CV_QUALIFIER, RID_CONST},
#line 15 "../../../gcc/cp/gxx.gperf"
      {"__const__", CV_QUALIFIER, RID_CONST},
#line 33 "../../../gcc/cp/gxx.gperf"
      {"__volatile", CV_QUALIFIER, RID_VOLATILE},
      {"", 0, 0},
#line 34 "../../../gcc/cp/gxx.gperf"
      {"__volatile__", CV_QUALIFIER, RID_VOLATILE},
#line 25 "../../../gcc/cp/gxx.gperf"
      {"__restrict", CV_QUALIFIER, RID_RESTRICT},
#line 26 "../../../gcc/cp/gxx.gperf"
      {"__restrict__", CV_QUALIFIER, RID_RESTRICT},
#line 77 "../../../gcc/cp/gxx.gperf"
      {"or", OROR, NORID,},
#line 67 "../../../gcc/cp/gxx.gperf"
      {"if", IF, NORID,},
      {"", 0, 0},
#line 9 "../../../gcc/cp/gxx.gperf"
      {"__asm__", ASM_KEYWORD, NORID},
#line 102 "../../../gcc/cp/gxx.gperf"
      {"typeof", TYPEOF, NORID,},
#line 23 "../../../gcc/cp/gxx.gperf"
      {"__real", REALPART, NORID},
      {"", 0, 0}, {"", 0, 0},
#line 30 "../../../gcc/cp/gxx.gperf"
      {"__sigof__", SIGOF, NORID		/* Extension */,},
#line 91 "../../../gcc/cp/gxx.gperf"
      {"static_cast", STATIC_CAST, NORID,},
#line 59 "../../../gcc/cp/gxx.gperf"
      {"explicit", SCSPEC, RID_EXPLICIT,},
#line 82 "../../../gcc/cp/gxx.gperf"
      {"register", SCSPEC, RID_REGISTER,},
#line 35 "../../../gcc/cp/gxx.gperf"
      {"__wchar_t", TYPESPEC, RID_WCHAR  /* Unique to ANSI C++ */,},
#line 74 "../../../gcc/cp/gxx.gperf"
      {"not", '!', NORID,},
#line 64 "../../../gcc/cp/gxx.gperf"
      {"for", FOR, NORID,},
#line 61 "../../../gcc/cp/gxx.gperf"
      {"extern", SCSPEC, RID_EXTERN,},
#line 85 "../../../gcc/cp/gxx.gperf"
      {"short", TYPESPEC, RID_SHORT,},
#line 49 "../../../gcc/cp/gxx.gperf"
      {"const", CV_QUALIFIER, RID_CONST,},
#line 90 "../../../gcc/cp/gxx.gperf"
      {"static", SCSPEC, RID_STATIC,},
      {"", 0, 0},
#line 46 "../../../gcc/cp/gxx.gperf"
      {"char", TYPESPEC, RID_CHAR,},
#line 13 "../../../gcc/cp/gxx.gperf"
      {"__complex__", TYPESPEC, RID_COMPLEX},
#line 66 "../../../gcc/cp/gxx.gperf"
      {"goto", GOTO, NORID,},
#line 94 "../../../gcc/cp/gxx.gperf"
      {"template", TEMPLATE, RID_TEMPLATE,},
#line 95 "../../../gcc/cp/gxx.gperf"
      {"this", THIS, NORID,},
#line 62 "../../../gcc/cp/gxx.gperf"
      {"false", CXX_FALSE, NORID,},
#line 89 "../../../gcc/cp/gxx.gperf"
      {"sizeof", SIZEOF, NORID,},
#line 98 "../../../gcc/cp/gxx.gperf"
      {"try", TRY, NORID,},
#line 93 "../../../gcc/cp/gxx.gperf"
      {"switch", SWITCH, NORID,},
#line 99 "../../../gcc/cp/gxx.gperf"
      {"typedef", SCSPEC, RID_TYPEDEF,},
      {"", 0, 0},
#line 76 "../../../gcc/cp/gxx.gperf"
      {"operator", OPERATOR, NORID,},
#line 27 "../../../gcc/cp/gxx.gperf"
      {"__signature__", AGGR, RID_SIGNATURE	/* Extension */,},
#line 45 "../../../gcc/cp/gxx.gperf"
      {"catch", CATCH, NORID,},
#line 53 "../../../gcc/cp/gxx.gperf"
      {"delete", DELETE, NORID,},
#line 101 "../../../gcc/cp/gxx.gperf"
      {"typeid", TYPEID, NORID,},
#line 88 "../../../gcc/cp/gxx.gperf"
      {"sigof", SIGOF, NORID		/* Extension */,},
#line 50 "../../../gcc/cp/gxx.gperf"
      {"const_cast", CONST_CAST, NORID,},
#line 28 "../../../gcc/cp/gxx.gperf"
      {"__signed", TYPESPEC, RID_SIGNED},
#line 47 "../../../gcc/cp/gxx.gperf"
      {"class", AGGR, RID_CLASS,},
#line 110 "../../../gcc/cp/gxx.gperf"
      {"xor", '^', NORID,},
#line 54 "../../../gcc/cp/gxx.gperf"
      {"do", DO, NORID,},
#line 51 "../../../gcc/cp/gxx.gperf"
      {"continue", CONTINUE, NORID,},
#line 39 "../../../gcc/cp/gxx.gperf"
      {"auto", SCSPEC, RID_AUTO,},
#line 32 "../../../gcc/cp/gxx.gperf"
      {"__typeof__", TYPEOF, NORID},
      {"", 0, 0},
#line 7 "../../../gcc/cp/gxx.gperf"
      {"__alignof__", ALIGNOF, NORID},
#line 63 "../../../gcc/cp/gxx.gperf"
      {"float", TYPESPEC, RID_FLOAT,},
#line 92 "../../../gcc/cp/gxx.gperf"
      {"struct", AGGR, RID_RECORD,},
#line 70 "../../../gcc/cp/gxx.gperf"
      {"long", TYPESPEC, RID_LONG,},
#line 22 "../../../gcc/cp/gxx.gperf"
      {"__null", CONSTANT, RID_NULL},
      {"", 0, 0},
#line 21 "../../../gcc/cp/gxx.gperf"
      {"__label__", LABEL, NORID},
#line 19 "../../../gcc/cp/gxx.gperf"
      {"__inline", SCSPEC, RID_INLINE},
#line 83 "../../../gcc/cp/gxx.gperf"
      {"reinterpret_cast", REINTERPRET_CAST, NORID,},
#line 20 "../../../gcc/cp/gxx.gperf"
      {"__inline__", SCSPEC, RID_INLINE},
#line 18 "../../../gcc/cp/gxx.gperf"
      {"__imag__", IMAGPART, NORID},
#line 100 "../../../gcc/cp/gxx.gperf"
      {"typename", TYPENAME_KEYWORD, NORID,},
#line 65 "../../../gcc/cp/gxx.gperf"
      {"friend", SCSPEC, RID_FRIEND,},
#line 48 "../../../gcc/cp/gxx.gperf"
      {"compl", '~', NORID,},
#line 81 "../../../gcc/cp/gxx.gperf"
      {"public", VISSPEC, RID_PUBLIC,},
#line 41 "../../../gcc/cp/gxx.gperf"
      {"bitor", '|', NORID,},
#line 72 "../../../gcc/cp/gxx.gperf"
      {"namespace", NAMESPACE, NORID,},
#line 78 "../../../gcc/cp/gxx.gperf"
      {"or_eq", ASSIGN, NORID,},
      {"", 0, 0},
#line 79 "../../../gcc/cp/gxx.gperf"
      {"private", VISSPEC, RID_PRIVATE,},
#line 31 "../../../gcc/cp/gxx.gperf"
      {"__typeof", TYPEOF, NORID},
      {"", 0, 0},
#line 6 "../../../gcc/cp/gxx.gperf"
      {"__alignof", ALIGNOF, NORID},
#line 12 "../../../gcc/cp/gxx.gperf"
      {"__complex", TYPESPEC, RID_COMPLEX},
#line 103 "../../../gcc/cp/gxx.gperf"
      {"union", AGGR, RID_UNION,},
      {"", 0, 0},
#line 16 "../../../gcc/cp/gxx.gperf"
      {"__extension__", EXTENSION, NORID},
      {"", 0, 0},
#line 84 "../../../gcc/cp/gxx.gperf"
      {"return", RETURN_KEYWORD, NORID,},
#line 37 "../../../gcc/cp/gxx.gperf"
      {"and", ANDAND, NORID,},
#line 8 "../../../gcc/cp/gxx.gperf"
      {"__asm", ASM_KEYWORD, NORID},
#line 17 "../../../gcc/cp/gxx.gperf"
      {"__imag", IMAGPART, NORID},
#line 106 "../../../gcc/cp/gxx.gperf"
      {"virtual", SCSPEC, RID_VIRTUAL,},
#line 80 "../../../gcc/cp/gxx.gperf"
      {"protected", VISSPEC, RID_PROTECTED,},
#line 96 "../../../gcc/cp/gxx.gperf"
      {"throw", THROW, NORID,},
#line 52 "../../../gcc/cp/gxx.gperf"
      {"default", DEFAULT, NORID,},
#line 105 "../../../gcc/cp/gxx.gperf"
      {"using", USING, NORID,},
#line 104 "../../../gcc/cp/gxx.gperf"
      {"unsigned", TYPESPEC, RID_UNSIGNED,},
#line 43 "../../../gcc/cp/gxx.gperf"
      {"break", BREAK, NORID,},
      {"", 0, 0},
#line 86 "../../../gcc/cp/gxx.gperf"
      {"signature", AGGR, RID_SIGNATURE	/* Extension */,},
#line 42 "../../../gcc/cp/gxx.gperf"
      {"bool", TYPESPEC, RID_BOOL,},
      {"", 0, 0},
#line 75 "../../../gcc/cp/gxx.gperf"
      {"not_eq", EQCOMPARE, NORID,},
      {"", 0, 0}, {"", 0, 0},
#line 55 "../../../gcc/cp/gxx.gperf"
      {"double", TYPESPEC, RID_DOUBLE,},
#line 87 "../../../gcc/cp/gxx.gperf"
      {"signed", TYPESPEC, RID_SIGNED,},
#line 109 "../../../gcc/cp/gxx.gperf"
      {"while", WHILE, NORID,},
#line 36 "../../../gcc/cp/gxx.gperf"
      {"asm", ASM_KEYWORD, NORID,},
#line 108 "../../../gcc/cp/gxx.gperf"
      {"volatile", CV_QUALIFIER, RID_VOLATILE,},
#line 38 "../../../gcc/cp/gxx.gperf"
      {"and_eq", ASSIGN, NORID,},
      {"", 0, 0},
#line 71 "../../../gcc/cp/gxx.gperf"
      {"mutable", SCSPEC, RID_MUTABLE,},
#line 56 "../../../gcc/cp/gxx.gperf"
      {"dynamic_cast", DYNAMIC_CAST, NORID,},
      {"", 0, 0},
#line 73 "../../../gcc/cp/gxx.gperf"
      {"new", NEW, NORID,},
#line 111 "../../../gcc/cp/gxx.gperf"
      {"xor_eq", ASSIGN, NORID,},
      {"", 0, 0}, {"", 0, 0}, {"", 0, 0}, {"", 0, 0},
      {"", 0, 0}, {"", 0, 0}, {"", 0, 0}, {"", 0, 0},
      {"", 0, 0}, {"", 0, 0}, {"", 0, 0}, {"", 0, 0},
      {"", 0, 0}, {"", 0, 0}, {"", 0, 0}, {"", 0, 0},
      {"", 0, 0}, {"", 0, 0}, {"", 0, 0}, {"", 0, 0},
      {"", 0, 0}, {"", 0, 0}, {"", 0, 0},
#line 58 "../../../gcc/cp/gxx.gperf"
      {"enum", ENUM, NORID,},
      {"", 0, 0}, {"", 0, 0}, {"", 0, 0}, {"", 0, 0},
#line 107 "../../../gcc/cp/gxx.gperf"
      {"void", TYPESPEC, RID_VOID,},
      {"", 0, 0}, {"", 0, 0}, {"", 0, 0},
#line 40 "../../../gcc/cp/gxx.gperf"
      {"bitand", '&', NORID,}
    };

  if (len <= MAX_WORD_LENGTH && len >= MIN_WORD_LENGTH)
    {
      register unsigned int key = hash (str, len);

      if (key <= MAX_HASH_VALUE)
        {
          register const char *s = wordlist[key].name;

          if (*str == *s && !strcmp (str + 1, s + 1))
            return &wordlist[key];
        }
    }
  return 0;
}
