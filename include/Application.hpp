#pragma once
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

class Application {
public:
    Application() = default;
    ~Application() = default;
    void run();

private:
    GLFWwindow* window;
    const uint32_t windowWidth { 800 };
    const uint32_t windowHeight { 600 };
	
	VkInstance instance;
    
    void createInstance();
    void initVulkan();
	void mainLoop();
	void cleanup();
    void initWindow();
};


