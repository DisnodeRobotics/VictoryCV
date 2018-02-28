#pragma once
#include "opencv2/opencv.hpp"
#include "../DetectorBase.h"
#include <algorithm>    // std::max

class CubeDetector : public DetectorBase
{   
    private: 
        cv::Size working_frame_size;
        double min_score = 50;
        double area_weight = 0.5;
        double area_max   = 0.75;
        double area_min   = 0.05;

        double ratio_weight = 0.7;
        double ratio_max_dif = 1;
        double ratio_perfered = 1;

        double calculate_score(cv::Rect inputRect);
    public:
        virtual void Init(VictoryConnectClient* vcClient);
        virtual void Process(cv::Mat* inputMat, cv::Mat* outputMat);
        virtual void Stop();

};