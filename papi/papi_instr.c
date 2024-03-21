/*
** This is a short file to show instrumentation of source with PAPI
*/
#include <stdio.h>
#include <stdlib.h>
#include <papi.h>

/*
** Some "interesting" function or other peice of code
*/
void work() {
  int iterations = 0;
  const int N=2000000;
  int results[N];
  for (int i=1;i<=N;++i) {
    unsigned long int n = i;
    int step = 0;
    while (n != 1) {
      ++step;
      if (n&1) n = 3*n+1;
      else n>>=1;
    }
    results[i-1] = step;
    iterations += step;
  }
  printf("The 3N+1 problem from 1 to N=%d took %d iterations\n",N,iterations);
}

/*
** We can either continually set and check for PAPI_OK, or use a define
*/
#define PAPI_CHECK(papi_call)                               \
   do {                                                     \
      const int papicheck = papi_call;                      \
      if (papicheck != PAPI_OK) {                           \
         fprintf(stderr, "ERROR: %s (%d) at %s:%d\n",       \
                      PAPI_strerror(papicheck), papicheck,  \
                      __FILE__, __LINE__);                  \
				return EXIT_FAILURE;                                \
      }                                                     \
   }while (0)

/*
** The number of PAPI events we want to use
*/
#define NUM_EVENTS 3


int main(int argc,char **argv) {

  /*
  ** Initialize PAPI
  */
  int retval = PAPI_library_init(PAPI_VER_CURRENT);
  if (retval != PAPI_VER_CURRENT) {
    fprintf(stderr,"Error initializing PAPI\n");
    return EXIT_FAILURE;
  }

  /*
  ** Create an event set
  */
  int eventset = PAPI_NULL;
  PAPI_CHECK(PAPI_create_eventset(&eventset));

  /*
  ** The "string" NATIVE counter names we want to use
  */
  char *eventnames[NUM_EVENTS] = {"perf::INSTRUCTIONS",
                                  "perf::CYCLES",
                                  "ix86arch::LLC_MISSES"};

  /*
  ** Get the numeric counter codes for each name and add them
  */
  int events[NUM_EVENTS];
  for (int i=0;i<NUM_EVENTS;++i) {
    PAPI_CHECK(PAPI_event_name_to_code(eventnames[i],&events[i]));
  }
  PAPI_CHECK(PAPI_add_events(eventset, events, NUM_EVENTS));

  /*
  ** Start counting
  */
  PAPI_CHECK(PAPI_start(eventset));

  /*
  ** Counters are collected within this region
  */
  work();

  /*
  ** Stop counting and get values
  */
  long long values[NUM_EVENTS];
  PAPI_CHECK(PAPI_stop(eventset, values));

  /*
  ** Print the values with the counter names
  */
  for (int i=0;i<NUM_EVENTS;++i) {
    printf("%s: %lld\n", eventnames[i], values[i]);
  }

  /*
  ** Cleanup and destroy the eventset
  */
  PAPI_CHECK(PAPI_cleanup_eventset(eventset));
  PAPI_CHECK(PAPI_destroy_eventset(&eventset));

  return EXIT_SUCCESS;
}
