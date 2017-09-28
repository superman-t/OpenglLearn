cmake_minimum_required (VERSION 2.8)

project (OpenglLearn)
add_subdirectory(3rdparty/glfw)
add_subdirectory(3rdparty/SOIL)

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
include_directories(${PROJECT_SOURCE_DIR}/3rdparty/SOIL/include)
include_directories(${PROJECT_SOURCE_DIR}/3rdparty/glm)

include_directories(3rdparty/assimp-3.1.1/include)
link_directories(${PROJECT_SOURCE_DIR}/3rdparty/assimp-3.1.1/lib)

if(WIN32)
	add_definitions(-DTARGET_PLATFORM_WINDOWS -DWIN32)
endif()

if(APPLE)
	add_definitions( -DTARGET_PLATFORM_MAC -DTARGET_PLATFORM_IOS)
endif()

if(CMAKE_GENERATOR STREQUAL Xcode)
    add_definitions( -DTARGET_COMPILE_XCODE)
endif()

find_package(OpenGL REQUIRED)
include_directories( ${OPENGL_INCLUDE_DIRS} )


add_executable(OpenglLearn ${OpenglLearn_src} )

target_link_libraries (OpenglLearn  ${OPENGL_LIBRARIES} glfw ${GLFW_LIBRARIES} assimp )

set(CMAKE_CXX_FLAGS "-std=c++11")

if (MSVC)
    set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT OpenglLearn)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -W4 -EHsc -D_USE_MATH_DEFINES")

else()
	
endif (MSVC)
