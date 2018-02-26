#include "InputDevice.h"
void InputDevice::InputDevive()
{
   
}
bool InputDevice::Init(int deviceID)
{
     frameThread = std::thread(&InputDevice::frame_cap, this);
    if (!vidCap.open(deviceID))
        return false;
}

void InputDevice::Enable()
{

    //frameThread.join();
}

void InputDevice::SetDetector(std::shared_ptr<DetectorBase> detector)
{
    currentDetector = detector;
}

void InputDevice::Disable() {}

std::shared_ptr<cv::Mat> InputDevice::getLastMat() { return lastMat; }

// PRIVATE
void InputDevice::frame_cap()
{
    std::cout<<"STarting capture trhead"<<std::endl;
    cv::Mat source;
    while (true)
    {
        if (vidCap.isOpened())
        {
           
            //vidCap.grab();
            vidCap >> source;

            if(currentDetector != nullptr){
                currentDetector->Process(&source, &source);
            }


            cv::imshow("Input Device", source);
        }else{
            //std::cout<<"Not Opened"<<std::endl;
        }
      
         if(cv::waitKey(30) >= 0) break;
    }
}