/**
 * @file Controller.h
 * @author neelyarl heidedra
 * @brief Header file for the Controller class.
 * @version 0.1
 * @date 2023-09-08
 *
 * @copyright Copyright (c) 2023
 *
 */
#ifndef CPP4_3D_VIEWER_V_2_0_1_CONTROLLER_CONTROLLER_H
#define CPP4_3D_VIEWER_V_2_0_1_CONTROLLER_CONTROLLER_H

#include <vector>

#include "../model/Aphine.h"
#include "../model/Model.h"
#include "./../model/Vertex3D.h"
#include "Command.h"

namespace s21 {
/**
  @brief transfers data from view to model*/
class Controller {
 public:
  ~Controller() = default;
  /**
      @brief adds available model to app*/
  void AddModel(const std::string& path);
  /**
    @brief gets new parameters for command*/
  void UpdateCommand(const CommandParameters& pars) {
    command.UpdateParameters(pars);
  };
  /**
    @brief sends command to current model*/
  void SendCommand(int model_index) {
    models[model_index].ApplyAphine(command);
  };
  /**
      @brief returns amount of loaded models*/
  std::size_t HowMany() const noexcept;
  /**
    @brief returns amount of vertexes in model*/
  std::size_t VertexNum(int n) const noexcept;
  /**
    @brief returns amount of surfaces in model*/
  std::size_t SurfaceNum(int n) const noexcept;
  /**
                     @brief checks if there any loaded models*/
  bool Empty() const noexcept;
  /**
          @brief gets verticies form model*/
  const Vertex3D& GetVertices(int) const;
  /**
    @brief gets verticies size form model*/
  std::size_t GetVertexSize(int counter) const;
  /**
          @brief gets lines form model*/
  const Vertex3D& GetLines(int) const;
  /**
        @brief gets lines size form model*/
  std::size_t GetLinesSize(int counter) const;
  /**
       @brief gets surfaces form model*/
  const Vertex3D& GetTriangles(int) const;
  /**
    @brief gets surfaces size form model*/
  std::size_t GetTrianglesSize(int counter) const;
  /**
      @brief returns instance of a class*/
  static Controller* GetInstance() {
    if (!instance) instance = new Controller();
    return instance;
  }

 private:
  static Controller* instance;
  Controller() = default;
  std::vector<Model> models;
  Command command;
};

}  // namespace s21

#endif  // CPP4_3D_VIEWER_V_2_0_1_CONTROLLER_CONTROLLER_H
