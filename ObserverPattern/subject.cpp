#include <iostream>
#include <algorithm>
#include "subject.h"
#include "observer.h"


Car::Car()
	:
	m_position(0),
	m_color(Color::BLACK)
{

}

Car::~Car()
{
	unsubscribeAll();
}

int Car::getPosition() const noexcept
{
	return m_position;
}

void Car::setPosition( int val )
{
	m_position = val;
	notify(/*MessageType*/);			// CAN ALSO SPECIFY MESSAGE TYPE to send
}

void Car::setColor( Color color )
{
	std::cout << "setting color\n";
	m_color = color;
	//notify(/*MessageType*/);	// suppose nobody subscribed to this event
}

void Car::subscribe( class IObserver* observer )
{
	m_pObservers.push_back( observer );
	std::cout << "IObserver Subscribed\n";
}

void Car::unsubscribe( class IObserver* observer ) noexcept
{
	m_pObservers.erase( std::remove( m_pObservers.begin(),
			m_pObservers.end(),
			observer ),
		m_pObservers.end() );
	std::cout << "IObserver Unsubscribed\n";
}

void Car::unsubscribeAll() noexcept
{
	for ( auto* ob : m_pObservers )
	{
		unsubscribe( ob );
	}
}

void Car::notify(/*MessageType*/)
{
	for ( const auto* ob : m_pObservers )
	{
		// SWITCH OVER MESSAGE TYPES AND NOTIFY INTERESTED OBSERVERS APPROPRIATELY
		// ..
		ob->notify();
	}
}