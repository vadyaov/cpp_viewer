/**
 * @file file_reader.h
 * @author neelyarl heidedra
 * @brief Header file for the FileReader class.
 * @version 0.1
 * @date 2023-09-08
 *
 * @copyright Copyright (c) 2023
 *
 */
#ifndef CPP4_3D_VIEWER_V_2_0_1_FILE_READER_H
#define CPP4_3D_VIEWER_V_2_0_1_FILE_READER_H

#include <fstream>
#include <sstream>
#include <vector>

#include "Model.h"

namespace s21 {
/**
  @brief class for reading object files*/
class FileReader {
 public:
  FileReader() = default;
  ~FileReader() { file_.close(); };
  /**
      @brief reads and parses file*/
  explicit FileReader(const std::string&);
  /**
      @brief vertex getter*/
  std::vector<Vertex3D> GetVertexBuffer();
  /**
      @brief surface getter*/
  std::vector<std::vector<int>> GetSurfaceBuffer();

 private:
  std::ifstream file_;
  std::streampos pos_;
};

}  // namespace s21

#endif  // CPP4_3D_VIEWER_V_2_0_1_FILE_READER_H
