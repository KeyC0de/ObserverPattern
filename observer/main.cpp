#include "observer.h"
#include "subject.h"


int main()
{
	std::unique_ptr<Car> car = std::make_unique<Car>();

	LeftObserver lo{car.get()};
	RightObserver ro{car.get()};

	std::cout << "Press A for left, D for right, c for color, Q to quit\n";

	while ( true )
	{
		char c;
		std::cin >> c;
		switch ( c )
		{
			case 'a':
			case 'A':
				car->setPosition( -1 );
				break;
			case 'c':
			case 'C':
				car->setColor( Color::MAGENTA );
				break;
			case 'd':
			case 'D':
				car->setPosition( 1 );
				break;
			case 'Q':
			case 'q':
				goto _BREAK_OFF_LOOP;
				break;
			default:
				break;
		}
	}
_BREAK_OFF_LOOP:
	return 0;
}