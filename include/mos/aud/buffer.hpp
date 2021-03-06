#pragma once

#include <atomic>
#include <string>
#include <memory>
#include <vector>

namespace mos {
namespace aud {

class Buffer;
using SharedBuffer = std::shared_ptr<Buffer>;

/** 16bit integer audio buffer. */
class Buffer final {
public:
  using Samples = std::vector<short>;

  template<class T>
  /** Construct buffer from a container of shorts. */
  Buffer(const T begin, const T end, const int channels = 1,
              const unsigned int sample_rate = 44100u)
      : channels_(channels), sample_rate_(sample_rate),
        samples_(begin, end), id_(current_id_++) {}

  /** Empty buffer constructor. */
  explicit Buffer(const int channels = 1);

  /** Construct from *.ogg file. */
  explicit Buffer(const std::string &path);

  ~Buffer() = default;

  /** Load shared buffer. */
  static SharedBuffer load(const std::string &path);

  Samples::const_iterator begin() const;

  Samples::const_iterator end() const;

  /** Raw data. */
  const short *data() const;

  /** Unique id. */
  unsigned int id() const;

  /** Get number of channels. */
  int channels() const;

  /** Get sample rate */
  int sample_rate() const;

  /** Duration in seconds. */
  float duration() const;

  /** Size of samples container. */
  size_t size() const;

private:
  static std::atomic_uint current_id_;
  unsigned int id_;
  Samples samples_;
  int channels_;
  int sample_rate_;
};
}
}