# Seminar 1. Tools for parallel programming 1: OpenMP directives  

Some directives:

## directive parallel

```
#pragma omp parallel [clause]
        structured block
```

Specify what calculus are executed in parallel.  
A thread (master) create a set of threads when reaching a `parallel` directive.  
Each thread executes the code included in the block region.  

An [example of `Hello World` in `C`].  

```
#include <stdio.h>

#ifdef _OPENMP
  #include <omp.h>
#else
  #define omp_get_thread_num() 0
#endif

main() {

  int ID;
  #pragma omp parallel private(ID)
  {
    ID = omp_get_thread_num();
    printf("Hello(%d)",ID);
    printf("World(%d)\n",ID);
  }
}
```
