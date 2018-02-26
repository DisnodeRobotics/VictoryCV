#pragma once
#include "opencv2/opencv.hpp"
#include "../DetectorBase.h"
class SwitchDetector : public DetectorBase
{
    public:
        virtual void Init();
        virtual void Process(cv::Mat* inputMat, cv::Mat* outputMat);
        virtual void Stop();

};