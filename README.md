# About the `dataperf` project

The source code accompanying this readme contains example code to measure the run-time performance efficiency of various SystemC data types. If you wish to run this code yourself, you will need:

1. C++ compiler with C++11 features
   * Minimum: clang 5.0 or GCC 4.7 or Visual C++ 2013
2. SystemC 2.3 or better
   * Obtain from accellera.org
4. `cmake` 3.20 or better

You can use `cmake` under Linux as follows:

```bash
rm -fr build;
source setup.profile;
cmake -S . -B build -DCMAKE_PREFIX_PATH="${PROJECT_DIR}" 2>&1 | tee config.log;
cmake --build build 2>&1 | tee compile.log;
ctest --test-dir build -V 2>&1 | tee test.log;
```

Or use the included `boostrap.bash` script.

Of course, you can also use `gmake`; however, you will need to modify `GNUmakefile` to suit your configuration.
