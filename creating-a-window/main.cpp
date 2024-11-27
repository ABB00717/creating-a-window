#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

void frameBufferSizeCallback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

int main() {
  // Init GLFW
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  // Create a window
  GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Learn OpenGL", nullptr, nullptr);
  if (window==nullptr) return -1;
  glfwMakeContextCurrent(window);

  // Init Glad
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) return false;

  glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT); // 設定視口大小
  glfwSetFramebufferSizeCallback(window, frameBufferSizeCallback); // 設定視窗大小改變時的callback
  while (!glfwWindowShouldClose(window)) {
    processInput(window); // 檢查是否按下ESC

    // 渲染指令
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f); // 設定清除顏色
    glClear(GL_COLOR_BUFFER_BIT); // 清除顏色緩衝

    glfwSwapBuffers(window); // 雙緩衝區交換
    glfwPollEvents(); // 檢查有沒有觸發事件
  }

  glfwTerminate();
  return 0;
}

void frameBufferSizeCallback(GLFWwindow* window, int width, int height) {
  glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE)==GLFW_PRESS) {
    glfwSetWindowShouldClose(window, true);
  }
}