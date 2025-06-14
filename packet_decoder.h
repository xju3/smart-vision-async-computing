// packet_decoder.h
#pragma once
#include <condition_variable>
#include <functional>
#include <mutex>
#include <opencv2/opencv.hpp>
#include <queue>
#include <thread>
#include <vector>

extern "C" {
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>
}

using DecoderCallback =
    std::function<void(std::vector<cv::Mat> &frames, int gopId, int disposedFrames)>;

class PacketDecoder {
public:
  PacketDecoder(std::string video_file_name, DecoderCallback callback);
  ~PacketDecoder();

  void decode(const std::vector<AVPacket *> &pkts, int interval, int gopId, int disposedFrames);
  void reset();

private:
  struct DecodeTask {
    std::vector<AVPacket *> pkts;
    int interval;
    int gopId;
    int total;
  };

  std::string video_file_name;
  int vidIdx;
  AVFormatContext *fmtCtx;
  AVCodec *codec;
  AVCodecParameters *codecpar;

  std::vector<std::thread> workers;
  std::queue<DecodeTask> taskQueue;
  std::mutex queueMutex;
  std::condition_variable queueCond;
  bool stopThreads;
  DecoderCallback callback;

  void workerLoop();
  AVCodecContext *cloneDecoderContext();
  void decodeTask(DecodeTask task, AVCodecContext *ctx);

  bool initialize();
};