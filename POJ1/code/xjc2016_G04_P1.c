/*project1 
 Algorithm 1 is to use N - 1 multiplications.
 Algorithm 2 works in the following way: if N is even, XN = XN / 2  XN / 2; and
 if N is odd, XN = X(N – 1) / 2  X(N – 1) / 2  X.
 Figure 2.11 in your textbook gives the recursive version of this algorithm.
 */
#include <stdio.h>
#include <time.h>
clock_t start, stop; /* clock_t is a built-in type for processor time (ticks) */
double duration1, duration2,duration3; /* records the run time (seconds) of a function */

#define Iterations 1000000

double AL1_Pow(double x, long int n);
double AL2_Pow(double x, long int n);
double AL3_Pow(double x, long int n);
int IsEven(long int n);

int main() {
  double x;
  long int n;
  long int i;
  double Result1 = 0, Result2 = 0, Result3 = 0;
  long int Ticks1 = 0, Ticks2 = 0, Ticks3 = 0;
  printf("Input the base and the exponent, please:\n");
  scanf("%lf%d", &x, &n);

  start = clock(); // start time counting for Alg1
  for (i = 0; i < Iterations; i++) {
    Result1 = AL1_Pow(x, n);
  }
  stop = clock(); // stop time counting for Alg1
  Ticks1 = stop - start;
  duration1 = ((double)(stop - start)) / CLOCKS_PER_SEC;

  start = clock(); // start time counting for Alg2
  for (i = 0; i < Iterations; i++) {
    Result2 = AL2_Pow(x, n);
  }
  stop = clock(); // stop time counting for Alg2
  Ticks2 = stop - start;
  duration2 = ((double)(stop - start)) / CLOCKS_PER_SEC;

  start = clock(); // start time counting for Alg3
  for (i = 0; i < Iterations; i++) {
    Result3 = AL3_Pow(x, n);
  }
  stop = clock(); // stop time counting for Alg3
  Ticks3 = stop - start;
  duration3 = ((double)(stop - start)) / CLOCKS_PER_SEC;

  printf("result1 is %lf ,the first algorithm uses %lf secs(%d ticks)\n",
         Result1, duration1, Ticks1);
  printf("result2 is %lf ,the second algorithm uses %lf secs(%d ticks)\n",
         Result2, duration2, Ticks2);
  printf("result3 is %lf ,the third algorithm uses %lf secs(%d ticks)\n",
         Result3, duration3, Ticks3);
  return 0;
}

/* Function:AL1_Pow
 * Usage: Result = AL1_Pow(x,n);
 * -----------------------------
 * use N – 1 multiplications to calculate the result.
 */
double AL1_Pow(double x, long int n) {
  /* Initialising the result to be 1 can avoid discussing the case when n = 0 */
  double result = 1;
  long int i;
  /* do the multiplications */
  for (i = 0; i < n; i++) {
    result *= x;
  }
  return result;
}

/* Function:AL2_Pow
 * Usage: Result = AL2_Pow(x,n);
 *-----------------------------
 * an iterative version of Algorithm 2;the exponent n can be showed in the
 *binary form;
 * Take 3^15 as an exampl.We konw 15(decimal） = 1111 （binary）which means
 * 3^15 = 3^8 * 3^4 * 3^2 * 3 and then, use the following function:
 * Firstly,after finding the lowest order of 1111 is 1,let result * 3^1 and by
 *making n = n>>1,1111
 * is changed into 111;
 * Secondly,after finding the lowest order of 111 is 1,let result * 3^2 and by
 *making n = n>>1,111
 * is changed into 11;
 * Thirdly,after finding the lowest order of 11 is 1,let result * 3^4 and by
 *making n = n>>1,11
 * is changed into 1;
 * Finally,after finding the lowest order of 1 is 1,let result * 3^8 and by
 *making n = n>>1,1
 * is changed into 0.Quit the while;
 */
double AL2_Pow(double x, long int n) {
  /* Initialising the result to be 1 can avoid discussing the case when n = 0 */
  double result = 1;
  double t = x;
  /**/
  while (n > 0) {
    /*if the lowest order of n in binary form is 1 */
    if ((n & 1) != 0) {
      result = result * t;
    }
    /* n>>1 is the same as n/2*/
    n = n >> 1;
    t = t * t;
  }
  return result;
}
/* Function:AL2_Pow
 * Usage: Result = AL2_Pow(x,n);
 *-----------------------------
 * Recursing version in textbook
 */
double AL3_Pow(double x, long int n) {
  if (n == 0) /*when n = 0 ,the rusult is 1*/
    return 1;
  if (n == 1) /*when n = 1 ,the rusult is x itself*/
    return x;
  if (IsEven(n)) /*judge if n is even*/
    return AL3_Pow(x * x, n / 2);
  else /*n is odd*/
    return AL3_Pow(x * x, n / 2) * x;
}
/* Function:IsEven
 * Usage: Result = IsEven(n);
 *-----------------------------
 * judge a number is odd or not
 * if the n is EVEN, n-n/2 will equal to n/2; else it will be odd
 */
int IsEven(long int n) {
  if (n - n / 2 == n / 2)
    /*n/2 will be a interger ,so when n is odd ,n/2 isn't equal to n-n/2*/
    return 1;
  else
    return 0;
}
