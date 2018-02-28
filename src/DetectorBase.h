#pragma once
#include "opencv2/opencv.hpp"
#include "victoryconnect/VictoryConnectClient.h"
class DetectorBase
{
    public:
        struct CubeDetectorResult{
            int id;
            double score;
            cv::Mat objectMat;
            cv::Rect objectRect;
        };

        virtual void Init(VictoryConnectClient* vcClient){}
        virtual void Process(cv::Mat* inputMat, cv::Mat* outputMat){}
        virtual void NetSetting(std::string key, std::string val){}
        virtual void Stop(){}

};