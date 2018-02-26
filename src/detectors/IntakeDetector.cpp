#include "IntakeDetector.h"
void IntakeDetector::Init(){

}

void IntakeDetector::Process(cv::Mat* inputMat, cv::Mat* outputMat)
{
    cv::Mat temp;
    inputMat->copyTo(temp);
    cv::putText(temp,"Intake Detector", cv::Point(50,50),0,1.0,cv::Scalar(0,255,255));
    temp.copyTo(*outputMat);
    temp.release();
}

void IntakeDetector::Stop()
{

}