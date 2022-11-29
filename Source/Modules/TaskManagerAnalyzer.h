#ifndef DLPSYSTEM_TASKMANAGERANALYZER_H
#define DLPSYSTEM_TASKMANAGERANALYZER_H

#ifdef UNICODE
#define tcout std::wcout
#else
#define tcout std::wcout
#endif // UNICODE

#include <Windows.h>
#include <tlhelp32.h>

#include <iostream>
#include <vector>
#include <list>

//int startTaskManagerAnalyzer();
int startTaskManagerAnalyzerTest();

//class TaskManagerAnalyzer {
//
//};


#endif //DLPSYSTEM_TASKMANAGERANALYZER_H
