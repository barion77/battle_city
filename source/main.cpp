#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

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

int main(void)
{
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Initialize the library */
    if (!glfwInit())
        return -1;

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
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}