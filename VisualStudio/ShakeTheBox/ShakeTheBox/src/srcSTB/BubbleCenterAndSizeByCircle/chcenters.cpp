//
//  Academic License - for use in teaching, academic research, and meeting
//  course requirements at degree granting institutions only.  Not for
//  government, commercial, or other organizational use.
//
//  chcenters.cpp
//
//  Code generation for function 'chcenters'
//


// Include files
#include "chcenters.h"
#include "BubbleCenterAndSizeByCircle_rtwutil.h"
#include "CircleIdentifier.h"
#include "NeighborhoodProcessor.h"
#include "chradii.h"
#include "imhmax.h"
#include "medfilt2.h"
#include "minOrMax.h"
#include "Cregionprops.h"
#include "rt_nonfinite.h"
#include "sort.h"
#include <cstring>

// Function Definitions
void chcenters(const coder::array<creal_T, 2U> &varargin_1, coder::array<double,
               2U> &centers, coder::array<double, 2U> &metric)
{
  int nx;
  coder::array<double, 2U> accumMatrixRe;
  int k;
  coder::array<bool, 1U> x;
  int i;
  bool continuePropagation;
  bool exitg1;
  coder::array<double, 2U> Hd;
  coder::array<double, 2U> b_accumMatrixRe;
  c_images_internal_coder_Neighbo np;
  coder::array<bool, 2U> bw;
  coder::array<struct_TT, 1U> s;
  coder::array<bool, 2U> bwpre;
  int b_np[2];
  int iv[9];
  int iv1[9];
  bool c_np[9];
  coder::array<double, 1U> b_x;
  b_struct_TT expl_temp;
  coder::array<double, 1U> c_x;
  coder::array<int, 2U> iidx;
  centers.set_size(0, 0);
  metric.set_size(0, 0);
  nx = varargin_1.size(0) * varargin_1.size(1);
  accumMatrixRe.set_size(varargin_1.size(0), varargin_1.size(1));
  for (k = 0; k < nx; k++) {
    accumMatrixRe[k] = rt_hypotd_snf(varargin_1[k].re, varargin_1[k].im);
  }

  x.set_size((accumMatrixRe.size(0) * accumMatrixRe.size(1)));
  nx = accumMatrixRe.size(0) * accumMatrixRe.size(1);
  for (i = 0; i < nx; i++) {
    x[i] = (accumMatrixRe[i] == accumMatrixRe[0]);
  }

  continuePropagation = true;
  nx = 1;
  exitg1 = false;
  while ((!exitg1) && (nx <= x.size(0))) {
    if (!x[nx - 1]) {
      continuePropagation = false;
      exitg1 = true;
    } else {
      nx++;
    }
  }

  if (!continuePropagation) {
    unsigned int varargin_1_idx_0;
    unsigned int varargin_1_idx_1;
    int b_i;
    varargin_1_idx_0 = static_cast<unsigned int>(accumMatrixRe.size(0));
    varargin_1_idx_1 = static_cast<unsigned int>(accumMatrixRe.size(1));
    if (static_cast<int>(varargin_1_idx_0) > static_cast<int>(varargin_1_idx_1))
    {
      nx = static_cast<int>(varargin_1_idx_1);
    } else {
      nx = static_cast<int>(varargin_1_idx_0);
    }

    if (nx > 5) {
      if ((accumMatrixRe.size(0) == 0) || (accumMatrixRe.size(1) == 0)) {
        Hd.set_size(accumMatrixRe.size(0), accumMatrixRe.size(1));
        nx = accumMatrixRe.size(0) * accumMatrixRe.size(1);
        for (i = 0; i < nx; i++) {
          Hd[i] = accumMatrixRe[i];
        }
      } else {
        b_accumMatrixRe.set_size(accumMatrixRe.size(0), accumMatrixRe.size(1));
        nx = accumMatrixRe.size(0) * accumMatrixRe.size(1) - 1;
        for (i = 0; i <= nx; i++) {
          b_accumMatrixRe[i] = accumMatrixRe[i];
        }

        medfilt2(b_accumMatrixRe, Hd);
      }
    } else {
      Hd.set_size(accumMatrixRe.size(0), accumMatrixRe.size(1));
      nx = accumMatrixRe.size(0) * accumMatrixRe.size(1);
      for (i = 0; i < nx; i++) {
        Hd[i] = accumMatrixRe[i];
      }
    }

    b_accumMatrixRe.set_size(Hd.size(0), Hd.size(1));
    nx = Hd.size(0) * Hd.size(1) - 1;
    for (i = 0; i <= nx; i++) {
      b_accumMatrixRe[i] = Hd[i];
    }

    imhmax(b_accumMatrixRe, Hd);
    np.ImageSize[0] = Hd.size(0);
    np.ImageSize[1] = Hd.size(1);
    np.Padding = 1.0;
    np.ProcessBorder = true;
    np.NeighborhoodCenter = 1.0;
    np.PadValue = 0.0;
    for (b_i = 0; b_i < 9; b_i++) {
      np.Neighborhood[b_i] = true;
      np.ImageNeighborLinearOffsets[b_i] = 0;
      np.NeighborLinearIndices[b_i] = 0;
    }

    std::memset(&np.NeighborSubscriptOffsets[0], 0, 18U * sizeof(int));
    varargin_1_idx_0 = static_cast<unsigned int>(Hd.size(0));
    varargin_1_idx_1 = static_cast<unsigned int>(Hd.size(1));
    bw.set_size((static_cast<int>(varargin_1_idx_0)), (static_cast<int>
      (varargin_1_idx_1)));
    nx = static_cast<int>(varargin_1_idx_0) * static_cast<int>(varargin_1_idx_1);
    for (i = 0; i < nx; i++) {
      bw[i] = true;
    }

    continuePropagation = true;
    while (continuePropagation) {
      bool p;
      bwpre.set_size(bw.size(0), bw.size(1));
      nx = bw.size(0) * bw.size(1);
      for (i = 0; i < nx; i++) {
        bwpre[i] = bw[i];
      }

      for (b_i = 0; b_i < 9; b_i++) {
        iv[b_i] = np.ImageNeighborLinearOffsets[b_i];
        iv1[b_i] = np.NeighborLinearIndices[b_i];
      }

      b_np[0] = np.ImageSize[0];
      b_np[1] = np.ImageSize[1];
      for (int i1 = 0; i1 < 9; i1++) {
        c_np[i1] = np.Neighborhood[i1];
      }

      c_images_internal_coder_Neighbo::computeParameters((b_np), (c_np), (iv),
        (iv1), (np.NeighborSubscriptOffsets), (np.InteriorStart),
        (np.InteriorEnd));
      for (b_i = 0; b_i < 9; b_i++) {
        np.ImageNeighborLinearOffsets[b_i] = iv[b_i];
        np.NeighborLinearIndices[b_i] = iv1[b_i];
      }

      expl_temp.bw.set_size(bw.size(0), bw.size(1));
      nx = bw.size(0) * bw.size(1);
      for (i = 0; i < nx; i++) {
        expl_temp.bw[i] = bw[i];
      }

      np.process2D(Hd, bw, (&expl_temp));
      p = false;
      if ((bwpre.size(0) == bw.size(0)) && (bwpre.size(1) == bw.size(1))) {
        p = true;
      }

      if (p && ((bwpre.size(0) != 0) && (bwpre.size(1) != 0)) && ((bw.size(0) !=
            0) && (bw.size(1) != 0))) {
        k = 0;
        exitg1 = false;
        while ((!exitg1) && (k <= bw.size(0) * bw.size(1) - 1)) {
          if (bwpre[k] != bw[k]) {
            p = false;
            exitg1 = true;
          } else {
            k++;
          }
        }
      }

      continuePropagation = p;
      continuePropagation = !continuePropagation;
    }

    Cregionprops(bw, accumMatrixRe, s);
    if (s.size(0) != 0) {
      int idx;
      centers.set_size(s.size(0), 2);
      i = s.size(0);
      for (idx = 0; idx < i; idx++) {
        centers[idx] = s[idx].WeightedCentroid[0];
        centers[idx + centers.size(0)] = s[idx].WeightedCentroid[1];
      }

      i = centers.size(0) - 1;
      k = static_cast<int>(((-1.0 - static_cast<double>(centers.size(0))) + 1.0)
                           / -1.0);
      for (idx = 0; idx < k; idx++) {
        int b_idx;
        b_idx = i - idx;
        if (rtIsNaN(centers[b_idx]) || rtIsNaN(centers[b_idx + centers.size(0)]))
        {
          int nrows;
          accumMatrixRe.set_size(centers.size(0), centers.size(1));
          nx = centers.size(0) * centers.size(1);
          for (b_i = 0; b_i < nx; b_i++) {
            accumMatrixRe[b_i] = centers[b_i];
          }

          nrows = centers.size(0) - 1;
          if (1 > centers.size(0) - 1) {
            nx = 0;
          } else {
            nx = centers.size(0) - 1;
          }

          b_accumMatrixRe.set_size(nx, 2);
          for (b_i = b_idx + 1; b_i <= nrows; b_i++) {
            accumMatrixRe[b_i - 1] = accumMatrixRe[b_i];
          }

          for (b_i = 0; b_i < nx; b_i++) {
            b_accumMatrixRe[b_i] = accumMatrixRe[b_i];
          }

          for (b_i = b_idx + 1; b_i <= nrows; b_i++) {
            accumMatrixRe[(b_i + accumMatrixRe.size(0)) - 1] = accumMatrixRe[b_i
              + accumMatrixRe.size(0)];
          }

          for (b_i = 0; b_i < nx; b_i++) {
            b_accumMatrixRe[b_i + b_accumMatrixRe.size(0)] = accumMatrixRe[b_i +
              accumMatrixRe.size(0)];
          }

          accumMatrixRe.set_size(b_accumMatrixRe.size(0), 2);
          nx = b_accumMatrixRe.size(0) * b_accumMatrixRe.size(1);
          for (b_i = 0; b_i < nx; b_i++) {
            accumMatrixRe[b_i] = b_accumMatrixRe[b_i];
          }

          centers.set_size(accumMatrixRe.size(0), 2);
          nx = accumMatrixRe.size(0) * accumMatrixRe.size(1);
          for (b_i = 0; b_i < nx; b_i++) {
            centers[b_i] = accumMatrixRe[b_i];
          }
        }
      }

      if (centers.size(0) != 0) {
        nx = centers.size(0);
        b_x.set_size(centers.size(0));
        for (i = 0; i < nx; i++) {
          b_x[i] = centers[i + centers.size(0)];
        }

        i = centers.size(0) - 1;
        for (k = 0; k <= i; k++) {
          b_x[k] = rt_roundd_snf(b_x[k]);
        }

        nx = centers.size(0);
        c_x.set_size(centers.size(0));
        for (i = 0; i < nx; i++) {
          c_x[i] = centers[i];
        }

        i = centers.size(0) - 1;
        for (k = 0; k <= i; k++) {
          c_x[k] = rt_roundd_snf(c_x[k]);
        }

        nx = b_x.size(0);
        for (i = 0; i < nx; i++) {
          b_x[i] = static_cast<int>(b_x[i]) + Hd.size(0) * (static_cast<int>
            (c_x[i]) - 1);
        }

        accumMatrixRe.set_size(b_x.size(0), 1);
        nx = b_x.size(0);
        for (i = 0; i < nx; i++) {
          accumMatrixRe[i] = Hd[static_cast<int>(b_x[i]) - 1];
        }

        b_sort(accumMatrixRe, iidx);
        metric.set_size(accumMatrixRe.size(0), 1);
        nx = accumMatrixRe.size(0) * accumMatrixRe.size(1);
        for (i = 0; i < nx; i++) {
          metric[i] = accumMatrixRe[i];
        }

        accumMatrixRe.set_size(iidx.size(0), 2);
        nx = iidx.size(0);
        for (i = 0; i < nx; i++) {
          accumMatrixRe[i] = centers[iidx[i] - 1];
        }

        for (i = 0; i < nx; i++) {
          accumMatrixRe[i + accumMatrixRe.size(0)] = centers[(iidx[i] +
            centers.size(0)) - 1];
        }

        centers.set_size(accumMatrixRe.size(0), accumMatrixRe.size(1));
        nx = accumMatrixRe.size(0) * accumMatrixRe.size(1);
        for (i = 0; i < nx; i++) {
          centers[i] = accumMatrixRe[i];
        }
      }
    }
  }
}

// End of code generation (chcenters.cpp)
