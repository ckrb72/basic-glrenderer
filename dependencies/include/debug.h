#pragma once

#if defined(DEBUG)
#include <iostream>

#define dbglog(va_args) do { std::cout << va_args << std::endl; } while(0)

#define error_log(va_args) do { std::cerr << va_args << std::endl; } while(0)

#else
#define dbglog(va_args) do {} while(0)

#define error_log(va_args) do {} while(0)

#endif