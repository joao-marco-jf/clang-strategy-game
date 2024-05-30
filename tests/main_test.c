#include "CUnit/Basic.h"
#include "example.h"

void sum_test() {
  CU_ASSERT_EQUAL(sum(2, 14), 16);
  CU_ASSERT_EQUAL(sum(0, 0), 0);
  CU_ASSERT_EQUAL(sum(-1 ,6), 5);
}

int main() {
   if (CUE_SUCCESS != CU_initialize_registry())
      return CU_get_error();

   CU_pSuite pSuite = NULL;

   pSuite = CU_add_suite("sum_test_suite", 0, 0);

   if (NULL == pSuite) {
     CU_cleanup_registry();
     return CU_get_error();
   }

   if (NULL == CU_add_test(pSuite, "sum_test", sum_test)) {
     CU_cleanup_registry();
     return CU_get_error();
   }

   CU_basic_set_mode(CU_BRM_VERBOSE);
   CU_basic_run_tests();
   return CU_get_error();
}