#ifndef INPUT_H
#define INPUT_H

#include <Thor/Input.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <unordered_map>
#include <list>
#include <functional>
#include <vector>

enum Actions
{
    ACTION_JUMP,
    ACTION_MOVE_RIGHT,
    ACTION_MOVE_LEFT,

    // Key actions
    ACTION_UP,
    ACTION_DOWN,
    ACTION_ENTER,

    // Debug stuff
    ACTION_ENABLE_DEBUG,
    ACTION_TOGGLE_PAUSE,

    // General stuff
    ACTION_EXIT,
};

enum ButtonDevice
{
    DEVICE_NONE,
    DEVICE_JOYSTICK,
    DEVICE_KEYBOARD,
    DEVICE_EVENT
};

enum ButtonType
{
    BUTTON_TYPE_NONE,
    BUTTON_TYPE_KEY,
    BUTTON_TYPE_AXIS
};

class Game;

class Input
{
public:
    class InputButton
    {
    private:
        union ButtonKey
        {
            sf::Keyboard::Key KeyboardKey;
            int JoystickButton;
            sf::Joystick::Axis JoystickAxis;
            sf::Event::EventType Event;

            ButtonKey(sf::Event::EventType ev) : Event(ev) { }
            ButtonKey(sf::Keyboard::Key key) : KeyboardKey(key) {}
            ButtonKey(int key) : JoystickButton(key) {}
            ButtonKey(sf::Joystick::Axis axis) : JoystickAxis(axis) {}
        };
    public:
        template<typename T = sf::Keyboard::Key>
        InputButton(ButtonDevice device, ButtonType type, T k = sf::Keyboard::Space, std::function<void(thor::ActionContext<Actions>)>* callback = nullptr) : Device(device), Type(type), Button(k), Callback(callback) {}

        ButtonDevice Device;
        ButtonType Type;
        ButtonKey Button;
        std::function<void(thor::ActionContext<Actions>)>* Callback;
    };

    Input(Game* _game);
    ~Input();

    void LoadBindings();
    void SaveBindings();

    void LoadActions();
    void Update(sf::RenderWindow& window);

    bool IsActive(unsigned int player, Actions action) const;

    // Define event handlers
    void OnExit(thor::ActionContext<Actions> context);
    void TogglePause(thor::ActionContext<Actions> context);


    // Misc stuff
    static bool IsSystemAction(Actions action);

    std::vector<thor::ActionMap<Actions>*> KeyActions;
    std::vector<thor::ActionMap<Actions>::CallbackSystem*> PlayerCallbacks;
    thor::ActionMap<Actions>::CallbackSystem SystemCallbacks;
    typedef std::unordered_multimap<Actions, InputButton> BindingsMap;
    std::vector<BindingsMap> KeyBindings;
    Game* game;
};
#endif