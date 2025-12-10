#include "InputController.h"
#include "WindowController.h"

InputController::InputController()
{
    m_window = WindowController::GetInstance().GetWindow();
}

InputController::~InputController() {}

glm::vec3 InputController::GetMovementVector()
{
    glm::vec3 movement(0.0f);

    // --- Check what type of movement we're doing ---
    bool moveXY = glfwGetMouseButton(m_window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS;
    bool moveZ = glfwGetMouseButton(m_window, GLFW_MOUSE_BUTTON_MIDDLE) == GLFW_PRESS;

    // If no buttons pressed → no movement
    if (!moveXY && !moveZ)
        return movement;

    // --- Get mouse position ---
    double mouseX, mouseY;
    glfwGetCursorPos(m_window, &mouseX, &mouseY);

    Resolution r = WindowController::GetInstance().GetResolution();
    double centerX = r.width * 0.5;
    double centerY = r.height * 0.5;

    // Vector from center → mouse
    double dx = mouseX - centerX;
    double dy = centerY - mouseY; // Y inverted

    double dist = sqrt(dx * dx + dy * dy);
    if (dist < 0.0001)
        return movement;

    // Normalized movement direction
    double ndx = dx / dist;
    double ndy = dy / dist;

    // Intensity based on distance from center
    double maxDist = sqrt(centerX * centerX + centerY * centerY);
    double intensity = glm::clamp(dist / maxDist, 0.0, 1.0);

    const float baseSpeed = 0.01f;
    float speed = baseSpeed * (float)intensity;

    // --- Apply correct movement type --- 
    if (moveXY)
    {
        movement.x = (float)ndx * speed;
        movement.y = (float)ndy * speed;
    }

    if (moveZ)
    {
        movement.z = (float)ndy * speed;
    }

    return movement;
}
