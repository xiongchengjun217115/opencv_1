#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>
int main()
{
    // 创建
    cv::Mat img = cv::imread("./docs/naiwa1.png");
    cv::Mat gray_img;
    cv::Mat hsv_img;
    cv::Mat edges;
    cv::Mat mask;
    std::vector<std::vector<cv::Point>> contours;

    if (img.empty())
    {
        std::cout << "Failed to load image" << std::endl;
        return -1;
    }

    // 创建视频
    cv::VideoCapture cap("./docs/homework.mp4");
    if (!cap.isOpened())
    {
        std::cout << "Failed to open video" << std::endl;
        return -1;
    }

    // 转化
    while (cap.read(img))
    {
        // cv::cvtColor(img, gray_img, cv::COLOR_BGR2GRAY);
        cv::cvtColor(img, hsv_img, cv::COLOR_BGR2HSV);
        cv::inRange(
            hsv_img,
            cv::Scalar(0, 25, 25),
            cv::Scalar(45, 255, 255),
            mask);
        // cv::bitwise_not(mask, mask);
        // cv::Mat kernel = cv::getStructuringElement(
        //     cv::MORPH_RECT, cv::Size(5, 5));
        // cv::erode(mask, mask, kernel);
        // cv::Mat kernel = cv::getStructuringElement(
        //     cv::MORPH_ELLIPSE, cv::Size(3, 3));
        // cv::morphologyEx(mask, mask, cv::MORPH_CLOSE, kernel);

        // 调参
        //   int hmin = 0, smin = 0, vmin = 0;
        //   int hmax = 179, smax = 255, vmax = 255;
        //   cv::namedWindow("Trackbars", cv::WINDOW_NORMAL);
        //   cv::resizeWindow("Trackbars", 960, 640);
        //   cv::createTrackbar("hmin", "Trackbars", &hmin, 179);
        //   cv::createTrackbar("smin", "Trackbars", &smin, 255);
        //   cv::createTrackbar("vmin", "Trackbars", &vmin, 255);
        //   cv::createTrackbar("hmax", "Trackbars", &hmax, 179);
        //   cv::createTrackbar("smax", "Trackbars", &smax, 255);
        //   cv::createTrackbar("vmax", "Trackbars", &vmax, 255);
        //   while(true) {
        //   cv::Scalar lower(hmin, smin, vmin);
        //   cv::Scalar upper(hmax, smax, vmax);
        //   cv::inRange(hsv_img, lower, upper, mask);
        //   cv::imshow("Trackbars", mask);
        //   if (cv::waitKey(30) == 'q') break;
        //   }

        // 轮廓
        cv::findContours(
            mask,
            contours,
            cv::RETR_EXTERNAL,
            cv::CHAIN_APPROX_SIMPLE);

        for (int i = 0; i < contours.size(); i++)
        {
            if (cv::contourArea(contours[i]) > 100000)
            {
                cv::Rect rect = cv::boundingRect(contours[i]);
                cv::Rect feet(
                    rect.x,
                    rect.y + rect.height * 0.85,
                    rect.width,
                    rect.height * 0.15);
                cv::Mat v;
                cv::extractChannel(hsv_img, v, 2);
                cv::Mat feet_v = v(feet);
                cv::Mat gradient;
                cv::Sobel(feet_v, gradient, CV_32F, 0, 1, 3);
                cv::Mat gradient_show;
                cv::convertScaleAbs(gradient, gradient_show);
                // cv::imshow("Gradient", gradient_show);
                cv::Mat negative_gradient;
                cv::inRange(
                    gradient,
                    cv::Scalar(-10000),
                    cv::Scalar(-50),
                    negative_gradient);
                cv::Mat kernel = cv::getStructuringElement(
                    cv::MORPH_RECT, cv::Size(3, 1));
                cv::morphologyEx(
                    negative_gradient,
                    negative_gradient,
                    cv::MORPH_OPEN,
                    kernel);
                int best_y = -1;
                int max_count = 0;

                for (int y = 0; y < negative_gradient.rows; y++)
                {
                    int count = cv::countNonZero(negative_gradient.row(y));

                    if (count > max_count)
                    {
                        max_count = count;
                        best_y = y;
                    }
                }
                if (best_y >= 0 && max_count > 20)
                {
                    int cut_y = feet.y + best_y;

                    cv::Rect shadow(
                        rect.x,
                        cut_y,
                        rect.width,
                        rect.y + rect.height - cut_y);

                    mask(shadow).setTo(0);
                }
            }
            cv::findContours(
                    mask,
                    contours,
                    cv::RETR_EXTERNAL,
                    cv::CHAIN_APPROX_SIMPLE);
                //cv::imshow("Negative Gradient", negative_gradient);
                cv::rectangle(img, feet, cv::Scalar(0, 255, 0), 2);
                cv::drawContours(
                    img,
                    contours,
                    i,
                    cv::Scalar(0, 0, 255),
                    2);
        }

        // 显示
        // cv::namedWindow("Image1", cv::WINDOW_NORMAL);
        // cv::namedWindow("Image2", cv::WINDOW_NORMAL);
        // std::cout << img.at<cv::Vec3b>(75, 138) << std::endl;
        // cv::imshow("Image1", hsv_img);
        // cv::imshow("Image2", mask);
        // cv::imshow("Contour", img);
        // cv::waitKey(0);

        // 显示视频
        cv::imshow("Video", img);
        if (cv::waitKey(30) == 'q')
            break;
    }
    cap.release();
    cv::destroyWindow("Video");
    return 0;
}
