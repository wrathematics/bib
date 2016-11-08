#include "../src/bib.h"

#include "internal/all_equal.h"

#define CONTEXT(x) printf("## %s\n", x);
#define TEST(x) printf("    * %s: ", x);

int test_mvprod()
{
  int ret;
  const int m = 5;
  const int n = 3;
  
  dmatrix_t x;
  dvector_t v;
  dvector_t test, truth;
  
  CONTEXT("mvprod");
  
  
  TEST("transpose=false");
  
  setmat(m, n, NULL, &x);
  setvec(n, NULL, &v);
  setvec(m, NULL, &truth);
  
  for (int j=0; j<n; j++)
  {
    v.data[j] = j+1;
    
    for (int i=0; i<m; i++)
      x.data[i + m*j] = (i+m*j) + 1;
  }
  
  truth.data[0] = 46;
  truth.data[1] = 52;
  truth.data[2] = 58;
  truth.data[3] = 64;
  truth.data[4] = 70;
  
  mvprod_a(false, 1.0, &x, &v, &test);
  ret = all_equal(true, 1, m, test.data, truth.data);
  
  
  
  TEST("transpose=true");
  
  freevec(&v);
  freevec(&truth);
  freevec(&test);
  
  setvec(m, NULL, &v);
  setvec(n, NULL, &truth);
  
  for (int i=0; i<m; i++)
    v.data[i] = i+1;
  
  truth.data[0] = 55;
  truth.data[1] = 130;
  truth.data[2] = 205;
  
  mvprod_a(true, 1.0, &x, &v, &test);
  ret = all_equal(true, 1, n, test.data, truth.data);
  
  
  freevec(&v);
  freevec(&truth);
  freevec(&test);
  freemat(&x);
  return ret;
}

int main()
{
  printf("\n# Level 2 BLAS tests\n\n");
  test_mvprod();
  
  return 0;
}
