#pragma once

enum class Color
{
	ORANGE,
	RED,
	YELLOW,
	BLUE,
	PINK,
	CYAN,
	MAGENTA,
	BLACK,
	GRAY
};

enum MessageType : int
{
	UNKNOWN = 0,
	KEYBOARD_PRESSED,
	MOUSE_MOVED,
	MOUSE_PRESSED,
	COLLISSION,
	OBJECT_DESTROYED
};

// when a key mouse/keyboard/controller has been pressed
enum KeyCode : int
{
	MOUSE_LMB = 0,
	MOUSE_MMB,
	MOUSE_RMB,
	KEYBOARD_UP,
	KEYBOARD_RIGHT,
	KEYBOARD_DOWN,
	KEYBOARD_LEFT
};

struct Vec2
{
	Vec2( int x, int y )
		:
		x(x),
		y(y)
	{}
	int x;
	int y;
};


class Message
{
	MessageType m_type;
};

class KeyMessage
	: Message
{
public:
	KeyCode m_code;
};

class MouseMessage
	: Message
{
public:
	Vec2 m_position;
};
