#pragma once
#include "../List.h"
#include "Fixtures/CustomAsserts.h"

namespace test
{
  struct SortTest
  {

    SortTest()
    {
      List<int> lst{6, 5, 1, 2, 4, 3, 7};

      lst.sort();

      int value = 0;
      for(int x: lst)
        assertEqual(x, ++value, __LINE__, __FILE__);
    }
  };

  static SortTest sortTest;
}