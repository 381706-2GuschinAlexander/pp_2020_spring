// Copyright 2020 Guschin Alexander
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <vector>
#include "../../../modules/task_1/guschin_a_cc_labeling/cc_labeling.h"

std::vector<std::vector<std::int8_t>> Convert(const cv::Mat& image) {
  std::vector<std::vector<std::int8_t>> result_matrix(
      image.rows, std::vector<std::int8_t>(image.cols, 0));
  for (int i = 0; i < image.rows; ++i)
    for (int j = 0; j < image.cols; ++j) {
      cv::Vec3b iter_color = image.at<cv::Vec3b>(i, j);
      if (iter_color[0] == 0 && iter_color[1] == 0 && iter_color[2] == 0)
        result_matrix[i][j] = 1;
    }

  return result_matrix;
}

void Show(const std::vector<std::vector<std::int32_t>>& v_image) {
  cv::Mat image = cv::Mat::zeros(v_image.size(), v_image[0].size(), CV_8UC3);
  for (int i = 0; i < v_image.size(); ++i)
    for (int j = 0; j < v_image[0].size(); ++j) {
      cv::Vec3b iter_color;
      int color = v_image[i][j] * 100;
      iter_color[0] = (color / 10) % 256;
      iter_color[1] = (color / 20) % 256;
      iter_color[2] = (color / 50) % 256;
      image.at<cv::Vec3b>(i, j) = iter_color;
    }

  imshow("Display Window", image);
}

int main() {
  cv::Mat image = cv::Mat::zeros(300, 600, CV_8UC3);
  circle(image, cv::Point(250, 150), 100, cv::Scalar(0, 255, 128), -100);
  circle(image, cv::Point(350, 150), 100, cv::Scalar(255, 255, 255), -100);
  imshow("Display Window", image);
  cv::waitKey(0);
  return 0;
}