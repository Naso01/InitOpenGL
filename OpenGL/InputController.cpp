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

    // Only act when left click is pressed
    if (glfwGetMouseButton(m_window, GLFW_MOUSE_BUTTON_LEFT) != GLFW_PRESS)
        return movement;

    // Mouse pos
    double mouseX, mouseY;
    glfwGetCursorPos(m_window, &mouseX, &mouseY);

    Resolution r = WindowController::GetInstance().GetResolution();

    // Screen center
    double centerX = r.width * 0.5;
    double centerY = r.height * 0.5;

    // Vector from center → mouse
    double dx = mouseX - centerX;
    double dy = centerY - mouseY;
    // NOTE: invert Y because OpenGL coords + screen coords flipped

    // Compute distance from center
    double dist = sqrt(dx * dx + dy * dy);

    // Normalize direction
    double len = sqrt(dx * dx + dy * dy);
    if (len < 0.0001)
        return movement;

    double ndx = dx / len;   // normalized x direction
    double ndy = dy / len;   // normalized y direction

    // Scale: farther = faster
    double maxDist = sqrt(centerX * centerX + centerY * centerY);
    double intensity = dist / maxDist; // 0 to 1

    // Clamp intensity
    intensity = glm::clamp(intensity, 0.0, 1.0);

    // Base speed
    const float baseSpeed = 0.01f;

    // Final movement
    float speed = baseSpeed * (float)intensity;

    movement.x += (float)ndx * speed;
    movement.y += (float)ndy * speed;

    return movement;
}
