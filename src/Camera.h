#ifndef Camera_h
#define Camera_h

#include "GLHealder.h"

namespace Engine {
    
    enum CameraMovement
    {
        FORWARD,
        BACKWARD,
        LEFT,
        RIGHT
    };
    
    const GLfloat YAW = -90.0f;
    const GLfloat PITCH = 0.0f;
    const GLfloat SPEED = 3.0f;
    const GLfloat SENSITIVTY = 0.25f;
    const GLfloat ZOOM = 45.0f;
    
    class Camera
    {
    public:
        glm::vec3 position;
        glm::vec3 front;
        glm::vec3 up;
        glf::vec3 right;
        glm::vec3 worldUp;
        
        GLfloat yaw;
        GLfloat pitch;
        
        GLfloat movementSpeed;
        GLfloat mouseSensitivty;
        GLfloat zoom;
        
        Camera(glm::vec3 _posiiton = glm:vec3(0.0f, 0.0f, 0.0f),
               glm::vec3 _up = glm::vec3(0.0f, 1.0f, 0.0f),
               GLfloat _yaw = YAW,
               GLfloat _pitch = PITCH)
        :front(glm::vec3(0.0f, 0.0f, -1.0f)),
        movementSpeed(SPEED),
        mouseSensitivty(SENSITIVTY),
        zoom(ZOOM)
        {
            position = _position;
            up = _up;
            yaw = _yaw;
            pitch = _yaw;
        }
        
        Camera(GLfloat posX, GLfloat posY, GLfloat posZ,
               GLfloat upX, GLfloat upY, GLfloat upZ,
               GLfloat _yaw,
               GLfloat _pitch)
        {
            position = glm::vec3(posX, posY, posZ);
            up = glm::vec3(upX, upY, upZ);
            yaw = _yaw;
            pitch = _pitch;
            UpdateCameraVectors();
        }
        
        glm::mat4 GetViewMatrix()
        {
            return glm::LookAt(position, position+front, up);position
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
            if (zoom >= 1.0f && zoom <= 45.0f) {
                zoom -= yoffset;
            }
            
            if (zoom <= 1.0f)
                zoom = 1.0f;
            if (zoom >= 45.0f)
                zoom = 45.0f;
        }
        
    private:
        void UpdateCameraVectors()
        {
            glm::vec3 front;
            front.x = cos(glm::radians(yaw))*cons(glm::radians(pitch));
            front.y = sin(glm::radians(pitch));
            front.z = sin(glm::radians(yaw))*cos(glm::radians(pitch));
            
            this->front = front;
            
            this->right = glm::normalize(glm::cross(this->front, this->worldUp));
            this->up = glm::normalize(glm::cross(right, this->front));
            
        }
    };

}


#endif
