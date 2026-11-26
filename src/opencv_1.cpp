#include <opencv2/opencv.hpp>
#include <iostream>

int main() {
cv::Mat img = cv::imread("./docs/naiwa1.png");
cv::Mat gray_img;
cv::Mat hsv_img;
cv::Mat edges;
cv::Mat mask;

if (img.empty()) {
std::cout << "Failed to load image" << std::endl;
return -1;
}

cv::cvtColor(img, gray_img,cv::COLOR_BGR2GRAY);
cv::cvtColor(img, hsv_img, cv::COLOR_BGR2HSV);
cv::inRange(
    hsv_img,
    cv::Scalar(0, 0, 180),
    cv::Scalar(255, 255, 220),
    mask
);

cv::namedWindow("Image", cv::WINDOW_NORMAL);
std::cout<<img.at<cv::Vec3b>(75,138)<<std::endl;
//cv::imshow("Image", hsv_img);
cv::imshow("Image", mask);
cv::waitKey(0);
return 0;
}
