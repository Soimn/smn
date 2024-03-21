#define SMN_IMPLEMENTATION
#include "smn.h"

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
}

int
main(int argc, char** argv)
{
  Test_StringStuff();
	return 0;
}
