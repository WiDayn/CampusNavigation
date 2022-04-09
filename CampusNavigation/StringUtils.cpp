/*****************************************************************//**
 * \file   StringUtils.cpp
 * \author WiDAYN
 * \date   10 April 2022
 *********************************************************************/
#include "StringUtils.h"
#pragma warning(disable:4996)

std::string StringUtils::getTime()
{
	time_t t = time(0);
	struct tm* now = localtime(&t);

	std::stringstream time;

	time << now->tm_year + 1900 << "Äê";
	time << now->tm_mon + 1 << "ÔÂ";
	time << now->tm_mday << "ÈÕ ";
	time << now->tm_hour << ":";
	time << now->tm_min << ":";
	time << now->tm_sec;

	return time.str();
}
