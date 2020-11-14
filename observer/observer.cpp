#include <iostream>
#include "observer.h"
#include "subject.h"


IObserver::IObserver( class Car* subject )
	:
	m_pSubject{subject} 
{}

IObserver::~IObserver() noexcept
{
	m_pSubject->unsubscribe( this );
}

IObserver::IObserver( IObserver&& rhs ) noexcept
	:
	m_pSubject{std::move( rhs.m_pSubject )}
{}

IObserver& IObserver::operator=( IObserver&& rhs ) noexcept
{
	if ( this != &rhs )
	{
		std::swap( this->m_pSubject, rhs.m_pSubject );
	}
	return *this;
}

LeftObserver::LeftObserver( class Car* subject )
	:
	IObserver{subject}
{
	subject->subscribe( this );			// CAN ALSO SUBSCRIBE TO A MESSAGE TYPE
}

void LeftObserver::update() const noexcept
{
	std::wcout << L"Car turned left\n";
}

RightObserver::RightObserver( class Car* subject )
	:
	IObserver{subject}
{
	subject->subscribe( this );
}

void RightObserver::update() const noexcept
{
	std::wcout << L"Car turned right\n";
}
