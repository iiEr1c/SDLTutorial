#pragma once

#include <cstdint>

namespace HF {
/**
 * 维护两个状态, 开始&暂停
 * 本质就是在start()调用后, 记录暂停/非暂停的事件间隔
 * 初始状态: 0, 0 false, false
 * 暂停时: 已开始 & 已暂停, [开始, 暂停]的duration <- m_pausedTicks
 * 取消暂停: 已开始 & 不暂停, [上次暂停, 当前时刻]的duration, <- m_startTicks
 */
class FakerTimer {
  uint64_t m_startTicks = 0;
  uint64_t m_pausedTicks = 0;
  bool m_isPaused = false;
  bool m_isStarted = false;

public:
  FakerTimer();
  ~FakerTimer();

  FakerTimer(const FakerTimer &) = delete;
  FakerTimer &operator=(const FakerTimer &) = delete;

  FakerTimer(FakerTimer &&) noexcept;
  FakerTimer &operator=(FakerTimer &&) noexcept;

  /* 记录开始时刻的timepoint */
  void start();
  /* 清除所有的记录, 更新为暂停状态 */
  void stop();
  /* 距离上次start过去了多少ticks */
  void pause();
  /* 距离上一次暂停过去了多少ticks */
  void unpause();

  /* 根据状态返回ticks */
  uint64_t getTicks() const;

  bool isStarted() const;
  bool isPaused() const;
};
}; // namespace HF