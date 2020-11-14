#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include "misc.h"


class Car;

class IObserver 
{
	// perhaps add enum with messages of interest - and subscribe to them all
	class Car* m_pSubject;
public:
	IObserver( class Car* subject );
	virtual ~IObserver() noexcept;

	IObserver( const IObserver& rhs ) = delete;
	IObserver& operator=( const IObserver& rhs ) = delete;
	IObserver( IObserver&& rhs ) noexcept;
	IObserver& operator=( IObserver&& rhs ) noexcept;

	virtual void update() const noexcept = 0;
};

class LeftObserver
	: public IObserver 
{
public:
	LeftObserver( class Car* subject );
	void update() const noexcept override;
};

class RightObserver
	: public IObserver 
{
public:
	RightObserver( class Car* subject );
	void update() const noexcept override;
};
