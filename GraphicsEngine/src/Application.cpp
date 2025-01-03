#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "Renderer.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/quaternion.hpp"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include "scenes/QuaternionicBezierScene.h"
#include "scenes/DupinPatchScene.h"
#include <scenes/TubeTestScene.h>
#include <scenes/SphereTestScene.h>
#include <scenes/CyclidicCubeScene.h>
#include <scenes/PlaneTestScene.h>
#include <scenes/NewScene.h>

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(1080, 1080, "Graphics Engine", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    glfwSwapInterval(1);

    if (glewInit() != GLEW_OK)
        std::cout << "Error!" << std::endl;

    std::cout << glGetString(GL_VERSION) << std::endl;

    {
        GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
        GLCall(glEnable(GL_BLEND));

        geometry::MeshFactory meshFactory;
        NewScene scene;

        
        for (int i = 0; i < 15; i++)
        {
            for (int j = 0; j < 15; j++)
            {
                auto cubeMesh = meshFactory.CreateCubeMesh();
                SceneObject scnObj(std::move(cubeMesh), glm::vec3(i * 5 - 23, 0.0, j * 5 - 25));

                auto color = scnObj.GetMesh().GetUniforms().find("objectColor");

                color->second.value.vec3 = glm::vec3(0.55 + 0.02 * i, 0.55, 0.55 - 0.02 * j);

                scene.AddSceneObject(std::move(scnObj));
            }
        }

        //scenes::QuaternionicBezierScene scene;
        //scenes::DupinPatchScene scene;
        //scenes::CyclidicCubeScene scene;
        //scenes::SphereTestScene scene;
        //scenes::TubeTestScene scene;
        //scenes::PlaneTestScene scene;

        Renderer renderer;
        renderer.SetClearColor(glm::vec4(0.5f, 0.5f, 0.5f, 1.0f));

        ImGui::CreateContext();
        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init("#version 130");
        ImGui::StyleColorsDark();

        float cameraPosW = 0.25f;
        float cameraHeight = 2.5f;
        float cameraDist = 5.0f;

        while (!glfwWindowShouldClose(window))
        {
            renderer.Clear();

            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();

            glm::mat4 view = glm::lookAt(
                glm::vec3(
                    glm::cos(glm::radians(360.0f) * cameraPosW) * cameraDist,
                    cameraHeight,
                    glm::sin(glm::radians(360.0f) * cameraPosW) * cameraDist) /* + scene.sceneCenter*/,
                /*scene.sceneCenter*/ glm::vec3(0.0f, 0.0f, 0.0f),
                glm::vec3(0.0f, 1.0f, 0.0f)
                );

            scene.RenderScene(renderer, view);

            {
                ImGui::Begin("Camera Controls");
                ImGui::SliderFloat("Camera Position", &cameraPosW, 0.0f, 1.0f);
                ImGui::SliderFloat("Camera Height", &cameraHeight, -10.0f, 10.0f);
                ImGui::SliderFloat("Camera Distance", &cameraDist, 1.0f, 30.0f);
                ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
                ImGui::End();
            }

            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

            glEnd();

            /* Swap front and back buffers */
            glfwSwapBuffers(window);

            /* Poll for and process events */
            glfwPollEvents();
        }
    }
    glfwTerminate();
    return 0;
}