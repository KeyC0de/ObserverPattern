#include <iostream>
#include "observer.h"
#include "subject.h"
#if defined _DEBUG && !defined NDEBUG
#	pragma comment( lib, "C:/Program Files (x86)/Visual Leak Detector/lib/Win64/vld.lib" )
#	include <C:/Program Files (x86)/Visual Leak Detector/include/vld.h>
#endif

#if defined _WIN32 || defined _MSC_VER
#	pragma region WIN_CONSOLE
#	include <windows.h>
#	include <io.h>
#	include <fcntl.h>
static DWORD getFontFamily( HANDLE h )
{
	CONSOLE_FONT_INFO cfi;
	BOOL conFont = GetCurrentConsoleFont( h,
		false,
		&cfi );
	std::cout << conFont
		<< "\nnFont="
		<< cfi.nFont
		<< "fontSize=("
		<< cfi.dwFontSize.X
		<< ','
		<< cfi.dwFontSize.Y
		<< ")\n";
	return conFont ? cfi.nFont
		: -1;
}

void getConsoleInfo( HANDLE h )
{
	using GETNUMBEROFCONSOLEFONTS = DWORD (WINAPI* )();
	using SETCONSOLEFONT = BOOL (WINAPI*)( HANDLE hConOut, DWORD nFont );
	auto GetNumberOfConsoleFonts =
		(GETNUMBEROFCONSOLEFONTS) GetProcAddress( LoadLibraryW( L"KERNEL32" ),
		"GetNumberOfConsoleFonts" );
	auto setConsoleFont = (SETCONSOLEFONT) GetProcAddress( LoadLibraryW( L"KERNEL32" ),
		"SetConsoleFont");
	(void)setConsoleFont;
	auto font = getFontFamily( h );
	std::cout << "nConsoleFonts="
		<< GetNumberOfConsoleFonts()
		<< "fontName="
		<< font
		<< '\n';
}
#	pragma endregion
#endif


int main()
{
	fflush( stdout );
#if defined _WIN32 || defined _MSC_VER
#	pragma region UNICODE_SUPPORT
	// change code page to UTF-8 UNICODE
	if ( !IsValidCodePage( CP_UTF8 ) )
	{
		return GetLastError();
	}
	if ( !SetConsoleCP( CP_UTF8 ) )
	{
		return GetLastError();
	}
	if ( !SetConsoleOutputCP( CP_UTF8 ) )
	{
		return GetLastError();
	}
	
	// change console font - post Windows Vista only
	HANDLE hStdOut = GetStdHandle( STD_OUTPUT_HANDLE );
	CONSOLE_FONT_INFOEX cfie;
	const auto sz = sizeof( CONSOLE_FONT_INFOEX );
	ZeroMemory( &cfie, sz );
	cfie.cbSize = sz;
	cfie.dwFontSize.Y = 14;
	wcscpy_s( cfie.FaceName,
		L"Lucida Console" );
	SetCurrentConsoleFontEx( hStdOut,
		false,
		&cfie );

	getConsoleInfo( hStdOut );
	// change file stream translation mode
#	pragma endregion
#endif
	
	/// program:...
	Car car = Car{};

	LeftObserver lo{&car};
	RightObserver ro{&car};

	std::cout << "Press A for left, D for right, c for color, Q to quit\n";

	while ( true )
	{
		char c;
		std::cin >> c;
		switch ( c )
		{
			case 'a':
			case 'A':
				car.setPosition( -1 );
				break;
			case 'c':
			case 'C':
				car.setColor( Color::MAGENTA );
				break;
			case 'd':
			case 'D':
				car.setPosition( 1 );
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