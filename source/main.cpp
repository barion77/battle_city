#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "renderer/shader_program.h"
#include "resources/resources_manager.h"

GLfloat points[] = {
    -0.5f, -0.5f, 0.0f,
    0.5f, -0.5f, 0.0f,
    0.0f, 0.5f, 0.0f,
};

GLfloat colors[] = {
    1.0f, 0.5f, 0.5f,
    0.5f, 1.0f, 0.5f,
    0.5f, 0.5f, 1.0f,
};

int window_sizeX = 640;
int window_sizeY = 480;

void glfw_window_increasing_size(GLFWwindow* window, int width, int height)
{
    window_sizeX = width;
    window_sizeY = height;
    glViewport(0, 0, window_sizeX, window_sizeY);
}

void glfw_key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GL_TRUE); 
    }
}

int main(int argc, char** argv)
{
    /* Initialize the library */
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    GLFWwindow* window = glfwCreateWindow(window_sizeX, window_sizeY, "Battle city", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwSetWindowSizeCallback(window, glfw_window_increasing_size);
    glfwSetKeyCallback(window, glfw_key_callback);

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
	
	if (!gladLoadGL())
	{
		std::cout << "Can't load library GLAD" << std::endl;
		return -1;
	}
	
    std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;
    std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;
	
	glClearColor(0, 1, 0.5, 1);

    {
        ResourceManager recource_manager(argv[0]);
        auto pdefault_shader_program = recource_manager.load_shader("Default_Shader", "/res/shaders/vertex.txt", "/res/shaders/fragment.txt");
        if (!pdefault_shader_program)
        {
            std::cerr << "Can't create shader program: " << "Default_Shader" << std::endl;
            return -1;
        }

        GLuint points_vbo = 0;
        glGenBuffers(1, &points_vbo);
        glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);

        GLuint colors_vbo = 0;
        glGenBuffers(1, &colors_vbo);
        glBindBuffer(GL_ARRAY_BUFFER, colors_vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);

        GLuint vao = 0;
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);

        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, colors_vbo);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {
            /* Render here */
            glClear(GL_COLOR_BUFFER_BIT);

            pdefault_shader_program->use();
            glBindVertexArray(vao);
            glDrawArrays(GL_TRIANGLES, 0, 3);

            /* Swap front and back buffers */
            glfwSwapBuffers(window);

            /* Poll for and process events */
            glfwPollEvents();
        }
    }

    glfwTerminate();
    return 0;
}