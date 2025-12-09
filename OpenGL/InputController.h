#ifndef INPUT_CONTROLLER_H
#define INPUT_CONTROLLER_H

#include "StandardIncludes.h"

enum class ClickQuadrant {
    NONE = 0,
    TOP_LEFT,
    TOP_RIGHT,
    BOTTOM_LEFT,
    BOTTOM_RIGHT
};

class InputController : public Singleton<InputController>
{
public:
    // Constructor / Destructor
    InputController();
    virtual ~InputController();

    // Methods
    void Initialize();               
    glm::vec3 GetMovementVector();                         

private:

    // Members
    GLFWwindow* m_window;
};

#endif // !INPUT_CONTROLLER_H
