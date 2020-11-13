#pragma once

#include <vector>

enum class Color;
class IObserver;

class Car final
{
private:
	std::vector<class IObserver*> m_observers;
	int m_position;
	Color m_color;

	void notify();
public:
	Car()
		:
		m_position{0},
		m_color{Color::BLACK}
	{}
	~Car()
	{
		unsubscribeAll();
	}

	int getPosition() const noexcept
	{
		return m_position;
	}
	void setPosition( int val )
	{
		m_position = val;
		notify(/*MessageType*/);			// CAN ALSO SPECIFY MESSAGE TYPE to send
	}

	void setColor( Color color )
	{
		std::cout << "setting color" << '\n';
		m_color = color;
		//notify(/*MessageType*/);	// suppose nobody subscribed to this event
	}
	
	void subscribe( IObserver* observer )
	{
		m_observers.push_back( observer );
		std::cout << "IObserver Subscribed\n";
	}

	void unsubscribe( IObserver* observer ) noexcept
	{
		m_observers.erase( std::remove( m_observers.begin(),
			m_observers.end(),
			observer ),
			m_observers.end() );
		std::cout << "IObserver Unsubscribed\n";
	}

	void unsubscribeAll() noexcept
	{
		for ( auto* ob : m_observers )
			unsubscribe( ob );
	}
};