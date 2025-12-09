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
    void Initialize();                     // Set callbacks, etc.
    void Update(glm::vec3& _meshPosition);                         // Called every frame
    ClickQuadrant GetClickedQuadrant();    // Determines which quadrant was clicked
    glm::vec2 GetMousePosition();          // Normalized or raw mouse pos

private:
    // Helpers
    ClickQuadrant DetermineQuadrant(const glm::vec2& mousePos);

    // Members
    GLFWwindow* m_window;
};

#endif // !INPUT_CONTROLLER_H
