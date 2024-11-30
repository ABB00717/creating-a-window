#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
float vertices[] = {
    0.5f,  0.5f, 0.0f, // 右上角
    0.5f, -0.5f, 0.0f, // 右下角
   -0.5f, -0.5f, 0.0f, // 左下角

    0.5f,  0.5f, 0.0f, // 右上角
   -0.5f, -0.5f, 0.0f, // 左下角
   -0.5f,  0.5f, 0.0f  // 左上角
};
unsigned int indices[] = {
  0, 1, 3,
  1, 2, 3
};
const char* vertexShaderSource = 
"#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main() {\n"
"  gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";
const char* fragmentShaderSource =
"#version 330 core\n"
"out vec4 FragColor;\n"
"void main() {\n"
"  FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\0";

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

  // 編譯頂點著色器
  unsigned int vertexShader;
  vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
  glCompileShader(vertexShader);
  int success;
  char infoLog[512];
  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
    std::cout<<"ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"<<infoLog<<std::endl;
  }

  // 編譯片段著色器
  unsigned int fragmentShader;
  fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
  glCompileShader(fragmentShader);
  glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
    std::cout<<"ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n"<<infoLog<<std::endl;
  }

  // 連結頂點和片段著色器
  unsigned int shaderProgram;
  shaderProgram = glCreateProgram();
  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
  glLinkProgram(shaderProgram); // 把頂點和片段著色器連結成一個完整的程序
  glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
    std::cout<<"ERROR::SHADER::PROGRAM::LINK_FAILED\n"<<infoLog<<std::endl;
  }
  glUseProgram(shaderProgram); // 使用這個程序
  glDeleteShader(vertexShader); // 刪除已經連結到程序的頂點著色器
  glDeleteShader(fragmentShader); // 刪除已經連結到程序的片段著色器

  // 綁定 VBO, VAO, EBO
  unsigned int VBO, VAO, EBO;
  glGenVertexArrays(1, &VAO);
  glBindVertexArray(VAO);
  glGenBuffers(1, &VBO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  glGenBuffers(1, &EBO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

  // 告訴OpenGL如何解析頂點數據
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  // 解綁 VBO, VAO, EBO
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT); // 設定視口大小
  glfwSetFramebufferSizeCallback(window, frameBufferSizeCallback); // 設定視窗大小改變時的callback
  while (!glfwWindowShouldClose(window)) {
    processInput(window); // 檢查是否按下ESC

    // 渲染指令
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // 線框模式
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f); // 設定清除顏色
    glClear(GL_COLOR_BUFFER_BIT); // 清除顏色緩衝
    glUseProgram(shaderProgram);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);

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