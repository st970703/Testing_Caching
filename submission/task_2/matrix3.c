/* do not add other includes */
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>

//elee353
double getTime(){
  struct timeval t;
  double sec, msec;

  while (gettimeofday(&t, NULL) != 0);
  sec = t.tv_sec;
  msec = t.tv_usec;

  sec = sec + msec/1000000.0;

  return sec;
}

/* for task 1 only */
void usage(void)
{
	fprintf(stderr, "Usage: cachetest1/2 [--repetitions M] [--array_size N]\n");
	exit(1);
}

int main (int argc, char *argv[])
{
  double t1, t2;

  /* variables for task 1 */
  unsigned int M = 1000;
  unsigned int N = 256*1024;

  /* declare variables; examples, adjust for task */
  double **a;
  double **b;
  double **c;

  double sum = 0;

  /* parameter parsing task 1 */
  for(int i=1; i<(unsigned)argc; i++) {
	  if (strcmp(argv[i], "--repetitions") == 0) {
		  i++;
		  if (i < argc)
			  sscanf(argv[i], "%u", &M);
		  else
			  usage();
	  } else if (strcmp(argv[i], "--array_size") == 0) {
		  i++;
		  if (i < argc)
			  sscanf(argv[i], "%u", &N);
		  else
			  usage();
	  } else usage();
  }


  /* allocate memory for arrays; examples, adjust for task */
  a = (double **)malloc(N * sizeof(double*));
  b = (double **)malloc(N * sizeof(double*));
  c = (double **)malloc(N * sizeof(double*));

	 /* initialise matrix elements */
   for(int i = 0; i < N; i++) {

     a[i] = (double *)malloc(N * sizeof(double));
     b[i] = (double *)malloc(N * sizeof(double));
     c[i] = (double *)malloc(N * sizeof(double));

   }

 /* initialise matrix elements */
   for (int i = 0; i < N; i++) {
     for (int j = 0; j < N; j++) {
       a[i][j] = i;
       b[i][j] = i;
     }
   }

  unsigned int i = 0;
  unsigned int j = 0;
  unsigned int k = 0;

  t1 = getTime();

  double **temp;

unsigned int l, m = 0;

  /* code to be measured goes here */
  /***************************************/
  int block_size = 8;

	int en = block_size * (N/block_size);

	for (l = 0; l < en; l += block_size) {
		for (m = 0; m < en; m += block_size) {
			for (i = 0; i < N; i++) {
				for (j = m; j < m + block_size; j++) {
					sum = c[i][j];
					for (k = l; k < l + block_size; k++) {
						sum = sum + a[i][k]*b[k][j];
					}
					c[i][j] = sum;
				}
			}
		}
	}
  /***************************************/
	t2 = getTime();

  /* output; examples, adjust for task */
  printf("time: %6.2f secs\n",(t2 - t1));
  // printf("a matrix:\n");
  //   for (i = 0; i < N; i++) {
  //     for (j = 0; j < N; j++)
  //       printf("%6.2f\t", a[i][j]);
	//
  //     printf("\n");
  //   }
	//
  //   printf("b matrix:\n");
  //     for (i = 0; i < N; i++) {
  //       for (j = 0; j < N; j++)
  //         printf("%6.2f\t", b[i][j]);
	//
  //       printf("\n");
  //     }
	//
  // printf("c matrix:\n");
  //   for (i = 0; i < N; i++) {
  //     for (j = 0; j < N; j++)
  //       printf("%6.2f\t", c[i][j]);
	//
  //     printf("\n");
  //   }

  /* IMPORTANT: also print the result of the code, e.g. the sum,
   * otherwise compiler might optimise away the code */

  /* free memory; examples, adjust for task */
  free(a);
  free(b);
  free(c);

  return 0;
}
