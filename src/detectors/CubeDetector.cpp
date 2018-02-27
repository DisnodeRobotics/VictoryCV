#include "CubeDetector.h"
void CubeDetector::Init()
{
}

void CubeDetector::Process(cv::Mat *inputMat, cv::Mat *outputMat)
{

    cv::Mat displayMat;
    cv::Mat mask;
    cv::Mat workingMat;
    cv::Mat channels[3];
    std::vector<std::vector<cv::Point>> contours;
    std::vector<cv::Vec4i> hierarchy;

    inputMat->copyTo(displayMat);
    cv::putText(displayMat, "Cube Detector", cv::Point(50, 50), 0, 1.0, cv::Scalar(0, 255, 255));

    cvtColor(displayMat, workingMat, cv::COLOR_BGR2YUV);
    working_frame_size = workingMat.size();
    cv::blur(workingMat, workingMat, cv::Size(20, 20));

    cv::split(workingMat, channels);

    cv::threshold(channels[1], mask, 110, 255, cv::THRESH_BINARY_INV);

    int morph_elem = 0;
    int morph_size = 0;
    int morph_operator = 0;
    int const max_operator = 4;
    int const max_elem = 2;
    int const max_kernel_size = 21;
    int operation = morph_operator + 2;

    cv::Mat element = cv::getStructuringElement(morph_elem, cv::Size(2 * morph_size + 1, 2 * morph_size + 1), cv::Point(morph_size, morph_size));

    /// Apply the specified morphology operation
    morphologyEx(mask, mask, operation, element);

    cv::findContours(mask, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE);

    /// Approximate contours to polygons + get bounding rects and circles
    std::vector<std::vector<cv::Point>> contours_poly(contours.size());
    std::vector<cv::Rect> boundRect(contours.size());
    std::vector<cv::Point2f> center(contours.size());
    std::vector<float> radius(contours.size());

    cv::Rect chosenRect;
    double chosenScore = 0;
    /// Draw polygonal contour + bonding rects + circles
    for (int i = 0; i < contours.size(); i++)
    {
        approxPolyDP(cv::Mat(contours[i]), contours_poly[i], 3, true);
        boundRect[i] = cv::boundingRect(cv::Mat(contours_poly[i]));

        float area = boundRect[i].area();
        double score = calculate_score(boundRect[i]);
        if (score > min_score &&  area > chosenScore)
        {
            chosenRect = boundRect[i];
            chosenScore = score;
        }
    }
    cv::Scalar color = cv::Scalar(0, 255, 255);
    cv::putText(displayMat, "Score: " + std::to_string(chosenScore), chosenRect.tl(),0,0.7,cv::Scalar(0,255,0),1);
    cv::rectangle(displayMat, chosenRect.tl(), chosenRect.br(), color, 2, 4, 0);
    displayMat.copyTo(*outputMat);
    displayMat.release();
    mask.release();
    workingMat.release();
}

void CubeDetector::Stop()
{
}
// PRIVATE
double CubeDetector::calculate_score(cv::Rect inputRect)
{
    double m_score = 0;

    //Ratio Scoring
    double m_ratio_wh = (double)inputRect.width / (double)inputRect.height;
    double m_ratio_hw = (double)inputRect.height / (double)inputRect.width;

    double m_ratio = std::max(m_ratio_wh, m_ratio_hw);
    double m_ratio_diff = std::abs(ratio_perfered - m_ratio);
    if (m_ratio_diff > ratio_max_dif)
    {
        return 0;
    }

    double m_ratio_score = 100 - ((100 * m_ratio_diff) * ratio_weight);
    //std::cout << "Ration: " << m_ratio << std::endl;
    //std::cout << "Ratio Score: " << m_ratio_score << std::endl;
    // Ratio: 1.4
    // Error: 0.4
    // Score = 60

    //Area Scoring
    double m_area = inputRect.area();
    double m_screen_area = working_frame_size.area();
    double m_area_perc = m_area / m_screen_area;
    if(m_area_perc > area_max || m_area_perc < area_min){return 0;}
    double m_area_normalized = (m_area_perc - area_min) / (area_max - area_min);
    double m_area_dif = std::abs(area_max-m_area_normalized) * 100 * area_weight;
    double m_area_score = 100 - m_area_dif;

    std::cout << "Area Score: " << m_area_score << std::endl;
    std::cout << "Ratio Score: " << m_ratio_score << std::endl;
    m_score = (m_area_score + m_ratio_score) / 2;
    return m_score;
}