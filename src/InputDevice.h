#pragma once
#include "opencv2/opencv.hpp"
#include "DetectorBase.h"
#include <memory>
#include <thread>
class InputDevice
{
    private:
        cv::VideoCapture vidCap;
        std::shared_ptr<cv::Mat> lastMat;
        double FPS;
        std::shared_ptr<DetectorBase> currentDetector;

        void frame_cap();

        std::thread frameThread;

    public:
        void InputDevive();
        bool Init(int deviceId);
        void Enable();
        void SetDetector(std::shared_ptr<DetectorBase> detector);
        void Disable();

        std::shared_ptr<cv::Mat> getLastMat();

};