#pragma once

#include "GLFW/glfw3.h"
#include "vulkan/vulkan.h"
#include <vector>

inline const int SCREEN_WIDTH = 1280;
inline const int SCREEN_HEIGHT = 800;

inline const char *APP_NAME = "HelloVulkan";

#define DEBUG 1

#ifdef DEBUG
    const bool enableValidationLayers = true;
#else
    const bool enableValidationLayers = false;
#endif

class App{
public:
    void run();
private:
    void initWindow();
    void initVulkan();
    void mainLoop();
    void dispose();

    void createInstance();

    bool checkValidationLayerSupport();

    std::vector<const char*> getRequiredExtensions();

    void setupDebugMessenger();

    void pickPhysicalDevice();

    void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);

    VkResult createDebugUtilsMessengerEXT(VkInstance instance, 
        const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, 
        const VkAllocationCallbacks* pAllocator, 
        VkDebugUtilsMessengerEXT* pDebugMessenger);

    void destroyDebugUtilsMessengerEXT(VkInstance instance, 
            VkDebugUtilsMessengerEXT debugMessenger, 
            const VkAllocationCallbacks* pAllocator);

    GLFWwindow *window;
    
    VkInstance instance;

    VkDebugUtilsMessengerEXT debugMessenger;

    VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;

    std::vector<const char*> validationLayers = {
        "VK_LAYER_KHRONOS_validation"
    };
    std::vector<const char*> extensions = {};
    
    static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
        VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
        VkDebugUtilsMessageTypeFlagsEXT messageType,
        const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
        void* pUserData);
};
