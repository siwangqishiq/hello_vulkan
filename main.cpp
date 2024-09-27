
#include <iostream>
#include <stdexcept>
#include "VulkanDemo.h"

int main(){
    App app;
    try{
        app.run();
    }catch(const std::exception &e){
        std::cerr << e.what() << std::endl;
        return -1;
    }
    return 0;
}


