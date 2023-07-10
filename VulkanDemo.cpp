
#include "VulkanDemo.hpp"
#include <iostream>
#include <cstring>


void App::run(){
    initWindow();
    initVulkan();
    mainLoop();
    dispose();
}

void App::initWindow(){
    glfwInit();
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, APP_NAME, nullptr, nullptr);
}

void App::initVulkan(){
    createInstance();
    pickPhysicalDevice();
}

void App::createInstance(){
    if (enableValidationLayers && !checkValidationLayerSupport()) {
        throw std::runtime_error("validation layers requested, but not available!");
    }

    VkApplicationInfo appInfo{};
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pApplicationName = APP_NAME;
    appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.pEngineName = "NoEngine";
    appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.apiVersion = VK_API_VERSION_1_0;

    VkInstanceCreateInfo instanceCreateInfo{};
    instanceCreateInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    instanceCreateInfo.pApplicationInfo = &appInfo;

    uint32_t glfwExtensionCount = 0;
    const char** glfwExtension;
    glfwExtension = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
    std::cout << "glfwExtensionCount = " << glfwExtensionCount << std::endl;
    for(int i = 0 ; i < glfwExtensionCount;i++){
        std::cout << "glfwExtension : " << glfwExtension[i] << std::endl;
    }//end for i

    instanceCreateInfo.enabledExtensionCount = glfwExtensionCount;
    instanceCreateInfo.ppEnabledExtensionNames = glfwExtension;

    if (enableValidationLayers) {
        // const char *debugLayer = "VK_LAYER_LUNARG_monitor";
        // validationLayers.push_back(debugLayer);
        instanceCreateInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
        instanceCreateInfo.ppEnabledLayerNames = validationLayers.data();
    } else {
        instanceCreateInfo.enabledLayerCount = 0;
    }

    if(vkCreateInstance(&instanceCreateInfo , nullptr , &instance) != VK_SUCCESS){
        throw std::runtime_error("failed to create instance!");
    }
}

bool App::checkValidationLayerSupport(){
    uint32_t layerCount;
    vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

    std::vector<VkLayerProperties> availableLayers(layerCount);
    vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());
    std::cout << "available layer count: " << layerCount << std::endl;
    for(auto &prop : availableLayers){
        std::cout << prop.layerName << " " << prop.description << std::endl;
    }

    for (const char* layerName : validationLayers) {
        bool layerFound = false;
        for (const auto& layerProperties : availableLayers) {
            if (strcmp(layerName, layerProperties.layerName) == 0) {
                layerFound = true;
                break;
            }
        }

        if (!layerFound) {
            return false;
        }
    }
    return true;
}

void App::pickPhysicalDevice(){
    uint32_t deviceCount = 0;
    vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr);

    if(deviceCount == 0){
        throw std::runtime_error("failed to find GPUs with Vulkan support!");
    }

    std::vector<VkPhysicalDevice> devices(deviceCount);
    vkEnumeratePhysicalDevices(instance, &deviceCount, devices.data());
    std::cout << "physical device count :" << deviceCount << std::endl;

    for(VkPhysicalDevice &pDevice : devices){
        VkPhysicalDeviceProperties prop;
        vkGetPhysicalDeviceProperties(pDevice , &prop);

        std::cout << "physical device name :" << prop.deviceName 
            << " type " << prop.deviceType 
            << " deviceid " << prop.deviceID 
            << std::endl;
    }//end for devices 
    
       
}

void App::mainLoop(){
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
    }//end while
}

void App::dispose(){

    vkDestroyInstance(instance , nullptr);
    glfwDestroyWindow(window);
    glfwTerminate();
}

