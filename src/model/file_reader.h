#ifndef FILE_READER_H_
#define FILE_READER_H_

#include <fstream>
#include <vector>

#include "vertex.h"

class FileReader {
  public:
    FileReader() = default;
    ~FileReader() = default;

    explicit FileReader(const std::string&);

    std::vector<_3DVertex> GetVertexBuffer();

    std::vector<std::vector<int>> GetSurfaceBuffer();

  private:
    std::ifstream file_;
    std::streampos pos_;
};

#endif  // FILE_READER_H_
