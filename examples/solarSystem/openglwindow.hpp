#ifndef OPENGLWINDOW_HPP_
#define OPENGLWINDOW_HPP_

#include <array>
#include <vector>

#include "abcg.hpp"
#include "camera.hpp"

struct Vertex {
  glm::vec3 position;

  bool operator==(const Vertex& other) const {
    return position == other.position;
  }
};

struct Planet {
  glm::vec3 planetScale;
  glm::vec4 planetColor;
};

class OpenGLWindow : public abcg::OpenGLWindow {
 protected:
  void handleEvent(SDL_Event& ev) override;
  void initializeGL() override;
  void paintGL() override;
  void paintUI() override;
  void resizeGL(int width, int height) override;
  void terminateGL() override;

 private:
  GLuint m_VAO{};
  GLuint m_VBO{};
  GLuint m_EBO{};
  GLuint m_program{};

  int m_viewportWidth{};
  int m_viewportHeight{};

  Camera m_camera;
  float m_dollySpeed{0.0f};
  float m_truckSpeed{0.0f};
  float m_panSpeed{0.0f};

  std::array<Planet, sizeof(Planet)> planets{};
  int planetIndex;
  int velocity = 5;

  std::vector<Vertex> m_vertices;
  std::vector<GLuint> m_indices;

  abcg::ElapsedTimer m_timer;

  void loadModelFromFile(std::string_view path);
  void update();
  std::array<Planet, sizeof(Planet)> initializePlanetAttrib();
};

#endif