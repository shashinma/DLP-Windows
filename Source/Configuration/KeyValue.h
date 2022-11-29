#ifndef DLPSYSTEM_KEYVALUE_H
#define DLPSYSTEM_KEYVALUE_H

#include <Windows.h>
#include <iostream>


#define RUS 0x0419
#define ENG 0x0409

bool shiftStatement(bool wParam);
void keyValueChecker(PKBDLLHOOKSTRUCT keystroke, WPARAM wParam);

#endif //DLPSYSTEM_KEYVALUE_H
