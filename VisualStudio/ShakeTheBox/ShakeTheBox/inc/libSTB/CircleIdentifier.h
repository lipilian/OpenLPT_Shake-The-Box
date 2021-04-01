//
//  Academic License - for use in teaching, academic research, and meeting
//  course requirements at degree granting institutions only.  Not for
//  government, commercial, or other organizational use.
//
//  CircleIdentifier.h
//
//  Code generation for function 'CircleIdentifier'
//


#ifndef CIRCLEIDENTIFIER_H
#define CIRCLEIDENTIFIER_H

// Include files
#include <cstddef>
#include <cstdlib>
#include <deque>
#include "Position.h"
#include "rtwtypes.h"
#include "omp.h"
#include "BubbleCenterAndSizeByCircle_types.h"
#include "Frame.h"

using namespace std;

// Type Definitions
class CircleIdentifier
{
 public:
  CircleIdentifier(int**& p, int rows, int cols, int threshold);
  ~CircleIdentifier();
  void BubbleCenterAndSizeByCircle(double rmin, double rmax);
  Frame CreateFrame();

private:
    int**& img_p;
    int rows;
    int cols;
    int threshold;
    coder::array<bool, 2U> img;
    deque<Position> center;
    deque<double> radius;
};

#define MAX_THREADS                    omp_get_max_threads()
#endif

// End of code generation (CircleIdentifier.h)
