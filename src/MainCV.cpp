#include <iostream>
#include <signal.h>
#include "TCPClient.h"
#include <thread>
#include "opencv2/opencv.hpp"
TCPClient tcp;

void sig_exit(int s)
{
    tcp.exit();
    exit(0);
}
void tcp_client_loop()
{
    cout << "Starting Client Loop" << endl;
    while (1)
    {

        string rec = tcp.receive();
        if (rec != "")
        {
            cout << "Server Response:" << rec << endl;
            tcp.Send("0 0 heartbeat no_data");
        }
        sleep(0.1);
    }
}
int main(int argc, char *argv[])
{
    signal(SIGINT, sig_exit);

    tcp.setup("pi3-01.local", 9000);
    tcp.Send("0 0 id victory_cv");
    cout << "TCP Start" << endl;
    std::thread tcpTread(tcp_client_loop);

    cv::VideoCapture cap;
    // open the default camera, use something different from 0 otherwise;
    // Check VideoCapture documentation.
    cv::Mat source;
    cv::Mat output;
    cv::Mat channels[3];
    std::vector<std::vector<cv::Point>> contours;
    std::vector<cv::Vec4i> hierarchy;
    if (!cap.open(0))
        return 0;
    for (;;)
    {

        cap >> source;
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

        tcp.Send("0 0 cv " + to_string(pos));

        if (source.empty())
            break; // end of video stream
        cv::imshow("this is you, smile! :)", source);
        cv::imshow("mask", output);
        if (cv::waitKey(10) == 27)
            break; // stop capturing by pressing ESC
    }

    return 0;
}