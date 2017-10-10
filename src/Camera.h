#ifndef Camera_h
#define Camera_h

#include "GLHealder.h"

//namespace Engine {
    
    enum CameraMovement
    {
        FORWARD,
        BACKWARD,
        LEFT,
        RIGHT,
        UNKNOW
    };
    
    const GLfloat YAW = -90.0f;
    const GLfloat PITCH = 0.0f;
    const GLfloat SPEED = 3.0f;
    const GLfloat SENSITIVTY = 0.025f;
    const GLfloat ZOOM = 45.0f;
    
    class Camera
    {
    public:
        glm::vec3 position;
        glm::vec3 front;
        glm::vec3 up;
        glm::vec3 right;
        glm::vec3 worldUp;
        
        GLfloat yaw;
        GLfloat pitch;
        
        GLfloat movementSpeed;
        GLfloat mouseSensitivty;
        GLfloat zoom;
        
        Camera(glm::vec3 _position = glm::vec3(0.0f, 15.0f, 40.0f),
               glm::vec3 _up = glm::vec3(0.0f, 1.0f, 0.0f),
               GLfloat _yaw = YAW,
               GLfloat _pitch = PITCH)
        :front(glm::vec3(0.0f, 0.0f, -1.0f)),
        movementSpeed(SPEED),
        mouseSensitivty(SENSITIVTY),
        zoom(ZOOM)
        {
            position = _position;
            worldUp = _up;
            yaw = _yaw;
            pitch = _pitch;
            UpdateCameraVectors();
        }
        
        Camera(GLfloat posX, GLfloat posY, GLfloat posZ,
               GLfloat upX, GLfloat upY, GLfloat upZ,
               GLfloat _yaw,
               GLfloat _pitch)
        {
            position = glm::vec3(posX, posY, posZ);
            worldUp = glm::vec3(upX, upY, upZ);
            yaw = _yaw;
            pitch = _pitch;
            UpdateCameraVectors();
        }
        
        glm::mat4 GetViewMatrix()
        {
            //std::cout << position.y << " " << position.z << " " << zoom << " " << pitch << " " << yaw << std::endl;
            return glm::lookAt(position, position+front, up);
        }
        
        void ProcessKeyboard(CameraMovement direction, GLfloat deltaTime)
        {
            GLfloat velocity = this->movementSpeed * deltaTime;
            if (direction == FORWARD)
                this->position += this->front * velocity;
            if (direction == BACKWARD)
                this->position -= this->front * velocity;
            
            if (direction == LEFT)
                this->position -= this->right * velocity;
            if (direction == RIGHT)
                this->position += this->right * velocity;
            //std::cout << position.x << "," << position.z << std::endl;
        }
        
        void ProcessMouseMovement(GLfloat xoffset, GLfloat yoffset, GLboolean constrainPitch)
        {
            xoffset *= mouseSensitivty;
            yoffset *= mouseSensitivty;
            
            yaw += xoffset;
            pitch += yoffset;
            
            if (constrainPitch) {
                if (pitch > 89.0f)
                    pitch = 89.0f;
                if (pitch < -89.0f)
                    pitch = -89.0f;
            }
            UpdateCameraVectors();
        }
        
        void ProcessMouseScroll(GLfloat yoffset)
        {
            if (zoom >= 0.1f && zoom <= 90.0f) {
                zoom -= yoffset;
            }
            
            if (zoom <= 0.1f)
                zoom = 0.1f;
            if (zoom >= 90.0f)
                zoom = 90.0f;
        }
        
    private:
        void UpdateCameraVectors()
        {
            //std::cout << "yaw " << yaw << " " << "pitch " << pitch << std::endl;
            glm::vec3 front;
            front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
            front.y = sin(glm::radians(pitch));
            front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
            
            this->front = front;
            
            this->right = glm::normalize(glm::cross(this->front, this->worldUp));
            this->up = glm::normalize(glm::cross(right, this->front));
            
        }
    };

//}


#endif
