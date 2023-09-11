/**
 * @file facade.h
 * @author neelyarl heidedra
 * @brief Header file for the Facade class.
 * @version 0.1
 * @date 2023-09-08
 *
 * @copyright Copyright (c) 2023
 *
 */
#ifndef CPP4_3D_VIEWER_V_2_0_1_VIEW_FACADE_H
#define CPP4_3D_VIEWER_V_2_0_1_VIEW_FACADE_H
#include <GL/glew.h>

#include <chrono>
#include <fstream>
#include <thread>

#include "../controller/Controller.h"
#include "../model/Drawer.h"
#include "../model/Model.h"

namespace s21 {

class Settings;
/**
  @brief siplifies interraction with an app*/
class Facade {
 public:
  ~Facade();
  /**
                              @brief runs app*/
  void Run() const;
  /**
  @brief loads model from file*/
  void LoadModel(const std::string&) const;
  /**
     @brief draws model with selected settings*/
  void DrawModel(const Settings&) const;
  /**
      @brief draws settings window*/
  void SetingsWindow(Settings&) const;
  /**
      @brief makes a screenshoot*/
  void MakeScreenShot(bool, bool) const;
  /**
      @brief returns an instance of a class*/
  static Facade& GetInstance() {
    static Facade instance;
    return instance;
  }

 private:
  Facade();  // Singleton class
  GLFWwindow* window;
  Controller* ctr_;
  ModelDrawer* drawer_;
};

}  // namespace s21

#endif  // CPP3_3D_VIEWER_V_2_0_1_VIEW_FACADE_H
