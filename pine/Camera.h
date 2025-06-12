#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

// Directions for keyboard input
enum Camera_Movement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

class Camera {
public:
    // Camera Attributes
    glm::vec3 Position;
    glm::vec3 Front;
    glm::vec3 Up;
    glm::vec3 Right;
    glm::vec3 WorldUp;

    // Euler Angles
    float Yaw;
    float Pitch;

    // Options
    float MovementSpeed;
    float MouseSensitivity;

    // Constructor with vectors
    Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 3.0f),
           glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f),
           float yaw = -90.0f,
           float pitch = 0.0f);

    // Returns the view matrix calculated using Euler Angles and the LookAt Matrix
    glm::mat4 GetViewMatrix() const;

    // Processes input received from keyboard
    void ProcessKeyboard(Camera_Movement direction, float deltaTime);

    // Processes input received from mouse movement
    void ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch = true);

private:
    // Updates the Front, Right and Up vectors from the updated Euler angles
    void updateCameraVectors();
};
