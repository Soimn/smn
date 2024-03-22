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

int
main(int argc, char** argv)
{
  Test_StringStuff();
  Test_SB();
	return 0;
}
