#ifndef SMN_HEADER
#define SMN_HEADER

#include <stdio.h>
#include <stdarg.h>

typedef signed __int8  s8;
typedef signed __int16 s16;
typedef signed __int32 s32;
typedef signed __int64 s64;

typedef unsigned __int8  u8;
typedef unsigned __int16 u16;
typedef unsigned __int32 u32;
typedef unsigned __int64 u64;

typedef u32 uint;

typedef s64 smm;
typedef u64 umm;

typedef u8 bool;
#define true 1
#define false 0

typedef float f32;
typedef double f64;

// TODO
#define MAX(A, B) ((A) > (B) ? (A) : (B))
#define MIN(A, B) ((A) < (B) ? (A) : (B))

#ifndef SMN_NO_ASSERT
#define ASSERT(EX, ...) ((EX) ? 1 : (AssertHandler(__FILE__, __LINE__, #EX, "" __VA_ARGS__), 0))
#else
#define ASSERT(EX, ...)
#endif

void AssertHandler(char* file, uint line, char* expr, char* msg, ...);

typedef struct String
{
	u8* data;
	umm size;
} String;

#define STRING(S) (String){ .data = (u8*)(S), .size = sizeof(S)-1 }

bool Char_IsAlpha(u8 c);
u8 Char_ToLowerUnchecked(u8 c);
u8 Char_ToUpperUnchecked(u8 c);
u8 Char_ToLower(u8 c);
u8 Char_ToUpper(u8 c);

bool String_Match(String s0, String s1);
bool String_MatchCaseInsensitive(String s0, String s1);
String String_EatN(String s, umm amount);
String String_ChopN(String s, umm amount);

typedef struct SB__Header
{
  u32 len;
  u32 cap;
} SB__Header;

#define SB(T) T*

#define SB__Header(S) ((SB__Header*)(*(S)) - 1)
#define SB_Len(S) (*(S) == 0 ? 0 : (u32){SB__Header(S)->len})
#define SB_Cap(S) (*(S) == 0 ? 0 : (u32){SB__Header(S)->cap})
#define SB_Append(S, E) ((*(S))[SB__Resize(S, sizeof(**(S)), alignof(**(S)), SB_Len(S)+1)-1] = (E))
#define SB_Prepend(S, E)

#ifdef SMN_IMPLEMENTATION

void
AssertHandler(char* file, uint line, char* expr, char* msg, ...)
{
  va_list args;
  va_start(args, msg);
  fprintf(stderr, "%s(%u): Assertion \"%s\" failed\n", file, line, expr);
  if (msg != 0)
  {
    // TODO
    vfprintf(stderr, msg, args);
    putc('\n', stderr);
  }
  va_end(args);
}

bool
Char_IsAlpha(u8 c)
{
  return ((u8)((c&0xDF)-'A') <= (u8)('Z' - 'A'));
}

u8
Char_ToLowerUnchecked(u8 c)
{
  return c & 0xDF;
}

u8
Char_ToUpperUnchecked(u8 c)
{
  return c | 0x20;
}

u8
Char_ToLower(u8 c)
{
  return (Char_IsAlpha(c) ? Char_ToLowerUnchecked(c) : c);
}

u8
Char_ToUpper(u8 c)
{
  return (Char_IsAlpha(c) ? Char_ToUpperUnchecked(c) : c);
}

bool
String_Match(String s0, String s1)
{
	bool result = (s0.size == s1.size);

	for (umm i = 0; i < s0.size && result; ++i)
  {
    result = (s0.data[i] == s1.data[i]);
  }

	return result;
}

bool
String_MatchCaseInsensitive(String s0, String s1)
{
	bool result = (s0.size == s1.size);

	for (umm i = 0; i < s0.size && result; ++i)
  {
    result = (Char_ToLower(s0.data[i]) == Char_ToLower(s1.data[i]));
  }

	return result;
}

String
String_EatN(String s, umm amount)
{
  return (String){
    .data = s.data + amount,
    .size = MAX(s.size, amount) - amount,
  };
}

String
String_ChopN(String s, umm amount)
{
  return (String){
    .data = s.data,
    .size = MAX(s.size, amount) - amount,
  };
}

u32
SB__Resize(void** sbuf, umm elem_size, u8 elem_align, umm new_len)
{
  ASSERT(sizeof(SB__Header) % 8 == 0);

  if (*sbuf == 0)
  {
    umm new_cap = MAX(new_len, 4);
    *sbuf = (u8*)malloc(sizeof(SB__Header) + new_cap*elem_size) + sizeof(SB__Header);
  }
  else if (SB__Header(sbuf)->cap < new_len)
  {
    umm new_cap = 2*SB__Header(sbuf)->cap;
    if (new_cap < new_len) new_cap = new_len;

    *sbuf = (u8*)realloc((u8*)*sbuf - sizeof(SB__Header), sizeof(SB__Header) + SB__Header(sbuf)->cap*elem_size, sizeof(SB__Header) + new_cap*elem_size) + sizeof(SB__Header);
    SB__Header(sbuf)->cap = new_cap;
  }

  SB__Header(sbuf)->len = new_len;

  return new_len;
}

#endif
#endif
