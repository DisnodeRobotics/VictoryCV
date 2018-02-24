#include <iostream>
#include <signal.h>
#include "victoryconnect/VictoryConnectClient.h"
#include <thread>
#include "opencv2/opencv.hpp"
#include "InputDevice.h"
#include "detectors/CubeDetector.h"
#include "detectors/IntakeDetector.h"
#include "detectors/ScaleDetector.h"
#include "detectors/SwitchDetector.h"
VictoryConnectClient *vcClient;

int main(int argc, char *argv[])
{   


    InputDevice device0;
    device0.Init(0);
    device0.Enable();

    std::shared_ptr<CubeDetector> cubeDector;
    cubeDector.reset(new CubeDetector());
    cubeDector->Init();

    std::shared_ptr<IntakeDetector> intakeDector;
    intakeDector.reset(new IntakeDetector());
    intakeDector->Init();

    std::shared_ptr<ScaleDetector> scaleDector;
    scaleDector.reset(new ScaleDetector());
    scaleDector->Init();

    std::shared_ptr<SwitchDetector> switchDector;
    switchDector.reset(new SwitchDetector());
    switchDector->Init();


    std::vector<std::shared_ptr<DetectorBase>> detectors;

    detectors.push_back(std::move(cubeDector));
    detectors.push_back(std::move(intakeDector));
    detectors.push_back(std::move(scaleDector));
    detectors.push_back(std::move(switchDector));


    int index = 0;

    while(true){
        std::cout<<"Main Thread Running"<<std::endl;
        

        device0.SetDetector(detectors[index]);
        index++;
        if(index >= detectors.size()){
            index = 0;
        }
         std::this_thread::sleep_for( std::chrono::seconds(1) );
    }
    /*
    vcClient = new VictoryConnectClient();
    vcClient->Connect("127.0.0.1");
    //cout<<"Starting CV" << endl;
    while(true){}
    cv::VideoCapture cap1;
    cv::VideoCapture cap2;
    cv::VideoCapture cap3;

    cap1.set(CV_CAP_PROP_FRAME_WIDTH , 352);
    cap1.set(CV_CAP_PROP_FRAME_HEIGHT , 288);
    cap2.set(CV_CAP_PROP_FRAME_WIDTH , 352);
    cap2.set(CV_CAP_PROP_FRAME_HEIGHT , 288);
    cap3.set(CV_CAP_PROP_FRAME_WIDTH , 352);
    cap3.set(CV_CAP_PROP_FRAME_HEIGHT , 288);

    // open the default camera, use something different from 0 otherwise;
    // Check VideoCapture documentation.
    cv::Mat source;
    cv::Mat output;
    cv::Mat channels[3];
    std::vector<std::vector<cv::Point>> contours;
    std::vector<cv::Vec4i> hierarchy;
    if (!cap1.open(0))
        return 0;
    if (!cap1.open(2))
        return 0;
    if (!cap1.open(3))
        return 0;
    for (;;)
    {
        cv::Mat source1;
        cv::Mat source2;
        cv::Mat source3;
        
        cap1 >> source1;
        cap2 >> source2;
        cap3 >> source3;


        cv::hconcat(source1,source2,output);
    

        cvtColor(source, output, cv::COLOR_BGR2YUV);
        cv::blur(output, output, cv::Size(20, 20));

        cv::split(output, channels);

        cv::threshold(channels[1], output, 100, 255, cv::THRESH_BINARY_INV);

        int morph_elem = 0;
        int morph_size = 0;
        int morph_operator = 0;
        int const max_operator = 4;
        int const max_elem = 2;
        int const max_kernel_size = 21;
        int operation = morph_operator + 2;

        cv::Mat element = cv::getStructuringElement(morph_elem, cv::Size(2 * morph_size + 1, 2 * morph_size + 1), cv::Point(morph_size, morph_size));

        /// Apply the specified morphology operation
        morphologyEx(output, output, operation, element);

        cv::findContours(output, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE);

        /// Approximate contours to polygons + get bounding rects and circles
        std::vector<std::vector<cv::Point>> contours_poly(contours.size());
        std::vector<cv::Rect> boundRect(contours.size());
        std::vector<cv::Point2f> center(contours.size());
        std::vector<float> radius(contours.size());

        cv::Rect chosenRect;
        float chosenArea = 0;
        /// Draw polygonal contour + bonding rects + circles
        for (int i = 0; i < contours.size(); i++)
        {
            approxPolyDP(cv::Mat(contours[i]), contours_poly[i], 3, true);
            boundRect[i] = cv::boundingRect(cv::Mat(contours_poly[i]));

            float area = boundRect[i].area();

            if (std::abs(1 - boundRect[i].width / boundRect[i].height) < 1)
            {
                if (area > chosenArea)
                {
                    chosenRect = boundRect[i];
                }
            }
            else
            {
                //std::cout << "Bad Ratio" << std::endl;
            }
        }
        cv::Scalar color = cv::Scalar(0, 255, 255);
        cv::rectangle(source, chosenRect.tl(), chosenRect.br(), color, 2, 4, 0);

        double pos = chosenRect.x + chosenRect.width;

        vcClient->SendPacket(0,"cv",to_string(pos));

        if (source.empty())
            break; // end of video stream
        cv::imshow("this is you, smile! :)", source);
        cv::imshow("mask", output);
        if (cv::waitKey(10) == 27)
            break; // stop capturing by pressing ESC
    }
    */
    return 0;
}