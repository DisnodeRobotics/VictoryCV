#pragma once
#include "opencv2/opencv.hpp"
#include "DetectorBase.h"
#include <memory>
class InputDevice
{
    private:
        std::unique_ptr<cv::VideoCapture> vidCap;
        std::shared_ptr<cv::Mat> lastMat;
        double FPS;
        std::shared_ptr<DetectorBase> currentDetector;

        void frame_cap();

    public:
        bool Init(int deviceId);
        void Enable();
        void SetDetector(std::shared_ptr<DetectorBase> detector);
        void Disable();

        cv::Mat* getLastMat();

};