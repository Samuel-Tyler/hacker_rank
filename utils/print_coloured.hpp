#pragma once

#include <iostream>
#include <string>

#ifdef __linux__
enum class Console_colour : int {
    FG_DEFAULT = 39,
    FG_BLACK = 30,
    FG_RED = 31,
    FG_GREEN = 32,
    FG_YELLOW = 33,
    FG_BLUE = 34,
    FG_MAGENTA = 35,
    FG_CYAN = 36,
    FG_LIGHT_GRAY = 37,
    FG_DARK_GRAY = 90,
    FG_LIGHT_RED = 91,
    FG_LIGHT_GREEN = 92,
    FG_LIGHT_YELLOW = 93,
    FG_LIGHT_BLUE = 94,
    FG_LIGHT_MAGENTA = 95,
    FG_LIGHT_CYAN = 96,
    FG_WHITE = 97,
    BG_RED = 41,
    BG_GREEN = 42,
    BG_BLUE = 44,
    BG_DEFAULT = 49
};

template <typename T>
void print_coloured(const T& info, Console_colour colour)
{
    std::cout << "\033[" << static_cast<int>(colour) << "m" <<info << "\033[" << static_cast<int>(Console_colour::FG_DEFAULT) << 'm';
}
#elif _WIN32
#include <windows.h>

enum class Console_colour : WORD {
    //   FG_DEFAULT
    FG_BLACK = FOREGROUND_INTENSITY,
    FG_RED = FOREGROUND_INTENSITY | FOREGROUND_RED,
    FG_GREEN = FOREGROUND_INTENSITY | FOREGROUND_GREEN,
    FG_YELLOW = FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_RED,
    FG_BLUE = FOREGROUND_INTENSITY | FOREGROUND_BLUE,
    FG_MAGENTA = FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_RED,
    FG_CYAN = FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_GREEN,
    FG_WHITE = FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED,
    FG_LIGHT_RED = FOREGROUND_RED,
    FG_LIGHT_GREEN = FOREGROUND_GREEN,
    FG_LIGHT_YELLOW = FOREGROUND_GREEN | FOREGROUND_RED,
    FG_LIGHT_BLUE = FOREGROUND_BLUE,
    FG_LIGHT_MAGENTA = FOREGROUND_BLUE | FOREGROUND_RED,
    FG_LIGHT_CYAN = FOREGROUND_BLUE | FOREGROUND_GREEN,
};

template <typename T>
void print_coloured(const T& info, Console_colour colour)
{
    WORD Attributes = 0;
    CONSOLE_SCREEN_BUFFER_INFO Info;
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleScreenBufferInfo(hStdout, &Info);
    Attributes = Info.wAttributes;
    SetConsoleTextAttribute(hStdout, static_cast<WORD>(colour));
    std::cout << info;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Attributes);
}

#else

enum class Console_colour : int {
    FG_DEFAULT = 39,
    FG_BLACK = 30,
    FG_RED = 31,
    FG_GREEN = 32,
    FG_YELLOW = 33,
    FG_BLUE = 34,
    FG_MAGENTA = 35,
    FG_CYAN = 36,
    FG_LIGHT_GRAY = 37,
    FG_DARK_GRAY = 90,
    FG_LIGHT_RED = 91,
    FG_LIGHT_GREEN = 92,
    FG_LIGHT_YELLOW = 93,
    FG_LIGHT_BLUE = 94,
    FG_LIGHT_MAGENTA = 95,
    FG_LIGHT_CYAN = 96,
    FG_WHITE = 97,
    BG_RED = 41,
    BG_GREEN = 42,
    BG_BLUE = 44,
    BG_DEFAULT = 49
};

template <typename T>
void print_coloured(const T& info, Console_colour)
{
    std::cout << info;
}
#endif
