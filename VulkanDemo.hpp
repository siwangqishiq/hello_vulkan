#pragma once

#include "GLFW/glfw3.h"
#include "vulkan/vulkan.h"
#include <vector>

inline const int SCREEN_WIDTH = 800;
inline const int SCREEN_HEIGHT = 600;

inline const char *APP_NAME = "HelloVulkan";

#ifdef DEBUG
    const bool enableValidationLayers = true;
#else
    const bool enableValidationLayers = true;
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

    GLFWwindow *window;
    
    VkInstance instance;

    const std::vector<const char*> validationLayers = {
        "VK_LAYER_KHRONOS_validation"
    };
    
};
