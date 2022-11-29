#include "TaskManagerAnalyzer.h"

std::list<std::string> trustedApps();

void trustedList(){

}

class SmartHandle{
public:
    SmartHandle(HANDLE handle){
        _handle = handle;
    }
    ~SmartHandle(){
        if(_handle){
            CloseHandle(_handle);
        }
    }

    operator bool(){
        return _handle != NULL;
    }

    operator HANDLE(){
        return _handle;
    }

    HANDLE handle(){
        return _handle;
    }
private:
    HANDLE _handle = NULL;
};

struct ProcessInfo {
    PROCESSENTRY32 pe;
    std::vector<THREADENTRY32> threads;
};

int startTaskManagerAnalyzer(){
    SmartHandle processSnap(CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0));
    SmartHandle threadSnap(CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0));

    if (!processSnap || !threadSnap){
        return 1;
    }

    std::vector<ProcessInfo> processInfos;
    std::vector<THREADENTRY32> threads;

    THREADENTRY32 te{ sizeof(THREADENTRY32) };
    if (Thread32First(threadSnap, &te) == FALSE){
        return 2;
    }
    do{
        threads.push_back(te);
    } while (Thread32Next(threadSnap, &te));

    PROCESSENTRY32 pe{ sizeof(PROCESSENTRY32) };
    if (Process32First(processSnap, &pe) == FALSE){
        return 2;
    }
    do{
        std::vector<THREADENTRY32> subThreads;
        for (const auto &thread : threads){
            if (thread.th32OwnerProcessID == pe.th32ProcessID){
                subThreads.push_back(thread);
            }
        }
        processInfos.push_back(ProcessInfo{ pe, subThreads });

    } while (Process32Next(processSnap, &pe));

    for (const auto &processInfo : processInfos){
        tcout << processInfo.pe.szExeFile << std::endl;
        for (const auto &thread : processInfo.threads){
            tcout << "    " << thread.th32ThreadID << std::endl;
        }

        if (!(std::find(trustedList, pe.szExeFile))) std::cout << "error"; // -> logger -> core
    }
    return 0;
}

int startTaskManagerAnalyzerTest()
{
    HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    PROCESSENTRY32 pe;  //хранит информацию о найденом процессе
    if (Process32First(hSnapshot, &pe)) //Поиск первого процесса в снимке
    {
        do
        {
            if (!pe.th32ProcessID) continue;    // Пропуск [System process]
            //Получаем дескриптор процесса
            HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, pe.th32ProcessID);
            char cPriority[18];
            switch (GetPriorityClass(hProcess)) //Получае приоритет процесса
            {
                case HIGH_PRIORITY_CLASS:
                    strcpy(cPriority, "HIGH");
                    break;
                case IDLE_PRIORITY_CLASS:
                    strcpy(cPriority, "LOW");
                    break;
                case NORMAL_PRIORITY_CLASS:
                    strcpy(cPriority, "MIDDLE");
                    break;
                case REALTIME_PRIORITY_CLASS:
                    strcpy(cPriority, "REALTIME");
                    break;
                default:
                    strcpy(cPriority, "HIGH");
            }
            CloseHandle(hProcess);
            //Выводим информацию о процессе
            printf("%25s%6d%18d%18s%12d\n", pe.szExeFile, pe.th32ProcessID,
                                            pe.cntThreads, cPriority, pe.th32ParentProcessID);
        }
        while (Process32Next(hSnapshot, &pe));  //Поиск следущего процесса в снимке
    }
    else printf("error -1");
    CloseHandle(hSnapshot);

    system("PAUSE");
    return 0;
}

/* Закрытие процесса
HANDLE  hProcess = OpenProcess(SYNCHRONIZE, TRUE, inProcessID);

if (NULL != hProcess)
{
WaitForSingleObject(hProcess,INFINITE);
}
*/