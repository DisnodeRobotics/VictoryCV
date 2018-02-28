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

    //InputDevice device1;
    //device0.Init(1);
    //device0.Enable();

   // InputDevice device2;
    ///device0.Init(3);
    //device0.Enable();

    std::shared_ptr<CubeDetector> cubeDector;
    cubeDector.reset(new CubeDetector());
    cubeDector->Init(vcClient);

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
        //index++;
        if(index >= detectors.size()){
            index = 0;
        }
         std::this_thread::sleep_for( std::chrono::seconds(3) );
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
    */
    return 0;
}