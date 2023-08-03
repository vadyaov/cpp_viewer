#ifndef FILE_READER_H_
#define FILE_READER_H_

#include "facade.h"
#include <fstream>
#include <sstream>

namespace s21 {
  class FileReader {
    public:
      Scene ReadScene(const std::string& path) {
        std::ifstream file(path);

        std::vector<Vertex> vertices;
        std::vector<Edge> edges;

        std::vector<Figure> figures;
        /* std::vector<float> indices; */

        std::string line;
        while (std::getline(file, line)) {
          if (IsVertexLine(line)) {
            vertices.push_back(ReadVertex(std::string(line.begin() + 2, line.end())));
          }
          /* } else if (IsSurfaceLine(line)) { */
          /*   ReadSurface(line, indices); */
          /* } */

        /* Edges will be lines between two points in one surface. I think so */

        }

        figures.push_back(Figure(vertices, edges));
        return Scene(figures);
      }
    private:
      bool IsVertexLine(const std::string& line) {
        return (line.size() > 1 && line[0] == 'v' && line[1] == ' ');
      }

      Vertex ReadVertex(const std::string& line) {
        /* std::cout << line << std::endl; */
        std::istringstream iss(line);
        float x, y, z;
        if (!(iss >> x >> y >> z)) {
          throw std::invalid_argument("Incorrect vertex buffer in obj file");
        }

        return Vertex(x, y, z);
      }
  };
} // namespace s21

#endif  // FILE_READER_H_


