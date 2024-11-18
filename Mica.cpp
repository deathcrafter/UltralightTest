#include "Mica.h"
#include "Utilities.h"


Mica::Mica(HWND hWnd)
{
	hWnd_ = hWnd;

	if (!hWnd_) return;

	// set the extended window style as WS_EX_COMPOSITED. [Ref](https://learn.microsoft.com/en-us/windows/win32/winmsg/extended-window-styles)
	SetWindowLong(hWnd_, GWL_EXSTYLE, GetWindowLong(hWnd_, GWL_EXSTYLE) | WS_EX_COMPOSITED);

	// initialize winrt instance
	winrt::init_apartment();

	// get a reference to Windows App SDK since it is an unpackaged app
	Utilities::WindowsAppSDKBootstrapperContext sdkContext;

	// Mica requires a compositor, which also requires a dispatcher queue
	auto controller = Utilities::CreateDispatcherQueueControllerForCurrentThread();

	compositor_ = winrt::Compositor();

	// The Mica controller needs to set a target with a root to recognize the visual base layer
	SetWindowTarget();

	// Need to set a root before we can enable Mica.
	target_.Root(compositor_.CreateContainerVisual());

	mica_controller_ = winrt::MicaController();

	is_supported_ = mica_controller_.SetTarget(winrt::Microsoft::UI::WindowId{ reinterpret_cast<uint64_t>(hWnd_) }, target_);
}

void Mica::SetWindowTarget()
{
	namespace abi = ABI::Windows::UI::Composition::Desktop;

	auto interop = compositor_.as<abi::ICompositorDesktopInterop>();
	winrt::Windows::UI::Composition::Desktop::DesktopWindowTarget target{ nullptr };
	winrt::check_hresult(interop->CreateDesktopWindowTarget(hWnd_, true, reinterpret_cast<abi::IDesktopWindowTarget**>(winrt::put_abi(target))));
	
	target_ = target;
}
