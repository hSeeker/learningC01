#include "test.h"
#include <stdio.h>

int test(char str[]) {
  if (str == NULL)
    return 1;
  printf("%s", str);
  return 0;
}
