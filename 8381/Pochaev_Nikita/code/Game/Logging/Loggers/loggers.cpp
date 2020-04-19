﻿#include "loggers.h"

std::ostream& operator<< (std::ostream &out, ILogger &log)
{
    out << log.getTime() << " << " << log.getLogInf();
    return out;
}


/*      TERMINAL LOGGER      */

TerminalLogger::TerminalLogger()
{
    time = std::make_shared<Time>();
}

TerminalLogger::~TerminalLogger()
{
    printProgWorkingTime();
    std::cout << ANSIColor::coloredString("Logger stopped working", ANSIColor::FG_GREEN) << std::endl;
}

eLOGGER_TYPE TerminalLogger::getType()
{
    return TERMINAL_LOG;
}

bool TerminalLogger::isActive()
{
    return true;
}

void TerminalLogger::printLog(std::string outInf)
{
    logInf = outInf;
    print();
}

void TerminalLogger::print()
{
    std::cout << this << std::endl;
}

void TerminalLogger::printCurrTime()
{
    std::cout << time << std::endl;
}

void TerminalLogger::printProgWorkingTime()
{
    std::cout << ANSIColor::coloredString("Program was working for " + time->getProgWorkTime() + " seconds.", ANSIColor::FG_GREEN) << std::endl;
}

std::shared_ptr<Time>& TerminalLogger::getTime()
{
    return time;
}

std::string TerminalLogger::getLogInf() const
{
    return logInf;
}


/*      FILE LOGGER      */

FileLogger::~FileLogger()
{
    printProgWorkingTime();
    fout << "Logger stopped working" << std::endl;
    fout.close();
}

FileLogger::FileLogger()
{
    std::string pathString = QDir::currentPath().toStdString();
    fout.open(pathString + "\\LOG.log", std::ofstream::trunc);
    if(!fout.is_open())
    {
        throw std::runtime_error("Unable to open log file");
    }

    time = std::make_shared<Time>();
}

eLOGGER_TYPE FileLogger::getType()
{
    return FILE_LOG;
}

bool FileLogger::isActive()
{
    return true;
}

void FileLogger::printLog(std::string outInf)
{
    logInf = outInf;
    print();
}

void FileLogger::print()
{
    fout << this << std::endl;
}

void FileLogger::printCurrTime()
{
    fout << time << std::endl;
}

void FileLogger::printProgWorkingTime()
{
    fout << "Program was working for " + time->getProgWorkTime() + " seconds."<< std::endl;
}

std::shared_ptr<Time>& FileLogger::getTime()
{
    return time;
}

std::string FileLogger::getLogInf() const
{
    return logInf;
}


/*      PROXY LOGGER      */

ProxyLogger::ProxyLogger(eLOGGER_TYPE loggerType)
{
    if(loggerType == TERMINAL_LOG)
    {
        logger = std::make_shared<TerminalLogger>();
    }
    else if(loggerType == FILE_LOG)
    {
        logger = std::make_shared<FileLogger>();
    }
    else
    {
        logger = nullptr;
    }
}

eLOGGER_TYPE ProxyLogger::getType()
{
    if(logger)
    {
        return logger->getType();
    }
    else
    {
        return NO_LOG;
    }
}

bool ProxyLogger::isActive()
{
    if(logger)
    {
        return logger->isActive();
    }
    else
    {
        return false;
    }
}

void ProxyLogger::printLog(std::string outInf)
{
    if(logger)
    {
        logger->printLog(outInf);
    }
}

void ProxyLogger::print()
{
    if(logger)
    {
        logger->print();
    }
}

void ProxyLogger::printCurrTime()
{
    if(logger)
    {
        logger->printCurrTime();
    }
}

void ProxyLogger::printProgWorkingTime()
{
    if(logger)
    {
        logger->printProgWorkingTime();
    }
}

std::shared_ptr<Time>& ProxyLogger::getTime()
{
    if(logger)
    {
        return logger->getTime();
    }
}

std::string ProxyLogger::getLogInf() const
{
    if(logger)
    {
        return logger->getLogInf();
    }
    else
    {
        return nullptr;
    }
}
