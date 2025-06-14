// inference_input.hpp
#pragma once
#include <opencv2/opencv.hpp>
#include <string>
#include <vector>

struct InferenceInput {
  std::vector<cv::Mat> decoded_frames;
  int gopIdx;
  int latest_frame_index;
};

// 推理结果结构
struct InferenceResult {
  std::string info;
  int type = 10; // 0: detection, 1: classification, etc.
  int taskId;
  int frameIndex;
  int seconds;
  std::string image;
  float confidence;
};

// 解码过程信息
struct TaskDecodeInfo {
  int taskId; 
  int type = 20;
  int total;
};

// 推理过程信息
struct TaskInferInfo {
  int taskId;
  int type = 30;
  int completed;
  int remain;
};
