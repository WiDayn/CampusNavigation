/*****************************************************************//**
 * \file   Logger.h
 * \author WiDAYN
 * \date   10 April 2022
 *********************************************************************/
#pragma once
#include "StringUtils.h"
#include <string>
#include <iostream>

class Logger
{
public:
	static void log(std::string s);
	static void logSuccess(std::string s);
	static void logInfo(std::string s);
	static void logWarn(std::string s);
	static void logFail(std::string s);
	static void writeToFile(std::string s);
};
