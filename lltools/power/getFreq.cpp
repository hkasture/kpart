/** $lic$
* MIT License
* 
* Copyright (c) 2017-2018 by Massachusetts Institute of Technology
* Copyright (c) 2017-2018 by Qatar Computing Research Institute, HBKU
* 
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
* 
* The above copyright notice and this permission notice shall be included in all
* copies or substantial portions of the Software.
* 
* If you use this software in your research, we request that you reference
* the KPart paper ("KPart: A Hybrid Cache Partitioning-Sharing Technique for
* Commodity Multicores", El-Sayed, Mukkara, Tsai, Kasture, Ma, and Sanchez,
* HPCA-24, February 2018) as the source in any publications that use this
* software, and that you send us a citation of your work.
* 
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
**/
#include <assert.h>
#include "dvfs.h"
#include <iostream>
#include <stdlib.h>
#include "sysconfig.h"
#include <unistd.h>
#include <vector>

using namespace std;

int main(int argc, char *argv[]) {
  int numCores = getNumCores();
  vector<int> freqs = getFreqsMHz();
  vector<int> cores;

  int c;
  while ((c = getopt(argc, argv, "ac:")) != -1) {
    switch (c) {
    case 'a':
      cores.clear();
      for (int c = 0; c < numCores; c++)
        cores.push_back(c);
      break;
    case 'c':
      int core = atoi(optarg);
      assert(core < numCores);
      cores.clear();
      cores.push_back(core);
      break;
    }
  }

  assert(cores.size() > 0);

  VFController ctrl;
  for (int c : cores) {
    cout << "Core " << c << " | Freq Target = " << ctrl.getFreqTgt(c)
         << " MHz | Freq = " << ctrl.getFreq(c) << " MHz" << endl;
  }

  return 0;
}
