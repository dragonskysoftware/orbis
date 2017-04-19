/*
 * strdup.h
 * Declares functions that duplicate character strings
 * Created by Andrew Davis
 * Created on 4/9/2017
 * All rights reserved
 */

//disallow reinclusion
#ifndef STRDUP_H_INC
#define STRDUP_H_INC

//include
#include <SDL2/SDL.h>
#include <cstring>
#include <cstdlib>

//function declarations

//strdup function - duplicates a string C++ style
char* strdup(const char* str) noexcept;

//C_strdup function - duplicates a string C style
char* C_strdup(const char* str) noexcept;

#endif
