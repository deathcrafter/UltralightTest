#include <winrt/base.h>
#include "MainApp.h"

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow) {
	MainApp mainApp;

	mainApp.Run();

	return 0;
}