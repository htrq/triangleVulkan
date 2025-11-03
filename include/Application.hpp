#pragma once
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <string>
#include <vector>

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
    std::vector<std::string> availableLayersNames;  // TODO: move this in Validation.hpp
     
    void initWindow();
    void initVulkan();
    void selectValidationLayer();
    void createInstance();
	void mainLoop();
	void cleanup();
    
};


