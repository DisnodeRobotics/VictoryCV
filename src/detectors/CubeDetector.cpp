#include "CubeDetector.h"
void CubeDetector::Init()
{
}

void CubeDetector::Process(cv::Mat *inputMat, cv::Mat *outputMat)
{
    cv::Mat temp;
    cv::Mat output;
    cv::Mat channels[3];
    std::vector<std::vector<cv::Point>> contours;
    std::vector<cv::Vec4i> hierarchy;


    inputMat->copyTo(temp);
    cv::putText(temp, "Cube Detector", cv::Point(50, 50), 0, 1.0, cv::Scalar(0, 255, 255));

    

    cvtColor(temp, output, cv::COLOR_BGR2YUV);
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
    cv::rectangle(temp, chosenRect.tl(), chosenRect.br(), color, 2, 4, 0);

    temp.copyTo(*outputMat);
    temp.release();
    output.release();
}

void CubeDetector::Stop()
{
}