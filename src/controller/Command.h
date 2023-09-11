/**
 * @file Command.h
 * @author neelyarl heidedra
 * @brief Header file for the Command class.
 * @version 0.1
 * @date 2023-09-08
 *
 * @copyright Copyright (c) 2023
 *
 */
#ifndef CPP4_3DVIEWER_V_2_0_1_CONTROLLER_COMMAND_H
#define CPP4_3DVIEWER_V_2_0_1_CONTROLLER_COMMAND_H

namespace s21 {
/**
  @brief defines trasnformation type for command*/
enum CommandType { Rotation, Move, Scale };
/**
  @brief defines axis trasformation should applied to*/
enum CommandAxis { x, y, z };
/**
  @brief defines parameteres that should be passed to command*/
struct CommandParameters {
  CommandType type;
  CommandAxis axis;
  double value;
};
/**
  @brief class is required to siplify sending information from view to model via
  *controller*/

class Command {
 public:
  Command() {
    parameters.type = Rotation;
    parameters.axis = x;
    parameters.value = 0;
  };
  ~Command(){};
  /**
     @brief updates parameters of passed command*/
  void UpdateParameters(const CommandParameters& new_parameters) {
    parameters = new_parameters;
  };
  /**
  @brief command parameters getter*/
  const CommandParameters GetParameters() const noexcept { return parameters; }

 private:
  CommandParameters parameters;
};
}  // namespace s21

#endif  // CPP4_3DVIEWER_V_2_0_1_CONTROLLER_COMMAND_H
