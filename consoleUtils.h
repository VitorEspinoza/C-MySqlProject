#include <windows.h>
HANDLE hConsole;

void initHConsole() {
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
}

setErrorColorTextConsole() {
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
}

setDetachColorTextConsole() {
	SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE);
}

setDefaultColorTextConsole() {
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}

setWarningColorTextConsole() {
  SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN);
}

setSuccessColorTextConsole() {
	SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
}
