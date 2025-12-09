#include "InputController.h"
#include "WindowController.h"

// Constructor
InputController::InputController()
{
    m_window = WindowController::GetInstance().GetWindow();
}

InputController::~InputController()
{
}

// Update: call once per frame
void InputController::Update(glm::vec3& _meshPosition)
{
    // Check left mouse click
    if (glfwGetMouseButton(m_window, GLFW_MOUSE_BUTTON_LEFT) != GLFW_PRESS)
        return;

    // Get mouse position
    double mouseX, mouseY;
    glfwGetCursorPos(m_window, &mouseX, &mouseY);

    Resolution r = WindowController::GetInstance().GetResolution();

    // Convert into quadrants
    bool left = mouseX < (r.width * 0.5);
    bool top = mouseY < (r.height * 0.5);

    // Movement step
    const float speed = 0.1f;

    // Determine quadrant
    if (left && top)
    {
        // Top-left → move light up-left
        _meshPosition.x -= speed;
        _meshPosition.y += speed;
    }
    else if (!left && top)
    {
        // Top-right → move light up-right
        _meshPosition.x += speed;
        _meshPosition.y += speed;
    }
    else if (left && !top)
    {
        // Bottom-left → move down-left
        _meshPosition.x -= speed;
        _meshPosition.y -= speed;
    }
    else
    {
        // Bottom-right → move down-right
        _meshPosition.x += speed;
        _meshPosition.y -= speed;
    }
}