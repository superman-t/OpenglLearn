cmake_minimum_required (VERSION 2.8)

project (OpenglLearn)
add_subdirectory(3rdparty/glfw)
file (GLOB OpenglLearn_src "*.cpp" "*.h" "src/*.cpp" "src/*.h" )
include_directories(${PROJECT_SOURCE_DIR}/3rdparty/glfw/include)
#link_directories(${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/glfw/lib)

if (WIN32)
	include_directories(${PROJECT_SOURCE_DIR}/3rdparty/glad/include)
	file(GLOB OpenglLearn_src  ${OpenglLearn_src} "src/glad.c")
	link_directories(${CMAKE_BINARY_DIR}/lib)
endif()

#define
if(WIN32)
	add_definitions(-DTARGET_PLATFORM_WINDOWS -DWIN32)
endif()

if(APPLE)
	add_definitions( -DTARGET_PLATFORM_MAC -DTARGET_PLATFORM_IOS)
endif()

find_package(OpenGL REQUIRED)
include_directories( ${OPENGL_INCLUDE_DIRS} )

add_executable(OpenglLearn ${OpenglLearn_src} )
if (WIN32)
    set(GLFW_LIBRARY "glfw3")
elseif(APPLE)
    set(GLFW_LIBRARY "glfw")
endif()
target_link_libraries (OpenglLearn  ${OPENGL_LIBRARIES} ${GLFW_LIBRARY} )

set(CMAKE_CXX_FLAGS "-std=c++11")

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
