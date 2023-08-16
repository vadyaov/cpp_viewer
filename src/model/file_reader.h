#ifndef FILE_READER_H_
#define FILE_READER_H_

#include <fstream>
#include <sstream>
/* #include <regex> */
#include <vector>
#include <iostream>

#include "vertex.h"

class FileReader {
  public:
    FileReader() = default;
    ~FileReader() = default;

    void LoadModel(const std::string& path) {
      std::ifstream file(path);
      
      if (!file) throw std::invalid_argument("Incorrect filename");

      std::string line;
      while (std::getline(file, line)) {
        if (IsVertexLine(line)) {
          vertex_buf_.push_back(ReadVertex(std::string(line.begin() + 2, line.end())));
        } else if (IsSurfaceLine(line)) {
          surface_buf_.push_back(ReadSurface(line));
       }
      }
    }

    std::vector<_3DVertex> GetVertexBuffer() {return (vertex_buf_);}
    std::vector<std::vector<int>> GetSurfaceBuffer() {return surface_buf_;}

    void print() {
      std::cout << "Inside Reader:\n\n";

      std::cout << "Vertex Buffer:\n";
      for (const auto& i : vertex_buf_) {
        std::cout << '(' << i.x_ << ", " << i.y_ << ", " << i.z_ << ")\n";
      }

      std::cout << "Surface Buffer:\n";
      for (const auto& i : surface_buf_) {
        for (const int j : i) 
          std::cout << j << ' ';
      std::cout << std::endl;
      }

    }

  private:
    std::vector<_3DVertex> vertex_buf_;
    std::vector<std::vector<int>> surface_buf_;


    bool IsVertexLine(const std::string& line) {
      return (line.size() > 1 && line[0] == 'v' && line[1] == ' ');
    }

    bool IsSurfaceLine(const std::string& line) {
      return (line.size() > 1 && line[0] == 'f' && line[1] == ' ');
    }

    _3DVertex ReadVertex(const std::string& line) {
      std::istringstream iss(line);
      float x, y, z;
      if (!(iss >> x >> y >> z))
        throw std::invalid_argument("Incorrect vertex buffer in obj file");

      return _3DVertex{x, y, z};
    }

    std::vector<int> ReadSurface(const std::string& line) {
      std::vector<int> idx;

      std::size_t i = 2;
      while (i < line.size()) {
        std::string index;

        if (line[i] == ' ') ++i;

        while (std::isdigit(static_cast<unsigned char>(line[i])))
          index += line[i++];

        idx.push_back(std::stoi(index));

        if (line[i] == '/')
          while (i < line.size() && line[i] != ' ') ++i;
      }

      return idx;
    }
};

#endif  // FILE_READER_H_
