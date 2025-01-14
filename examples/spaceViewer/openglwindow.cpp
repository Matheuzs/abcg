#include "openglwindow.hpp"

#include <fmt/core.h>
#include <imgui.h>

#include <cppitertools/itertools.hpp>
#include <glm/gtc/matrix_inverse.hpp>


void OpenGLWindow::handleEvent(SDL_Event& event) {
  glm::ivec2 mousePosition;
  SDL_GetMouseState(&mousePosition.x, &mousePosition.y);

  if (event.type == SDL_MOUSEMOTION) {
    m_trackBallModel.mouseMove(mousePosition);
    m_trackBallLight.mouseMove(mousePosition);
  }
  if (event.type == SDL_MOUSEBUTTONDOWN) {
    if (event.button.button == SDL_BUTTON_LEFT) {
      m_trackBallModel.mousePress(mousePosition);
    }
    if (event.button.button == SDL_BUTTON_RIGHT) {
      m_trackBallLight.mousePress(mousePosition);
    }
  }
  if (event.type == SDL_MOUSEBUTTONUP) {
    if (event.button.button == SDL_BUTTON_LEFT) {
      m_trackBallModel.mouseRelease(mousePosition);
    }
    if (event.button.button == SDL_BUTTON_RIGHT) {
      m_trackBallLight.mouseRelease(mousePosition);
    }
  }

  if (event.type == SDL_MOUSEWHEEL) {
    m_zoom += (event.wheel.y > 0 ? 1.0f : -1.0f) / 5.0f;
  }
}

void OpenGLWindow::initializeGL() {
  glClearColor(0, 0, 0, 1);
  glEnable(GL_DEPTH_TEST);

  // Create programs
  for (const auto& name : m_constants.m_shaderNames) {
    auto path{getAssetsPath() + "shaders/" + name};
    auto program{createProgramFromFile(path + ".vert", path + ".frag")};
    m_programs.push_back(program);
  }

  // Initial Planet (Earth)
  // m_planetIndex = 3;
  // // Initial Default Earth
  // m_earthIndex = 0;
  // Load default model
  loadModel(getAssetsPath() + "Planet.obj");

  // Load cubemap
  m_model.loadCubeTexture(getAssetsPath() + "maps/cube/");

  // Sets the angle and velocity of rotation
  m_trackBallModel.setAxis(glm::normalize(glm::vec3(-0.1, 1, 0.05)));
  m_trackBallModel.setVelocity(0.0001f);

  initializeSkybox();
}

void OpenGLWindow::initializeSkybox() {
  // Create skybox program
  auto path{getAssetsPath() + "shaders/" + m_skyShaderName};
  m_skyProgram = createProgramFromFile(path + ".vert", path + ".frag");

  // Generate VBO
  glGenBuffers(1, &m_skyVBO);
  glBindBuffer(GL_ARRAY_BUFFER, m_skyVBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(m_skyPositions), m_skyPositions.data(),
               GL_STATIC_DRAW);
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  // Get location of attributes in the program
  GLint positionAttribute{glGetAttribLocation(m_skyProgram, "inPosition")};

  // Create VAO
  glGenVertexArrays(1, &m_skyVAO);

  // Bind vertex attributes to current VAO
  glBindVertexArray(m_skyVAO);

  glBindBuffer(GL_ARRAY_BUFFER, m_skyVBO);
  glEnableVertexAttribArray(positionAttribute);
  glVertexAttribPointer(positionAttribute, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  // End of binding to current VAO
  glBindVertexArray(0);
}

void OpenGLWindow::loadModel(std::string_view path) {
  std::string viewType = getPlanetTexture(m_planetIndex);
  std::string earthTexture = getEarthTexture(m_earthIndex);

  // Load Diffuse and Complementary Textures, else load Earth Textures
  if (m_planetIndex != 3) {
    loadPlanetsTextures();
  } else {
    loadEarthTextures();
  }

  m_model.loadFromFile(path);
  m_model.setupVAO(m_programs.at(m_currentProgramIndex));

  m_trianglesToDraw = m_model.getNumTriangles();

  // Use material properties from the loaded model
  m_Ka = m_model.getKa();
  m_Kd = m_model.getKd();
  m_Ks = m_model.getKs();
  m_shininess = m_model.getShininess();
}

void OpenGLWindow::paintGL() {
  update();

  // Compute time elapsed to use on Clouds velocity
  float timer = m_timer.elapsed();

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glViewport(0, 0, m_viewportWidth, m_viewportHeight);

  // Use currently selected program
  m_currentProgramIndex = 0;

  const auto program{m_programs.at(m_currentProgramIndex)};
  glUseProgram(program);

  // Get location of uniform variables
  GLint viewMatrixLoc{glGetUniformLocation(program, "viewMatrix")};
  GLint projMatrixLoc{glGetUniformLocation(program, "projMatrix")};
  GLint modelMatrixLoc{glGetUniformLocation(program, "modelMatrix")};
  GLint normalMatrixLoc{glGetUniformLocation(program, "normalMatrix")};
  GLint lightDirLoc{glGetUniformLocation(program, "lightDirWorldSpace")};
  GLint shininessLoc{glGetUniformLocation(program, "shininess")};
  GLint IaLoc{glGetUniformLocation(program, "Ia")};
  GLint IdLoc{glGetUniformLocation(program, "Id")};
  GLint IsLoc{glGetUniformLocation(program, "Is")};
  GLint KaLoc{glGetUniformLocation(program, "Ka")};
  GLint KdLoc{glGetUniformLocation(program, "Kd")};
  GLint KsLoc{glGetUniformLocation(program, "Ks")};
  GLint diffuseTexLoc{glGetUniformLocation(program, "diffuseTex")};
  GLint complementaryTexLoc{glGetUniformLocation(program, "complementaryTex")};
  GLint normalTexLoc{glGetUniformLocation(program, "normalTex")};
  GLint cubeTexLoc{glGetUniformLocation(program, "cubeTex")};
  GLint texMatrixLoc{glGetUniformLocation(program, "texMatrix")};
  GLint timeLoc{glGetUniformLocation(program, "timer")};

  // Set uniform variables used by every scene object
  glUniformMatrix4fv(viewMatrixLoc, 1, GL_FALSE, &m_viewMatrix[0][0]);
  glUniformMatrix4fv(projMatrixLoc, 1, GL_FALSE, &m_projMatrix[0][0]);
  glUniform1i(diffuseTexLoc, 0);
  glUniform1i(normalTexLoc, 1);
  glUniform1i(cubeTexLoc, 2);
  glUniform1i(complementaryTexLoc, 3);
  glUniform1f(timeLoc, timer);

  glm::mat3 texMatrix{m_trackBallLight.getRotation()};
  glUniformMatrix3fv(texMatrixLoc, 1, GL_TRUE, &texMatrix[0][0]);

  auto lightDirRotated{m_trackBallLight.getRotation() * m_lightDir};
  glUniform4fv(lightDirLoc, 1, &lightDirRotated.x);
  glUniform4fv(IaLoc, 1, &m_Ia.x);
  glUniform4fv(IdLoc, 1, &m_Id.x);
  glUniform4fv(IsLoc, 1, &m_Is.x);

  // Set uniform variables of the current object
  glUniformMatrix4fv(modelMatrixLoc, 1, GL_FALSE, &m_modelMatrix[0][0]);

  auto modelViewMatrix{glm::mat3(m_viewMatrix * m_modelMatrix)};
  glm::mat3 normalMatrix{glm::inverseTranspose(modelViewMatrix)};
  glUniformMatrix3fv(normalMatrixLoc, 1, GL_FALSE, &normalMatrix[0][0]);

  glUniform1f(shininessLoc, m_shininess);
  glUniform4fv(KaLoc, 1, &m_Ka.x);
  glUniform4fv(KdLoc, 1, &m_Kd.x);
  glUniform4fv(KsLoc, 1, &m_Ks.x);

  m_model.render(m_trianglesToDraw);

  renderSkybox();
}

void OpenGLWindow::renderSkybox() {
  glUseProgram(m_skyProgram);

  // Get location of uniform variables
  GLint viewMatrixLoc{glGetUniformLocation(m_skyProgram, "viewMatrix")};
  GLint projMatrixLoc{glGetUniformLocation(m_skyProgram, "projMatrix")};
  GLint skyTexLoc{glGetUniformLocation(m_skyProgram, "skyTex")};

  // Set uniform variables
  auto viewMatrix{m_trackBallLight.getRotation()};
  glUniformMatrix4fv(viewMatrixLoc, 1, GL_FALSE, &viewMatrix[0][0]);
  glUniformMatrix4fv(projMatrixLoc, 1, GL_FALSE, &m_projMatrix[0][0]);
  glUniform1i(skyTexLoc, 0);

  glBindVertexArray(m_skyVAO);

  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_CUBE_MAP, m_model.getCubeTexture());

  glEnable(GL_CULL_FACE);
  glFrontFace(GL_CW);
  glDepthFunc(GL_LEQUAL);
  glDrawArrays(GL_TRIANGLES, 0, m_skyPositions.size());
  glDepthFunc(GL_LESS);

  glBindVertexArray(0);
  glUseProgram(0);
}

std::string OpenGLWindow::getPlanetTexture(int index) {
  std::string file;
  return m_constants.m_planetNames.at(index);
}

std::string OpenGLWindow::getEarthTexture(int index) {
  std::string file;
  return m_constants.m_earthTextures.at(index);
}

void OpenGLWindow::loadPlanetsTextures() {
    m_model.loadDiffuseTexture(getAssetsPath() + "maps/textures/" + getPlanetTexture(m_planetIndex) + ".png");
    m_model.loadComplementaryTexture(getAssetsPath() + "maps/textures/None.png");
    m_model.loadNormalTexture(getAssetsPath() + "maps/normals/CleanNormalMap.png");
}

void OpenGLWindow::loadEarthTextures() {
    m_model.loadDiffuseTexture(getAssetsPath() + "maps/textures/" + getEarthTexture(m_earthIndex) + ".png");
    m_model.loadComplementaryTexture(getAssetsPath() + "maps/textures/Clouds.png");
    m_model.loadNormalTexture(getAssetsPath() + "maps/normals/" + getPlanetTexture(m_planetIndex) + "NormalMap.png");
}

void OpenGLWindow::paintUI() {
  abcg::OpenGLWindow::paintUI();

  // Widgets Windows
  {
    static std::size_t currentIndex{3};
    static std::size_t currentIndexEarth{0};
    ImVec2 widgetSize{};

    if(currentIndex == 3) {
      widgetSize = {ImVec2(210, 85)};
    } else {
      widgetSize = {ImVec2(210, 65)};
    }

    ImGui::SetNextWindowPos(ImVec2(m_viewportWidth - widgetSize.x - 5, 5));
    ImGui::SetNextWindowSize(widgetSize);
    auto flags{ImGuiWindowFlags_NoDecoration};
    ImGui::Begin("Planetas", nullptr, flags);

    glFrontFace(GL_CCW);
    auto aspect{static_cast<float>(m_viewportWidth) /
                static_cast<float>(m_viewportHeight)};
    m_projMatrix = glm::perspective(glm::radians(45.0f), aspect, 0.1f, 10.0f);

    // Planets and Earth textures ComboBox

    {
      ImGui::PushItemWidth(120);
      // Planets Options ComboBox 
      if (ImGui::BeginCombo("Planetas", m_constants.m_planetNames.at(currentIndex))) {
        for (auto index : iter::range(m_constants.m_planetNames.size())) {
          const bool isSelected{currentIndex == index};
          if (ImGui::Selectable(m_constants.m_planetNames.at(index), isSelected))
            currentIndex = index;
          if (isSelected) ImGui::SetItemDefaultFocus();
        }
        ImGui::EndCombo();
      }
      // ImGui::PopItemWidth();

      // Earth Variants Textures ComboBox 
      if (!strcmp(m_constants.m_planetNames.at(currentIndex), "Terra")) {

        // ImGui::PushItemWidth(120);
        if (ImGui::BeginCombo("Variantes", m_constants.m_earthTextures.at(currentIndexEarth))) {
          for (auto index : iter::range(m_constants.m_earthTextures.size())) {
            const bool isSelected{currentIndexEarth == index};
            if (ImGui::Selectable(m_constants.m_earthTextures.at(index), isSelected))
              currentIndexEarth = index;
            if (isSelected) ImGui::SetItemDefaultFocus();
          }
          ImGui::EndCombo();
        }
        ImGui::PopItemWidth();
      }

      // Set up VAO if shader program has changed
      if (static_cast<int>(currentIndex) != m_planetIndex || static_cast<int>(currentIndexEarth) != m_earthIndex) {
        m_planetIndex = currentIndex;
        m_earthIndex = currentIndexEarth;
        if (currentIndex != 3) {
          loadPlanetsTextures();
        }
        else {
          loadEarthTextures();
        }
      }

      HelpMarker(m_constants.lbMarkInfo, m_constants.descMarkPlanets[currentIndex]);

      ImGui::End();
    }

    // Light Direction Sliders, Except Sun
    if(strcmp(m_constants.m_planetNames.at(currentIndex), "Sol")) {
      auto widgetSize2{ImVec2(220, 85)};
      auto flags2{ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar};

      ImGui::SetNextWindowPos(ImVec2(5, 5));
      ImGui::SetNextWindowSize(widgetSize2);
      ImGui::Begin("Light Direction", nullptr, flags2);

      ImGui::PushItemWidth(50);
      ImGui::DragFloat("X", &m_lightDir.x, 0.01f, -1.0f, 1.0f, "%.2f");
      ImGui::SameLine();
      ImGui::DragFloat("Y", &m_lightDir.y, 0.01f, -1.0f, 1.0f, "%.2f");
      ImGui::SameLine();
      ImGui::DragFloat("Z", &m_lightDir.z, 0.01f, -1.0f, 1.0f, "%.2f");

      ImGui::DragFloat("Alpha", &m_lightDir.a, 0.01f, -1.0f, 1.0f, "%.2f");
      ImGui::PopItemWidth();

      ImGui::SameLine(0, 40);
      HelpMarker(m_constants.lbMarkLight, m_constants.descMarkLight);

      ImGui::End();
    } else {
        m_lightDir = m_constants.sunLightDir;
    }
  }
}

void OpenGLWindow::resizeGL(int width, int height) {
  m_viewportWidth = width;
  m_viewportHeight = height;

  m_trackBallModel.resizeViewport(width, height);
  m_trackBallLight.resizeViewport(width, height);
}

void OpenGLWindow::terminateGL() {
  for (const auto& program : m_programs) {
    glDeleteProgram(program);
  }
}

void OpenGLWindow::terminateSkybox() {
  glDeleteProgram(m_skyProgram);
  glDeleteBuffers(1, &m_skyVBO);
  glDeleteVertexArrays(1, &m_skyVAO);
}

void OpenGLWindow::update() {
  m_modelMatrix = m_trackBallModel.getRotation();

  m_viewMatrix =
      glm::lookAt(glm::vec3(0.0f, 0.0f, 2.0f + m_zoom),
                  glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
}

void OpenGLWindow::HelpMarker(const char* label, const char* desc) {
    ImGui::TextColored(m_constants.yellow, "%s", label);
    if (ImGui::IsItemHovered())
    {
        ImGui::BeginTooltip();
        ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
        ImGui::TextUnformatted(desc);
        ImGui::PopTextWrapPos();
        ImGui::EndTooltip();
    }
}
