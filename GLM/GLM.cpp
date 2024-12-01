// GLM.cpp : This file contains the 'main' function. Program execution begins and ends there.
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

int main() {
  glm::vec4 vec(1.0f, 0.0f, 0.0f, 1.0f);
  glm::mat4 trans = glm::mat4(1.0f); // 初始化為單位矩陣
  trans = glm::translate(trans, glm::vec3(1.0f, 1.0f, 0.0f)); // 位移
  vec = trans*vec;
  std::cout<<vec.x<<vec.y<<vec.z<<std::endl;
}