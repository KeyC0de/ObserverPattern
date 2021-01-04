#pragma once

#include <vector>
#include "misc.h"


class IObserver;

// the Subject class
class Car final
{
private:
	std::vector<class IObserver*> m_pObservers;
	int m_position;
	Color m_color;
private:
	void notify();
public:
	Car();
	~Car();

	int getPosition() const noexcept;
	void setPosition( int val );
	void setColor( Color color );
	void subscribe( class IObserver* observer );
	void unsubscribe( class IObserver* observer ) noexcept;
	void unsubscribeAll() noexcept;
};