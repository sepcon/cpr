#ifndef STREAM_H
#define STREAM_H

#include <ostream>

namespace cpr {
namespace details {

  template <class Stream>
  struct StreamRefBase {
      using StreamType = Stream;
      StreamRefBase(Stream& stream) : stream_{&stream} {}
      StreamRefBase(){}
      bool IsNull() const { return !stream_; }
      StreamType* stream_ = nullptr;
  };

  struct DownloadStream : public StreamRefBase<std::ostream> {
    using StreamRefBase<std::ostream>::StreamRefBase;
  };
  struct UploadStream : public StreamRefBase<std::istream> {
      using StreamRefBase<std::istream>::StreamRefBase;
  };

}

// Alias for stream types
using details::DownloadStream;
using details::UploadStream;
using ResponseDataStream = DownloadStream;

}
#endif // STREAM_H
