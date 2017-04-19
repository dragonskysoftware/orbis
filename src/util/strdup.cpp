/*
 * strdup.cpp
 * Implements functions that duplicate character strings
 * Created by Andrew Davis
 * Created on 4/9/2017
 * All rights reserved
 */

//include header
#include "strdup.h"

//strdup function implementation - duplicates a character string
char* strdup(const char* str) noexcept {
	size_t len = strlen(str) + 1; //get the length of the supplied string plus one
	char* ret = new char[len]; //allocate a character string with the calculated length
	strcpy(ret, str); //copy in the supplied string
	return ret; //return the duplicated, initialized string
}

//C_strdup function implementation - duplicates a character string C style
char* C_strdup(const char* str) noexcept {
	size_t len = strlen(str) + 1; //get the length of the supplied string plus one
	char* ret = (char*)SDL_malloc(len * sizeof(char)); //allocate a character string with the calculated length
	if(ret) { //if the allocation succeeded
		strcpy(ret, str); //then copy in the supplied string
	}
	return ret; //return the duplicated, initialized string
}

//end of implementation
