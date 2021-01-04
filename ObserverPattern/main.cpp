#include <iostream>
#include "observer.h"
#include "subject.h"

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
	std::wcout << conFont
		<< L"\nnFont="
		<< cfi.nFont
		<< L"fontSize=("
		<< cfi.dwFontSize.X
		<< L','
		<< cfi.dwFontSize.Y
		<< L")\n";
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
    auto SetConsoleFont = (SETCONSOLEFONT) GetProcAddress(LoadLibraryW(L"KERNEL32"),
		"SetConsoleFont");
	auto font = getFontFamily( h );
	std::wcout << L"nConsoleFonts="
		<< GetNumberOfConsoleFonts()
		<< L"fontName="
		<< font
		<< L'\n';
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
	_setmode( _fileno( stdout ), _O_U16TEXT );
	_setmode( _fileno( stderr ), _O_U16TEXT );
	_setmode( _fileno( stdin ), _O_U16TEXT );
	// use w-streams for interaction with the console
	// use regular streams for interaction with files
#	pragma endregion
#endif
	std::ios_base::sync_with_stdio( false );
	// program:...

	Car car = Car{};

	LeftObserver lo{&car};
	RightObserver ro{&car};

	std::wcout << L"Press A for left, D for right, c for color, Q to quit\n";

	while ( true )
	{
		wchar_t c;
		std::wcin >> c;
		switch ( c )
		{
			case L'a':
			case L'A':
				car.setPosition( -1 );
				break;
			case L'c':
			case L'C':
				car.setColor( Color::MAGENTA );
				break;
			case L'd':
			case L'D':
				car.setPosition( 1 );
				break;
			case L'Q':
			case L'q':
				goto _BREAK_OFF_LOOP;
				break;
			default:
				break;
		}
	}
_BREAK_OFF_LOOP:
	return 0;
}