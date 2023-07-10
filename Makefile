CC := g++

SRC_DIR := .
BUILD_DIR := build
CFLAGS := -std=c++17

SHADER_DIR := shaders
GLSL_C := glslangValidator

build_dir:
	mkdir -p ${BUILD_DIR}

app.o:build_dir VulkanDemo.cpp VulkanDemo.hpp
	${CC} -c ${SRC_DIR}/VulkanDemo.cpp -o ${BUILD_DIR}/app.o -I include/ ${CFLAGS}

main:app.o
	${CC} -c ${SRC_DIR}/main.cpp -o ${BUILD_DIR}/main.o -I include/ ${CFLAGS}

link:main
	${CC} ${BUILD_DIR}/*.o -o ${BUILD_DIR}/main.exe -Llib -lglfw3dll -lvulkan-1
	
run:link
	${BUILD_DIR}/main
	
clean:
	rm -f ${BUILD_DIR}/*.o 
	rm -f ${BUILD_DIR}/main.exe


