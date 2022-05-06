/*****************************************************************//**
 * \file   Logger.cpp
 * \author WiDAYN
 * \date   10 April 2022
 *********************************************************************/
#include "Logger.h"

void Logger::log(std::string s)
{
	std::cout << s << std::endl;
}

void Logger::logSuccess(std::string s)
{
	std::cout << "\033[32m" << "[" << StringUtils::getTime() << " SUCCESS]" << s << "\033[0m" << std::endl;
}

void Logger::logInfo(std::string s)
{
	std::cout << "\033[34m" << "[" << StringUtils::getTime() << " INFO]" << s << "\033[0m" << std::endl;
}

void Logger::logWarn(std::string s)
{
	std::cout << "\033[33m" << "[" << StringUtils::getTime() << " WARN]" << s << "\033[0m" << std::endl;
}

void Logger::logFail(std::string s)
{
	std::cout << "\033[31m" << "[" << StringUtils::getTime() << " FAIL]" << s << "\033[0m" << std::endl;
}

void Logger::writeToFile(std::string s)
{
	std::cout << "\033[31m" << "[" << StringUtils::getTime() << "]" << s << "\033[0m" << std::endl;
}
