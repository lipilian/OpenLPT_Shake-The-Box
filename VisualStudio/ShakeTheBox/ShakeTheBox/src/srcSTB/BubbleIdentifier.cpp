//
//  Academic License - for use in teaching, academic research, and meeting
//  course requirements at degree granting institutions only.  Not for
//  government, commercial, or other organizational use.
//
//  BubbleIdentifier.cpp
//
//  Code generation for function 'BubbleIdentifier'
//


// Include files
#include "BubbleIdentifier.h"
#include "bwconncomp.h"
#include "regionprops.h"
#include <cstring>
#include <queue>
#include "Position.h"
#include "NumDataIO.h"

// Function Definitions
void BubbleIdentifier::BubbleCenterAndSize()
{
    coder::array<struct0_T, 1U> center_size;
    region_props(center_size); // get the center and size of all blobs.

    int n_center = *center_size.size();

    for (int i = 0; i < n_center; ++i) {
        double r = (center_size[i].MajorAxisLength + center_size[i].MinorAxisLength) / 4;
        double aspect_ratio = center_size[i].MajorAxisLength / center_size[i].MinorAxisLength;
        if (r > 3 && aspect_ratio < 1.5) { //assume bubble are perfect sphere 
            // correct the pixel number by shifting back by 2
            Position bubble(center_size[i].Centroid[0] - 2, center_size[i].Centroid[1] - 2, 0, r); //Position + radius
            center.push_back(bubble);
            radius.push_back(r);
        }
    }
}

void BubbleIdentifier::region_props(coder::array<struct0_T, 1U>& center_size) {
    double expl_temp;
    double CC_ImageSize[2];
    double CC_NumObjects;
    coder::array<double, 1U> CC_RegionIndices;
    coder::array<int, 1U> regionLengths;
    struct0_T b_s;
    int loop_ub;
    int i;
    struct_T statsAlreadyComputed;
    b_struct_T statsOneObj;
    coder::array<b_struct_T, 1U> stats;
    coder::array<int, 1U> idxCount;
    int k;
    bwconncomp(img, &expl_temp, CC_ImageSize, &CC_NumObjects, CC_RegionIndices,
        regionLengths);
    b_s.Centroid[0] = 0.0;
    b_s.Centroid[1] = 0.0;
    b_s.MajorAxisLength = 0.0;
    b_s.MinorAxisLength = 0.0;
    loop_ub = static_cast<int>(CC_NumObjects);
    center_size.set_size(loop_ub);
    for (i = 0; i < loop_ub; i++) {
        center_size[i] = b_s;
    }

    statsAlreadyComputed.Area = false;
    statsOneObj.Area = 0.0;
    statsAlreadyComputed.Centroid = false;
    statsOneObj.Centroid[0] = 0.0;
    statsOneObj.Centroid[1] = 0.0;
    statsAlreadyComputed.BoundingBox = false;
    statsOneObj.BoundingBox[0] = 0.0;
    statsOneObj.BoundingBox[1] = 0.0;
    statsOneObj.BoundingBox[2] = 0.0;
    statsOneObj.BoundingBox[3] = 0.0;
    statsAlreadyComputed.MajorAxisLength = false;
    statsOneObj.MajorAxisLength = 0.0;
    statsAlreadyComputed.MinorAxisLength = false;
    statsOneObj.MinorAxisLength = 0.0;
    statsAlreadyComputed.Eccentricity = false;
    statsOneObj.Eccentricity = 0.0;
    statsAlreadyComputed.Orientation = false;
    statsOneObj.Orientation = 0.0;
    statsAlreadyComputed.Image = false;
    statsOneObj.Image.set_size(0, 0);
    statsAlreadyComputed.FilledImage = false;
    statsOneObj.FilledImage.set_size(0, 0);
    statsAlreadyComputed.FilledArea = false;
    statsOneObj.FilledArea = 0.0;
    statsAlreadyComputed.EulerNumber = false;
    statsOneObj.EulerNumber = 0.0;
    statsAlreadyComputed.Extrema = false;
    std::memset(&statsOneObj.Extrema[0], 0, 16U * sizeof(double));
    statsAlreadyComputed.EquivDiameter = false;
    statsOneObj.EquivDiameter = 0.0;
    statsAlreadyComputed.Extent = false;
    statsOneObj.Extent = 0.0;
    statsOneObj.PixelIdxList.set_size(0);
    statsAlreadyComputed.PixelList = false;
    statsOneObj.PixelList.set_size(0, 2);
    statsAlreadyComputed.Perimeter = false;
    statsOneObj.Perimeter = 0.0;
    statsAlreadyComputed.Circularity = false;
    statsOneObj.Circularity = 0.0;
    statsAlreadyComputed.PixelValues = false;
    statsOneObj.PixelValues.set_size(0);
    statsAlreadyComputed.WeightedCentroid = false;
    statsAlreadyComputed.MeanIntensity = false;
    statsOneObj.MeanIntensity = 0.0;
    statsAlreadyComputed.MinIntensity = false;
    statsOneObj.MinIntensity = 0.0;
    statsAlreadyComputed.MaxIntensity = false;
    statsOneObj.MaxIntensity = 0.0;
    statsAlreadyComputed.SubarrayIdx = false;
    statsOneObj.SubarrayIdx.set_size(1, 0);
    statsOneObj.WeightedCentroid[0] = 0.0;
    statsOneObj.SubarrayIdxLengths[0] = 0.0;
    statsOneObj.WeightedCentroid[1] = 0.0;
    statsOneObj.SubarrayIdxLengths[1] = 0.0;
    stats.set_size(loop_ub);
    for (i = 0; i < loop_ub; i++) {
        stats[i] = statsOneObj;
    }

    statsAlreadyComputed.PixelIdxList = true;
    if (CC_NumObjects != 0.0) {
        int b_loop_ub;
        if ((regionLengths.size(0) != 1) && (regionLengths.size(0) != 0) &&
            (regionLengths.size(0) != 1)) {
            i = regionLengths.size(0);
            for (k = 0; k <= i - 2; k++) {
                regionLengths[k + 1] = regionLengths[k] + regionLengths[k + 1];
            }
        }

        idxCount.set_size((regionLengths.size(0) + 1));
        idxCount[0] = 0;
        b_loop_ub = regionLengths.size(0);
        for (i = 0; i < b_loop_ub; i++) {
            idxCount[i + 1] = regionLengths[i];
        }

        for (k = 0; k < loop_ub; k++) {
            int i1;
            i = idxCount[k + 1];
            if (idxCount[k] + 1 > i) {
                i1 = 0;
                i = 0;
            }
            else {
                i1 = idxCount[k];
            }

            b_loop_ub = i - i1;
            stats[k].PixelIdxList.set_size(b_loop_ub);
            for (i = 0; i < b_loop_ub; i++) {
                stats[k].PixelIdxList[i] = CC_RegionIndices[i1 + i];
            }
        }
    }

    ComputeCentroid(CC_ImageSize, stats, &statsAlreadyComputed);
    ComputeEllipseParams(CC_ImageSize, stats, &statsAlreadyComputed);
    ComputeEllipseParams(CC_ImageSize, stats, &statsAlreadyComputed);
    i = stats.size(0);
    //n_center = i;
    for (k = 0; k < i; k++) {
        center_size[k].Centroid[0] = stats[k].Centroid[0];
        center_size[k].Centroid[1] = stats[k].Centroid[1];
        center_size[k].MajorAxisLength = stats[k].MajorAxisLength;
        center_size[k].MinorAxisLength = stats[k].MinorAxisLength;
    }
}

Frame BubbleIdentifier::CreateFrame()
{
    //std::deque<Position> pos;
    //std::deque<double> r;
    //for (int i = 0; i < center.size(); ++ i) {
    //     pos.push_back(center[i]);
    //     r.push_back(radius[i]);
    //}
    return Frame(center);
}

void BubbleIdentifier::SaveCenter(string file_path) {
    NumDataIO<double> data_io;
    file_path.erase(file_path.end() - 3, file_path.end()); // erase "tif"
    data_io.SetFilePath(file_path + "txt");
    
    //	double particle_2Dcenter[x.size()][2];
    int n_center = center.size();
    double* particle_2Dcenter = new double[n_center * 2];
    //	for (int i = 0; i < x.size(); ++i)
    //		particle_2Dcenter[i] = new double[2];
    
    for (int i = 0; i < n_center; i ++) {
        particle_2Dcenter[2 * i] = center[i].X();
        particle_2Dcenter[2 * i + 1] = center[i].Y();
    }
    data_io.SetTotalNumber(n_center * 2);
    data_io.WriteData(particle_2Dcenter);

    delete[] particle_2Dcenter;
}

void BubbleIdentifier::SaveRadius(string file_path) {
    NumDataIO<double> data_io;
    file_path.erase(file_path.end() - 4, file_path.end()); // erase "tif"
    data_io.SetFilePath(file_path + "_r.txt");

    //	double particle_2Dcenter[x.size()][2];
    int n_center = radius.size();
    double* particle_2Dcenter = new double[n_center];
    //	for (int i = 0; i < x.size(); ++i)
    //		particle_2Dcenter[i] = new double[2];

    for (int i = 0; i < n_center; i++) {
        particle_2Dcenter[i] = radius[i];
    }
    data_io.SetTotalNumber(n_center);
    data_io.WriteData(particle_2Dcenter);

    delete[] particle_2Dcenter;
}

BubbleIdentifier::BubbleIdentifier(int**& p, int rows, int cols, int threshold) : img_p(p), rows(rows), cols(cols), threshold(threshold)
{

    img.set_size(rows, cols);

    // Loop over the array to initialize each element.
    for (int idx0 = 0; idx0 < img.size(0); idx0++) {
        for (int idx1 = 0; idx1 < img.size(1); idx1++) {
            // Set the value of the array element.
            // Change this value to the value that the application requires.
            if (img_p[idx0][idx1] > threshold)
                img[idx0 + img.size(0) * idx1] = true;
            else
                img[idx0 + img.size(0) * idx1] = false;
        }
    }
}

BubbleIdentifier::~BubbleIdentifier()
{
    // (no terminate code required)
}



// End of code generation (BubbleIdentifier.cpp)
