#include "util.h"

int ipow(int base, int exp){
  int result = 1;
  while(exp){
    if (exp & 1)
      result *= base;
    exp >>= 1;
    base *= base;
  }
  
  return result;
}

uint64_t rdtsc(){
  unsigned int lo,hi;
  __asm__ __volatile__ ("rdtsc" : "=a" (lo), "=d" (hi));
  return ((uint64_t)hi << 32) | lo;
}
