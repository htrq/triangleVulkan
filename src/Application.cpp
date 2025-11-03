#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <stdexcept>
#include <cstdlib>
#include <print>
#include <vector>
#include <string_view>
#include "Application.hpp"


void Application::run() {
    initWindow();
    initVulkan();
    mainLoop();
    cleanup();
}

void Application::initWindow() {
    if (!glfwInit()) {
        throw std::runtime_error("Error initializing GLFW");
    }
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    window = glfwCreateWindow(windowWidth, windowHeight, "MyVulkanApp", nullptr, nullptr);
}

void Application::initVulkan() {
    selectValidationLayer();
    createInstance();
}

void Application::selectValidationLayer() {
    uint32_t layerCount;
    vkEnumerateInstanceLayerProperties(&layerCount, nullptr);
    std::vector<VkLayerProperties> layerProperties(layerCount);
    vkEnumerateInstanceLayerProperties(&layerCount, layerProperties.data());
    bool layerFound { false };
    for (auto& lay : layerProperties)
    {
        if (std::string_view{lay.layerName} == "VK_LAYER_KHRONOS_validation") {
            availableLayersNames.push_back(lay.layerName);
            layerFound = true;
        }
    }
    if (!layerFound) {
        std::println("{}", "Suitable Validation Layer Not Found!");
    }
}
    
void Application::createInstance() {
    VkApplicationInfo appInfo{};
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.pEngineName = "No Engine";
    appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.apiVersion = VK_API_VERSION_1_0;
        
    // get glfw extension amount and names for enabledExtensionCount and ppEnabledExtensionNames
    uint32_t extensionsCount;
    const char** extensionsNames = glfwGetRequiredInstanceExtensions(&extensionsCount);
    
    for (int i = 0; i < extensionsCount; i++) {
        std::println("Available extensions: {}", extensionsNames[i]);  
    }
    
    VkInstanceCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo = &appInfo;
    createInfo.enabledExtensionCount = extensionsCount;
    createInfo.ppEnabledExtensionNames = extensionsNames;
    
    // tmp vector to push pointers
    std::vector<const char*> availableLayersNamesPtrs;  
    for (auto& lay : availableLayersNames)
    {
        availableLayersNamesPtrs.push_back(lay.c_str());
    }

    createInfo.ppEnabledLayerNames = availableLayersNamesPtrs.data();
    createInfo.enabledLayerCount = availableLayersNamesPtrs.size();
    std::println("{}", "*check* Enabled Layers: ");
    for (auto& str : availableLayersNames) {
        std::print("{} ", str);
    }
        
    
    
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



