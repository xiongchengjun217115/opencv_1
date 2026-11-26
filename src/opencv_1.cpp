#include <opencv2/opencv.hpp>

int main() {
cv::Mat img = cv::imread("./docs/naiwa1.png");
if (img.empty()) {
std::cout << "Failed to load image" << std::endl;
return -1;
}
cv::namedWindow("Image", cv::WINDOW_NORMAL);
std::cout<<img.at<cv::Vec3b>(75,138)<<std::endl;
cv::imshow("Image", img);
cv::waitKey(0);
return 0;
}