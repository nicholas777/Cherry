#pragma once

namespace Cherry {
    enum class EventType {
        Unknown = 0,
        GameErrorEvent,
        GameWarningEvent,
        WindowOpenEvent,
        WindowResizeEvent,
        WindowCloseEvent,
        WindowFocusEvent,
        WindowUnfocusEvent,
        MouseMoveEvent,
        MouseClickEvent,
        MouseReleaseEvent,
        MouseScrollEvent,
        KeyPressEvent,
        KeyReleaseEvent
    };

    enum class EventCategory { GameEvent, WindowEvent, MouseEvent, KeyboardEvent };
}
