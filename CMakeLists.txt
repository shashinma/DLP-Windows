cmake_minimum_required(VERSION 3.23)
project(DLPSystem)

set(CMAKE_CXX_STANDARD 20)

add_executable(DLPSystem Source/Modules/Keylogger.cpp Source/Secure/ActivitySecure.cpp Source/Core/Core.cpp Source/Controllers/ThreadsController.cpp Source/Configuration/KeyValue.cpp Source/Configuration/KeyValue.h main.cpp Source/Modules/Keylogger.h Source/Controllers/ThreadsController.h Source/Core/Core.h Source/Modules/AutoRun.cpp Source/Modules/AutoRun.h Source/Modules/TaskManagerAnalyzer.cpp Source/Modules/TaskManagerAnalyzer.h Source/Secure/ActivitySecure.h)
