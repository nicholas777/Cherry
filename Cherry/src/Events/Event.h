#pragma once

#include "EventType.h"
#include "core/Core.h"
#include "core/Log.h"

namespace Cherry
{
	struct CHERRY_API Event
	{
	protected:
		Event(EventType type, EventCategory category, const char* name)
			: Type(type), Category(category), Name(name) {};
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

	struct CHERRY_API GameErrorEvent : public Event
	{
		GameErrorEvent(const char* message)
			: Event(EventType::GameErrorEvent,
					EventCategory::GameEvent,
					"GameErrorEvent"), Message(message) {};

		const char* Message;

		std::string ToString() const override { return Name + std::string(": ") + Message; };
	};

	struct CHERRY_API GameWarningEvent : public Event
	{
		GameWarningEvent(const char* message)
			: Event(EventType::GameWarningEvent,
				EventCategory::GameEvent,
				"GameWarningEvent"), Message(message) {};

		const char* Message;

		std::string ToString() const override { return Name + std::string(": ") + Message; };
	};

	struct CHERRY_API WindowOpenEvent : public Event
	{
		WindowOpenEvent()
			: Event(EventType::WindowOpenEvent,
					EventCategory::WindowEvent,
					"WindowOpenEvent") {};

		std::string ToString() const override { return Name; };
	};

	struct CHERRY_API WindowResizeEvent : public Event
	{
		WindowResizeEvent(int width, int height)
			: Event(EventType::WindowResizeEvent,
				EventCategory::WindowEvent,
				"WindowResizeEvent") 
		{
			Width = width;
			Height = height;
		};

		int Width, Height;

		std::string ToString() const override { return Name; };
	};

	struct CHERRY_API WindowCloseEvent : public Event
	{
		WindowCloseEvent()
			: Event(EventType::WindowCloseEvent,
				EventCategory::WindowEvent,
				"WindowCloseEvent") {};

		std::string ToString() const override { return Name; };
	};

	struct CHERRY_API WindowFocusEvent : public Event
	{
		WindowFocusEvent()
			: Event(EventType::WindowFocusEvent,
				EventCategory::WindowEvent,
				"WindowFocusEvent") {};

		std::string ToString() const override { return Name; };
	};

	struct CHERRY_API WindowUnfocusEvent : public Event
	{
		WindowUnfocusEvent()
			: Event(EventType::WindowUnfocusEvent,
				EventCategory::WindowEvent,
				"WindowUnfocusEvent") {};

		std::string ToString() const override { return Name; };
	};

	struct CHERRY_API MouseMoveEvent : public Event
	{
		MouseMoveEvent(int x, int y)
			: Event(EventType::MouseMoveEvent,
				EventCategory::MouseEvent,
				"MouseMoveEvent") 
		{
			this->x = x;
			this->y = y;
		};

		int x, y;

		std::string ToString() const override 
		{ 
			return Name + std::string(": pos=")
				+ std::to_string(x)
				+ std::string(",")
				+ std::to_string(y);
		};
	};

	struct CHERRY_API MouseClickEvent : public Event
	{
		MouseClickEvent(int button)
			: Event(EventType::MouseClickEvent,
					EventCategory::MouseEvent,
					"MouseClickEvent"), Button(button) {};

		int Button;

		std::string ToString() const override
		{
			return Name + std::string(": pos=");
		};
	};

	struct CHERRY_API MouseReleaseEvent : public Event
	{
		MouseReleaseEvent(int button)
			: Event(EventType::MouseReleaseEvent,
				EventCategory::MouseEvent,
				"MouseReleaseEvent"), Button(button) {};

		int Button;

		std::string ToString() const override
		{
			return Name + std::string(": btn=")
				+ std::to_string(Button);
		};
	};

	struct CHERRY_API MouseScrollEvent : public Event
	{
		MouseScrollEvent(int offset)
			: Event(EventType::MouseReleaseEvent,
				EventCategory::MouseEvent,
				"MouseReleaseEvent"), Offset(offset) {};

		int Offset;

		std::string ToString() const override
		{
			return Name + std::string(": offset=")
				+ std::to_string(Offset);
		};
	};

	struct CHERRY_API KeyPressEvent : public Event
	{
		KeyPressEvent(int key, bool repeat)
			: Event(EventType::KeyPressEvent,
				EventCategory::KeyboardEvent,
				"KeyPressEvent"), Key(key), Repeat(repeat) {};

		int Key;
		bool Repeat;

		std::string ToString() const override
		{
			return Name + std::string(": key=")
				+ std::to_string(Key);
		};
	};

	struct CHERRY_API KeyReleaseEvent : public Event
	{
		KeyReleaseEvent(int key)
			: Event(EventType::KeyReleaseEvent,
				EventCategory::KeyboardEvent,
				"KeyReleaseEvent"), Key(key) {};

		int Key;

		std::string ToString() const override
		{
			return Name + std::string(": key=")
				+ std::to_string(Key);
		};
	};
}
