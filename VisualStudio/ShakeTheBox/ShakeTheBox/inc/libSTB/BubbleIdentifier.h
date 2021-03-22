//
//  Academic License - for use in teaching, academic research, and meeting
//  course requirements at degree granting institutions only.  Not for
//  government, commercial, or other organizational use.
//
//  BubbleIdentifier.h
//
//  Code generation for function 'BubbleIdentifier'
//


#ifndef BUBBLEIDENTIFIER_H
#define BUBBLEIDENTIFIER_H

// Include files
#include <cstddef>
#include <cstdlib>
#include <string>
#include <deque>
#include "Position.h"
#include "Frame.h"
#include "rtwtypes.h"
#include "BubbleCenterAndSize_types.h"
using namespace std;

// Type Definitions
class BubbleIdentifier
{
public:
    BubbleIdentifier(int**& p, int rows, int cols, int threshold);
    ~BubbleIdentifier();
    void BubbleCenterAndSize();
    void region_props(coder::array<struct0_T, 1U>& center_size);
    Frame CreateFrame();
    void SaveCenter(string file_path);
    void SaveRadius(string file_path);

private:
    int**& img_p;
    int rows;
    int cols;
    int threshold;
    coder::array<bool, 2U> img;
    //coder::array<struct0_T, 1U> center_size;
    //int n_center = 0;
    deque<Position> center;
    deque<double> radius;
};

#endif

// End of code generation (BubbleIdentifier.h)
