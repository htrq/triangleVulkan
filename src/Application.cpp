#include <stdexcept>
#include <cstdlib>
#include <print>
#include "Application.hpp"

void Application::run() {
    initVulkan();
    mainLoop();
    cleanup();
}
    
void Application::createInstance() {
    VkApplicationInfo appInfo{};
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.pEngineName = "No Engine";
    appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.apiVersion = VK_API_VERSION_1_0;
        
    uint32_t extensionsCount;
    const char** extensionsNames = glfwGetRequiredInstanceExtensions(&extensionsCount);
    for (int i = 0; i < extensionsCount; i++)
    {
        std::print("Available extensions: {}", extensionsNames[i]);  
    }
    
    VkInstanceCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo = &appInfo;
    createInfo.enabledExtensionCount = extensionsCount;
    createInfo.ppEnabledExtensionNames = extensionsNames;
    createInfo.enabledLayerCount = 0;
    
        
}
    
void Application::initVulkan() {
    createInstance();
}

void Application::mainLoop() {
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
    }
}

void Application::cleanup() {
    glfwDestroyWindow(window);
    glfwTerminate();
}

void Application::initWindow() {
    if (!glfwInit()) {
        throw std::runtime_error("Error initializing GLFW");
    }
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    window = glfwCreateWindow(windowWidth, windowHeight, "MyVulkanApp", nullptr, nullptr);
}

