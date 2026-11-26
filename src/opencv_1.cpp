#include <opencv2/opencv.hpp>
#include <iostream>

int main()
{
    cv::Mat img = cv::imread("./docs/naiwa1.png");
    cv::Mat gray_img;
    cv::Mat hsv_img;
    cv::Mat edges;
    cv::Mat mask;

    if (img.empty())
    {
        std::cout << "Failed to load image" << std::endl;
        return -1;
    }

    cv::cvtColor(img, gray_img, cv::COLOR_BGR2GRAY);
    cv::cvtColor(img, hsv_img, cv::COLOR_BGR2HSV);
    cv::inRange(
        hsv_img,
        cv::Scalar(91, 0, 141),
        cv::Scalar(137, 194, 255),
        mask);
    cv::bitwise_not(mask, mask);

    // int hmin = 0, smin = 0, vmin = 0;
    // int hmax = 179, smax = 255, vmax = 255;
    // cv::namedWindow("Trackbars", cv::WINDOW_NORMAL);
    // cv::resizeWindow("Trackbars", 960, 640);
    // cv::createTrackbar("hmin", "Trackbars", &hmin, 179);
    // cv::createTrackbar("smin", "Trackbars", &smin, 255);
    // cv::createTrackbar("vmin", "Trackbars", &vmin, 255);
    // cv::createTrackbar("hmax", "Trackbars", &hmax, 179);
    // cv::createTrackbar("smax", "Trackbars", &smax, 255);
    // cv::createTrackbar("vmax", "Trackbars", &vmax, 255);
    // while(true) {
    // cv::Scalar lower(hmin, smin, vmin);
    // cv::Scalar upper(hmax, smax, vmax);
    // cv::inRange(hsv_img, lower, upper, mask);
    // cv::imshow("Image3", mask);
    // if (cv::waitKey(30) == 'q') break;
    // }

    cv::namedWindow("Image1", cv::WINDOW_NORMAL);
    cv::namedWindow("Image2", cv::WINDOW_NORMAL);
    std::cout << img.at<cv::Vec3b>(75, 138) << std::endl;
    // cv::imshow("Image1", hsv_img);
    cv::imshow("Image2", mask);
    cv::waitKey(0);
    return 0;
}
