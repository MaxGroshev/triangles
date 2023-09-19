#ifndef ERROR_CONTR_H
#define ERROR_CONTR_H

//#define MY_DEBUG

#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <cstdlib>
#include "ASSERT.h"
#include "./console_colors.hpp"
#include "./logs_define.h"

//-----------------------------------------------------------------------------------------

#define CUR_POS_IN_PROG __FILE__, __PRETTY_FUNCTION__, __LINE__

//-----------------------------------------------------------------------------------------

int   is_nullptr (const void* ptr);
char* timestamp  ();
int   print_error_message (const char* file_, const char* func_, int line_);
template <class... Args>
int   write_logs (Args... log_text);

#include "./logs.tpp"

#endif
