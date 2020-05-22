// Copyright 2020 Guschin Alexander
// Std lab
#include <chrono>
#include <iostream>
#include <vector>
#include "../../task_4/guschin_a_cc_labeling/cc_labeling.h"
#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/opencv.hpp"

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
  for (std::int32_t i = 0; i < v_image.size(); ++i)
    for (std::int32_t j = 0; j < v_image[0].size(); ++j) {
      cv::Vec3b iter_color;
      if (v_image[i][j] == 0) {
        iter_color[0] = 255;
        iter_color[1] = 255;
        iter_color[2] = 255;
      } else {
        std::int32_t color = v_image[i][j];
        iter_color[0] = (v_image[i][j] * 7) % 255;
        //(v_image[i][j] * v_image[i][j] * v_image[i][j]) % 256;
        iter_color[1] = (v_image[i][j] * 29) % 255;
        //(v_image[i][j] * v_image[i][j]) % 256;
        iter_color[2] = (v_image[i][j] * 53) % 255;
        //(v_image[i][j]) % 256;
      }
      image.at<cv::Vec3b>(i, j) = iter_color;
    }

  imshow("Display Window", image);
  cv::waitKey(0);
}

std::int32_t main() {
  std::string source = "C:\\Users\\igush\\Desktop\\Paint\\test.bmp";
  cv::Mat Image = cv::imread(source, 1);
  std::vector<std::vector<std::int8_t>> bin_matrix = Convert(Image);

  auto start = omp_get_wtime();
  std::vector<std::vector<std::int32_t>> result = Labeling_std(bin_matrix);
  auto end = omp_get_wtime();

  std::cout << "required time: " << (end - start);

  Show(result);
  return 0;
}