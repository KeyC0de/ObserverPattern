#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>


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
	Vec2( int x,
		int y )
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

//////////////////////////////////////////////////////////////////////////////////////////

// forward declaration
class Car;

class IObserver 
{
	Car* m_pSubject;
public:
	explicit IObserver( Car* subject )
		:
		m_pSubject{subject} 
	{}
	virtual ~IObserver() noexcept
	{
		m_pSubject->unsubscribe( this );
	}

	IObserver( const IObserver& rhs ) = delete;
	IObserver& operator=( const IObserver& rhs ) = delete;
	IObserver( IObserver&& rhs )
		:
		m_pSubject{std::move( rhs.m_pSubject )}
	{}
	IObserver& operator=( IObserver&& rhs ) noexcept
	{
		if ( this != &rhs )
		{
			std::swap( this->m_pSubject, rhs.m_pSubject );
		}
		return *this;
	}

	virtual void update() const noexcept = 0;
};

class LeftObserver
	: public IObserver 
{
	// enum with messages of interest - subscribe to them all
public:
	LeftObserver( Car* subject )
		:
		IObserver{subject}
	{
		subject->subscribe( this );			// CAN ALSO SUBSCRIBE TO A MESSAGE TYPE
	}

	void update() const noexcept override
	{
		std::wcout << L"Car turned left\n";
	}
};

class RightObserver
	: public IObserver 
{
public:
	RightObserver( Car* subject )
		:
		IObserver{subject}
	{
		subject->subscribe( this );
	}

	void update() const noexcept override
	{
		std::wcout << L"Car turned right\n";
	}
};


void Car::notify(/*MessageType*/)
{
	for ( auto* ob : m_observers )
	{// CHOOSE OVER MESSAGE TYPES TO NOTIFY APPROPRIATE OBSERVERS
		ob->update();
	}
}