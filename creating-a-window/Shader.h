#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>; // 包含glad來獲取所有的必須OpenGL標頭檔

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>


class Shader {
public:
  // 程序ID
  unsigned int ID;

  // 構造器讀取並建構著色器
  Shader(const char* vertexPath, const char* fragmentPath);
  // 使用/啟動程序
  void use();
  // uniform工具函數
  void setBool(const std::string& name, bool value) const;
  void setInt(const std::string& name, int value) const;
  void setFloat(const std::string& name, float value) const;
private:
  // 檢查編譯/連結過程中是否出錯
  void checkCompileErrors(unsigned int shader, std::string type);
};

#endif