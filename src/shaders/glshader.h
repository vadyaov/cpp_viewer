/**
 * @file glshader.h
 * @author neelyarl heidedra
 * @brief Header file for the Shader class.
 * @version 0.1
 * @date 2023-09-08
 *
 * @copyright Copyright (c) 2023
 *
 */
#ifndef CPP4_3D_VIEWER_V_2_0_1_SHADERS_GLSHADER_H
#define CPP4_3D_VIEWER_V_2_0_1_SHADERS_GLSHADER_H

#include <GL/glew.h>

#include <fstream>
#include <glm/glm.hpp>
#include <iostream>
#include <sstream>
#include <vector>

namespace s21 {
/**
 @brief responsible for drawing shaders*/
class Shader {
 public:
  unsigned int ID;
  /**
    @brief constructor generates the shader on the fly*/
  // ------------------------------------------------------------------------
  Shader(const char *vertexPath, const char *fragmentPath) {
    glewExperimental = true;
    if (glewInit() != GLEW_OK) {
      throw std::runtime_error("Failed to initialize GLEW");
    }

    // 1. retrieve the vertex/fragment source code from filePath
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;
    /**
      @brief ensure ifstream objects can throw exceptions:*/
    vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    /**
      @brief ensure ifstream objects can throw exceptions:*/
    fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try {
      /**
          @brief open files*/
      vShaderFile.open(vertexPath);
      /**
        @brief open files*/
      fShaderFile.open(fragmentPath);
      std::stringstream vShaderStream, fShaderStream;
      /**
        @brief read file's buffer contents into streams*/
      vShaderStream << vShaderFile.rdbuf();
      /**
        @brief read file's buffer contents into streams*/
      fShaderStream << fShaderFile.rdbuf();
      /**
                         @brief close file handlers*/
      vShaderFile.close();
      /**
                         @brief close file handlers*/
      fShaderFile.close();
      /**
            @brief convert stream into string*/
      vertexCode = vShaderStream.str();
      /**
        @brief convert stream into string*/
      fragmentCode = fShaderStream.str();
    } catch (std::ifstream::failure &e) {
      std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ: " << e.what()
                << std::endl;
      throw;
    }
    const char *vShaderCode = vertexCode.c_str();
    const char *fShaderCode = fragmentCode.c_str();
    unsigned int vertex, fragment;
    vertex = glCreateShader(GL_VERTEX_SHADER); /**
      @brief vertex shader*/
    glShaderSource(vertex, 1, &vShaderCode, NULL);
    glCompileShader(vertex);
    CheckCompileErrors(vertex, "VERTEX");
    fragment = glCreateShader(GL_FRAGMENT_SHADER); /**
      @brief fragment Shader*/
    glShaderSource(fragment, 1, &fShaderCode, NULL);
    glCompileShader(fragment);
    CheckCompileErrors(fragment, "FRAGMENT");
    ID = glCreateProgram(); /**
      @brief shader Program*/
    glAttachShader(ID, vertex);
    glAttachShader(ID, fragment);
    glLinkProgram(ID);
    CheckCompileErrors(ID, "PROGRAM");
    glDeleteShader(vertex);   /**
        @brief delete the shaders as they're linked into our program
        *now and no longer necessary*/
    glDeleteShader(fragment); /**
      @brief delete the shaders as they're linked into our program
      *now and no longer necessary*/
  }
  // ------------------------------------------------------------------------
  /**
  @brief activate the shader*/
  void Use() { glUseProgram(ID); }
  // ------------------------------------------------------------------------
  void SetFloat(const std::string &name, float value) const {
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
  }
  // ------------------------------------------------------------------------
  void SetVec4(const std::string &name, const glm::vec4 &value) const {
    glUniform4fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
  }
  // ------------------------------------------------------------------------
  void SetMat4(const std::string &name, const glm::mat4 &mat) const {
    glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE,
                       &mat[0][0]);
  }

 private:
  // ------------------------------------------------------------------------
  /**
  @brief utility function for checking shader compilation/linking errors.*/
  void CheckCompileErrors(unsigned int shader, const std::string &type) {
    int success;
    char infoLog[1024];
    if (type != "PROGRAM") {
      glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
      if (!success) {
        glGetShaderInfoLog(shader, 1024, NULL, infoLog);
        std::cout
            << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n"
            << infoLog
            << "\n -- --------------------------------------------------- -- "
            << std::endl;
      }
    } else {
      glGetProgramiv(shader, GL_LINK_STATUS, &success);
      if (!success) {
        glGetProgramInfoLog(shader, 1024, NULL, infoLog);
        std::cout
            << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n"
            << infoLog
            << "\n -- --------------------------------------------------- -- "
            << std::endl;
      }
    }
  }
};
}  // namespace s21

#endif  // CPP4_3D_VIEWER_V_2_0_1_SHADERS_GLSHADER_H
