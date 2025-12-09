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

    bool left = mouseX < (r.width * 0.5);
    bool top = mouseY < (r.height * 0.5);

    const float speed = 0.001f;

    if (left && top)
        movement = { -speed,  speed, 0.0f }; // up-left
    else if (!left && top)
        movement = { speed,  speed, 0.0f }; // up-right
    else if (left && !top)
        movement = { -speed, -speed, 0.0f }; // down-left
    else
        movement = { speed, -speed, 0.0f }; // down-right

    return movement;
}
