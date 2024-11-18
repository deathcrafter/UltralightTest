#pragma once
#include <Windows.h>
#include <AppCore/AppCore.h>
#include <Ultralight/View.h>

using namespace ultralight;

class MainApp
{
public:
	MainApp();
	~MainApp();
	void Run();
protected:
	HWND hwnd_;
	RefPtr<App> app_;
	RefPtr<Window> window_;
	RefPtr<Overlay> overlay_;
	RefPtr<View> view_;
};
