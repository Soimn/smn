#ifndef SMN_HEADER
#define SMN_HEADER

typedef signed __int8  s8;
typedef signed __int16 s16;
typedef signed __int32 s32;
typedef signed __int64 s64;

typedef unsigned __int8  u8;
typedef unsigned __int16 u16;
typedef unsigned __int32 u32;
typedef unsigned __int64 u64;

typedef s64 smm;
typedef u64 umm;

typedef u8 bool;
#define true 1
#define false 0

typedef float f32;
typedef double f64;

typedef struct String
{
	u8* data;
	umm size;
} String;

#define STRING(S) (String){ .data = (u8*)(S), .size = sizeof(S)-1 }

bool String_Match(String s0, String s1);

#ifdef SMN_IMPLEMENTATION

bool
String_Match(String s0, String s1)
{
	bool result = (s0.size == s1.size);

	for (umm i = 0; i < s0.size && result; ++i) result = (s0.data[i] == s1.data[i]);

	return result;
}

#endif
#endif
