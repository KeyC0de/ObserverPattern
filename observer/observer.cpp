#include "observer.h"

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