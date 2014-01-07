// FILE: dataperf.cpp
//
// DESCRPTION:
//
//   Compare relative performance of data types in SystemC
//   by creating long loops and performing arithmetic.
//
// LICENSE:
//
//   Copyright 2014 David C Black
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
#include <cassert>
#include <systemc>
#include <iostream>
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
}

void start_timer(void)
{
  start = chrono::system_clock::now();
}

void report_time(const string& mesg)
{
  current = chrono::system_clock::now();
  elapsed_seconds = current - start;
  end_time = chrono::system_clock::to_time_t(current);
  cout << mesg << " took " << elapsed_seconds.count() << "s" << endl;
}

int sc_main(int argc, char* argv[])
{
  size_t loop_count = 1e8;
  if (argc > 1) {
    string arg(argv[1]);
    istringstream is(arg);
    long long int lli;
    is >> lli;
    loop_count = lli;
    assert(loop_count != 0);
  }

  {
    using data_t = int32_t;
    data_t result = 1;
    data_t A = 1103515245;
    data_t C = 12345;

    start_timer();
    for (size_t loop=loop_count; loop!=0; --loop)
    {
      result = A * result + C;
    }
    cout << "result=" << result << endl; // Ensure compiler doesn't optimize loop out
    report_time(typeid(data_t).name());
  }

  {
    using data_t = sc_int<32>;
    data_t result = 1;
    data_t A = 1103515245;
    data_t C = 12345;

    start_timer();
    for (size_t loop=loop_count; loop!=0; --loop)
    {
      result = A * result + C;
    }
    cout << "result=" << result << endl; // Ensure compiler doesn't optimize loop out
    report_time(typeid(data_t).name());
  }

  {
    using data_t = double;
    data_t result = 1;
    data_t A = 1103515245;
    data_t C = 12345;
    data_t B = 1LL<<32;

    start_timer();
    for (size_t loop=loop_count; loop!=0; --loop)
    {
      result = A * result + C;
      if (result >= B) result -= B;
    }
    cout << "result=" << result << endl; // Ensure compiler doesn't optimize loop out
    report_time(typeid(data_t).name());
  }

  {
    using data_t = sc_fixed<32,32>;
    data_t result = 1;
    data_t A = 1103515245;
    data_t C = 12345;

    start_timer();
    for (size_t loop=loop_count; loop!=0; --loop)
    {
      result = A * result + C;
    }
    cout << "result=" << result << endl; // Ensure compiler doesn't optimize loop out
    report_time(typeid(data_t).name());
  }

  return 0;
}

//End of file
