// FILE: dataperf.cpp
//
// DESCRIPTION:
//
//   Compare relative performance of data types in SystemC
//   by creating long loops and performing operations on the data.
//
// LICENSE:
//
//   Copyright 2014,2015 David C Black
//
//   Licensed under the Apache License, Version 2.0 (the "License");
//   you may not use this file except in compliance with the License.
//   You may obtain a copy of the License at
//
//       http://www.apache.org/licenses/LICENSE-2.0
//
//   Unless required by applicable law or agreed to in writing, software
//   distributed under the License is distributed on an "AS IS" BASIS,
//   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//   See the License for the specific language governing permissions and
//   limitations under the License.

#include "require_cxx11.h"
#include <cstdint>
#include <cmath>
#include <systemc>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <chrono>
#include <ctime>
#include <string>
#include <cstddef>

using namespace std;
using namespace sc_dt;

namespace {
  chrono::time_point<chrono::system_clock> start, current;
  chrono::duration<double> elapsed_seconds;
  time_t end_time;
  size_t loop_count = 1e8;
}

template<typename T>
void truncate(T& val)
{
  val = T(uint32_t(val)); // Truncate to 32 bits
}

template<>
void truncate<sc_bigint<32>>(sc_bigint<32>& val)
{
}

template<typename T>
void arithperf(void)
{
  cout << "Testing arithmetic " << typeid(T).name() << " occupies " << sizeof(T) << " bytes with loop_count=" << loop_count << " " << flush;
  T result =          1;
  T A      = 1103515245; // Linear congruential constants for 32 bit pseudo-random of max length
  T C      =      12345; // result = (A*result + C) & 0xFFFF_FFFF

  start = chrono::system_clock::now();
  for (size_t loop=loop_count; loop!=0; --loop)
  {
    // Compute
    result = A * result + C;
    truncate<T>(result);
  }
  cout << "result=" << fixed << setprecision(0) << result << " " << flush; // Ensure compiler doesn't optimize loop out
  current = chrono::system_clock::now();
  elapsed_seconds = current - start;
  end_time = chrono::system_clock::to_time_t(current);
  cout << "elapsed time " << setprecision(6) << elapsed_seconds.count() << "s" << endl;
}

template<typename T>
void logicperf(void)
{
  cout << "Testing logic " << typeid(T).name() << " occupies " << sizeof(T) << " bytes with loop_count=" << loop_count << " " << flush;
  size_t tbits = 8*sizeof(T);
  size_t rbits = 17;
  size_t lbits = tbits - rbits;
  T val    =          1;
  T A      = 1103515245; // Linear congruential constants for 32 bit pseudo-random of max length
  T C      =      12345; // val    = (A^ror(val,rbits) ^ C) & 0xFFFF_FFFF
  T rhs, lhs;
  start = chrono::system_clock::now();
  for (size_t loop=loop_count; loop!=0; --loop)
  {
    // Compute
    rhs = (val >> rbits);
    lhs = ((rhs << rbits)^val);
    val = A ^ ((lhs<<lbits)|rhs) ^ C;
  }
  cout << "result=" << fixed << setprecision(0) << val << " " << flush; // Ensure compiler doesn't optimize loop out
  current = chrono::system_clock::now();
  elapsed_seconds = current - start;
  end_time = chrono::system_clock::to_time_t(current);
  cout << "elapsed time " << setprecision(6) << elapsed_seconds.count() << "s" << endl;
}

int sc_main(int argc, char* argv[])
{
  for (int i=1; i<argc; ++i) { // Process command-line
    string arg(argv[i]);
    if (arg.length()>1 and string("-help").find(arg) == 0) {
      cout
        << "SYNOPSIS\n"
        << "  " << argv[0] << " [LOOP_COUNT]\n"
        << "EXAMPLES\n"
        << "  " << argv[0] << "1e7\n"
        << endl
        ;
      return 0;
    } else if (arg.find_first_not_of("0123456789e") == string::npos) {
      istringstream is(arg);
      double d;
      is >> d;
      loop_count = d;
      sc_assert(loop_count != 0);
    }//endif
  }

  arithperf<int32_t>();
  arithperf<sc_int<32>>();
  arithperf<sc_bigint<32>>();
  arithperf<double>();
  arithperf<sc_fixed_fast<32,32>>();
  arithperf<sc_fixed<32,32>>();

  cout << endl;

  logicperf<int32_t>();
  logicperf<sc_int<32>>();
  logicperf<sc_bigint<32>>();
  logicperf<sc_lv<32>>();
  logicperf<sc_bv<32>>();

  cout << "\nCompleted all tests" << endl;
  return 0;
}

//End of file