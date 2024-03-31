#define SMN_IMPLEMENTATION
#include "smn.h"

#include <ctype.h>

void
Test_StringStuff()
{
  String s0 = STRING("aaba");
  String s1 = STRING("abba");
  String s2 = STRING("aBba");

  ASSERT(!String_Match(s0, s1));
  ASSERT(String_Match(String_ChopN(s0, 3), String_ChopN(s1, 3)));
  ASSERT(String_Match(String_EatN(s0, 2), String_EatN(s1, 2)));
  ASSERT(!String_Match(s1, s2));
  ASSERT(String_MatchCaseInsensitive(s1, s2));

  ASSERT(String_Match(String_EatMaxN(s0, 5), STRING("")));
  ASSERT(String_Match(String_EatMaxN(s0, 3), String_EatN(s0, 3)));
  ASSERT(String_Match(String_ChopMaxN(s0, 5), STRING("")));
  ASSERT(String_Match(String_ChopMaxN(s0, 3), String_ChopN(s0, 3)));

  ASSERT(String_Match(String_FirstN(s0, 2), STRING("aa")));
  ASSERT(String_Match(String_LastN(s0, 2), STRING("ba")));
  ASSERT(String_Match(String_FirstMaxN(s0, 3), String_FirstN(s0, 3)));
  ASSERT(String_Match(String_LastMaxN(s0, 3), String_LastN(s0, 3)));
  ASSERT(String_Match(String_FirstMaxN(s0, 5), s0));
  ASSERT(String_Match(String_LastMaxN(s0, 5), s0));

  ASSERT(String_Match(String_EatWhitespace(STRING("   \t\r\f \v \n  aBb a")), STRING("aBb a")));

  ASSERT(String_FindFirstChar(STRING("ABCDEFGHIJKLMNOPQRSTUVWXYZ"), 'A') == 0);
  ASSERT(String_FindFirstChar(STRING("ABCDEFGHIJKLMNOPQRSTUVWXYZ"), 'P') == 'P'-'A');
  ASSERT(String_FindFirstChar(STRING("ABCDEFFFFGHIJKLMNOOOOPQRSTUVWXYZ"), 'O') == 17);
  ASSERT(String_FindLastChar(STRING("ABCDEFGHIJKLMNOPQRSTUVWXYZ"), 'A') == 0);
  ASSERT(String_FindLastChar(STRING("ABCDEFGHIJKLMNOPQRSTUVWXYZ"), 'P') == 'P'-'A');
  ASSERT(String_FindLastChar(STRING("ABCDEFFFFGHIJKLMNOOOOPQRSTUVWXYZ"), 'O') == 20);
}

void
Test_SB()
{
  SB(int) ia = 0;
  ASSERT(SB_Len(&ia) == 0 && SB_Cap(&ia) == 0);
  SB_Append(&ia, 3);
  ASSERT(SB_Len(&ia) == 1 && SB_Cap(&ia) == 4 && ia[0] == 3);
  SB_Prepend(&ia, 2);
  ASSERT(SB_Len(&ia) == 2 && SB_Cap(&ia) == 4 && ia[0] == 2 && ia[1] == 3);
  SB_Append(&ia, 4);
  SB_Prepend(&ia, 1);
  ASSERT(SB_Len(&ia) == 4 && SB_Cap(&ia) == 4 && ia[0] == 1 && ia[1] == 2 && ia[2] == 3 && ia[3] == 4);
  SB_UnorderedRemove(&ia, 1);
  ASSERT(SB_Len(&ia) == 3 && SB_Cap(&ia) == 4 && ia[0] == 1 && ia[1] == 4 && ia[2] == 3);
  SB_OrderedRemove(&ia, 1);
  ASSERT(SB_Len(&ia) == 2 && SB_Cap(&ia) == 4 && ia[0] == 1 && ia[1] == 3);
}

void
Test_Char()
{
  for (uint i = 0; i < 256; ++i)
  {
    u8 c = (u8)i;

    ASSERT(Char_IsAlpha(c) == (isupper(c) || islower(c)), "for char: %c", c);
    ASSERT(!Char_IsAlpha(c) || Char_ToLowerUnchecked(c) == tolower(c), "for char: %c", c);
    ASSERT(!Char_IsAlpha(c) || Char_ToUpperUnchecked(c) == toupper(c), "for char: %c", c);
    ASSERT(Char_ToLower(c) == tolower(c), "for char: %c. (%c vs %c)", c, Char_ToLower(c), tolower(c));
    ASSERT(Char_ToUpper(c) == toupper(c), "for char: %c. (%c vs %c)", c, Char_ToUpper(c), toupper(c));
    ASSERT(Char_IsWhitespace(c) == !!isspace(c), "for char: 0x%X", c);
    ASSERT(Char_IsDigit(c) == !!isdigit(c), "for char: %c", c);
    ASSERT(Char_IsHexAlphaDigit(c) == (!isdigit(c) && isxdigit(c)), "for char: %c", c);
  }
}

void
Test_SBMap()
{
  SBMap(String, int) si;
  SBMap_CreateT(&si, String);

  SBMap_Put(&si, STRING("Hello"), 42);
  SBMap_Put(&si, STRING("World"), 69);

  ASSERT(SBMap_Has(&si, STRING("Hello")));
  ASSERT(SBMap_Has(&si, STRING("World")));
  ASSERT(({ int v = 0; SBMap_Get(&si, STRING("Hello"), &v); v; }) == 42);
  ASSERT(({ int v = 0; SBMap_Get(&si, STRING("World"), &v); v; }) == 69);

  SBMap_Clr(&si);
  ASSERT(!SBMap_Has(&si, STRING("Hello")));
  ASSERT(!SBMap_Has(&si, STRING("World")));

  SBMap_Destroy(&si);
  ASSERT(si == 0);

  // TODO:
}

int
main(int argc, char** argv)
{
  Test_StringStuff();
  Test_SB();
  Test_Char();
  Test_SBMap();
  printf("All tests passed\n");

  return 0;
}
