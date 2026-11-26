#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>
// void connectEdges(cv::Mat& mask, int maxDist)
// {
//     std::vector<cv::Point> points;
//     std::vector<cv::Point> directions;

//     // 寻找端点
//     for (int y = 1; y < mask.rows - 1; y++)
//     {
//         for (int x = 1; x < mask.cols - 1; x++)
//         {
//             if (mask.at<uchar>(y, x) == 0)
//                 continue;

//             int count = 0;
//             cv::Point direction;

//             for (int dy = -1; dy <= 1; dy++)
//             {
//                 for (int dx = -1; dx <= 1; dx++)
//                 {
//                     if (dx == 0 && dy == 0)
//                         continue;

//                     if (mask.at<uchar>(y + dy, x + dx) > 0)
//                     {
//                         count++;
//                         direction = cv::Point(-dx, -dy);
//                     }
//                 }
//             }

//             if (count == 1)
//             {
//                 points.push_back(cv::Point(x, y));
//                 directions.push_back(direction);
//             }
//         }
//     }

//     // 寻找距离最近、方向合适的端点
//     std::vector<bool> used(points.size(), false);

//     for (int i = 0; i < points.size(); i++)
//     {
//         if (used[i])
//             continue;

//         int best = -1;
//         double minDist = maxDist;

//         for (int j = i + 1; j < points.size(); j++)
//         {
//             if (used[j])
//                 continue;

//             cv::Point d = points[j] - points[i];

//             // 判断两个端点是否相向
//             if (d.dot(directions[i]) <= 0 ||
//                 d.dot(directions[j]) >= 0)
//                 continue;

//             double dist = cv::norm(d);

//             if (dist < minDist)
//             {
//                 minDist = dist;
//                 best = j;
//             }
//         }

//         // 自动连线
//         if (best != -1)
//         {
//             cv::line(mask, points[i], points[best],
//                      cv::Scalar(255), 1);

//             used[i] = true;
//             used[best] = true;
//         }
//     }
// }

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

        // connectEdges(mask, 40);

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
        cv::drawContours(
            img,
            contours,
            -1,
            cv::Scalar(0, 0, 255),
            2);

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
        if (cv::waitKey(1) == 'q')
            break;
    }
    cap.release();
    cv::destroyWindow("Video");
    return 0;
}
