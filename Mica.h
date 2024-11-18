#pragma once
#include <Windows.h>
#include <Windows.UI.Composition.Interop.h>
#include <winrt/Windows.UI.Composition.Desktop.h>
#include <winrt/Microsoft.UI.Composition.SystemBackdrops.h>


namespace winrt {
	using namespace Microsoft::UI::Composition::SystemBackdrops;
	using namespace Windows::UI::Composition;
	using namespace Windows::UI::Composition::Desktop;
}

class Mica
{
public:
	Mica(HWND hWnd);
	bool is_supported() { return is_supported_; }

protected:
	HWND hWnd_;
	winrt::Compositor compositor_{ nullptr };
	winrt::DesktopWindowTarget target_{ nullptr };
	winrt::MicaController mica_controller_{ nullptr };
	bool is_supported_ = false;

	void SetWindowTarget();
};

