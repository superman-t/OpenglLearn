cmake_minimum_required (VERSION 2.8)

project (OpenglLearn)

add_subdirectory(3rdparty/glfw)
add_subdirectory(3rdparty/assimp)

file (GLOB OpenglLearn_src "main.cpp" 
							"src/*.cpp" "src/*.h" 
							"src/Managers/*.h" "src/Managers/*.cpp" 
							"src/Init/*.h" "src/Init/*.cpp" 
							"src/Rendering/*.h" "src/Rendering/*.cpp"
              "src/Rendering/Models/*.h" "src/Rendering/Models/*.cpp"
							)


if (WIN32)
	include_directories(${PROJECT_SOURCE_DIR}/3rdparty/glad/include)
	file(GLOB OpenglLearn_src  ${OpenglLearn_src} "src/glad.c")
	link_directories(${CMAKE_BINARY_DIR}/lib)
endif()

include_directories(${PROJECT_SOURCE_DIR}/3rdparty/glfw/include)
include_directories(${PROJECT_SOURCE_DIR}/3rdparty/glm)

include_directories(${PROJECT_BINARY_DIR}/3rdparty/assimp/include)
include_directories(${PROJECT_SOURCE_DIR}/3rdparty/assimp/include)

if(WIN32)
	add_definitions(-DTARGET_PLATFORM_WINDOWS -DWIN32)
endif()

if(APPLE)
	add_definitions( -DTARGET_PLATFORM_MAC -DTARGET_PLATFORM_IOS)
endif()

if(CMAKE_GENERATOR STREQUAL Xcode)
    add_definitions( -DTARGET_COMPILE_XCODE)
endif()

if(ANDROID)
  # Android requires GL ES 2.0 package automatically
  set(LIBRARIES GLESv2)
else()
  find_package (OpenGL REQUIRED)
  include_directories (${OPENGL_INCLUDE_DIR})
  set(LIBRARIES ${OPENGL_LIBRARIES})
endif()

add_executable(OpenglLearn ${OpenglLearn_src} )

target_link_libraries (OpenglLearn  ${LIBRARIES} glfw ${GLFW_LIBRARIES} assimp)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -v -stdlib=libc++")

if (MSVC)
    set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT OpenglLearn)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -W4 -EHsc -D_USE_MATH_DEFINES")

else()
    set(CMAKE_CXX_COMPILER      "clang++" )         # 显示指定使用的C++编译器
    set(CMAKE_CXX_FLAGS   "-g")                     # 调试信息
    set(CMAKE_CXX_FLAGS   "-Wall")                  # 开启所有警告

    set(CMAKE_CXX_FLAGS_DEBUG   "-O0" )             # 调试包不优化
    set(CMAKE_CXX_FLAGS_RELEASE "-O2 -DNDEBUG " )   # release包优化
endif (MSVC)
