#include "InputDevice.h"

bool InputDevice::Init(int deviceID){
    vidCap.reset(new cv::VideoCapture(0));
}