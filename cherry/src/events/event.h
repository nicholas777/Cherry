#pragma once

#include "core/core.h"
#include "core/keyCodes.h"
#include "core/log.h"
#include "core/mouseButtonCodes.h"
#include "eventType.h"

namespace Cherry {
    struct Event {
    protected:
        Event(EventType type, EventCategory category, const char* name)
            : Type(type), Category(category), Name(name){};
    public:

        EventType Type;
        EventCategory Category;
        std::string Name;
        bool handled = false;

        EventType GetType() const { return Type; };

        EventCategory GetCategory() const { return Category; };

        std::string GetName() const { return Name; };

        virtual std::string ToString() const { return Name; };
    };

    struct GameErrorEvent : public Event {
        GameErrorEvent(const char* message)
            : Event(EventType::GameErrorEvent, EventCategory::GameEvent, "GameErrorEvent"),
              Message(message){};

        const char* Message;

        std::string ToString() const override { return Name + std::string(": ") + Message; };
    };

    struct GameWarningEvent : public Event {
        GameWarningEvent(const char* message)
            : Event(EventType::GameWarningEvent, EventCategory::GameEvent, "GameWarningEvent"),
              Message(message){};

        const char* Message;

        std::string ToString() const override { return Name + std::string(": ") + Message; };
    };

    struct WindowOpenEvent : public Event {
        WindowOpenEvent()
            : Event(EventType::WindowOpenEvent, EventCategory::WindowEvent, "WindowOpenEvent"){};

        std::string ToString() const override { return Name; };
    };

    struct WindowResizeEvent : public Event {
        WindowResizeEvent(int width, int height)
            : Event(EventType::WindowResizeEvent, EventCategory::WindowEvent, "WindowResizeEvent") {
            Width = width;
            Height = height;
        };

        int Width, Height;

        std::string ToString() const override { return Name; };
    };

    struct WindowCloseEvent : public Event {
        WindowCloseEvent()
            : Event(EventType::WindowCloseEvent, EventCategory::WindowEvent, "WindowCloseEvent"){};

        std::string ToString() const override { return Name; };
    };

    struct WindowFocusEvent : public Event {
        WindowFocusEvent()
            : Event(EventType::WindowFocusEvent, EventCategory::WindowEvent, "WindowFocusEvent"){};

        std::string ToString() const override { return Name; };
    };

    struct WindowUnfocusEvent : public Event {
        WindowUnfocusEvent()
            : Event(EventType::WindowUnfocusEvent, EventCategory::WindowEvent,
                    "WindowUnfocusEvent"){};

        std::string ToString() const override { return Name; };
    };

    struct MouseMoveEvent : public Event {
        MouseMoveEvent(int x, int y)
            : Event(EventType::MouseMoveEvent, EventCategory::MouseEvent, "MouseMoveEvent") {
            this->x = x;
            this->y = y;
        };

        int x, y;

        std::string ToString() const override {
            return Name + std::string(": pos=") + std::to_string(x) + std::string(",") +
                   std::to_string(y);
        };
    };

    struct MouseClickEvent : public Event {
        MouseClickEvent(MouseButton button)
            : Event(EventType::MouseClickEvent, EventCategory::MouseEvent, "MouseClickEvent"),
              Button(button){};

        MouseButton Button;

        std::string ToString() const override { return Name + std::string(": pos="); };
    };

    struct MouseReleaseEvent : public Event {
        MouseReleaseEvent(MouseButton button)
            : Event(EventType::MouseReleaseEvent, EventCategory::MouseEvent, "MouseReleaseEvent"),
              Button(button){};

        MouseButton Button;

        std::string ToString() const override {
            return Name + std::string(": btn=") + std::to_string(Button);
        };
    };

    struct MouseScrollEvent : public Event {
        MouseScrollEvent(int offset)
            : Event(EventType::MouseScrollEvent, EventCategory::MouseEvent, "MouseReleaseEvent"),
              Offset(offset){};

        int Offset;

        std::string ToString() const override {
            return Name + std::string(": offset=") + std::to_string(Offset);
        };
    };

    struct KeyPressEvent : public Event {
        KeyPressEvent(Key key, bool repeat)
            : Event(EventType::KeyPressEvent, EventCategory::KeyboardEvent, "KeyPressEvent"),
              Keycode(key), Repeat(repeat){};

        Key Keycode;
        bool Repeat;

        std::string ToString() const override {
            return Name + std::string(": key=") + std::to_string(Keycode);
        };
    };

    struct KeyReleaseEvent : public Event {
        KeyReleaseEvent(Key key)
            : Event(EventType::KeyReleaseEvent, EventCategory::KeyboardEvent, "KeyReleaseEvent"),
              Keycode(key){};

        Key Keycode;

        std::string ToString() const override {
            return Name + std::string(": key=") + std::to_string(Keycode);
        };
    };
}
