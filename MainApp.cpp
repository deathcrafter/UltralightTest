#include "MainApp.h"
#include "Mica.h"

namespace winrt {
}

#define APP_WIDTH 400
#define APP_HEIGHT 60

MainApp::MainApp() {
	Settings settings = Settings();
	settings.app_name = "UltralightTest";
	settings.developer_name = "deathcrafter";
	//settings.force_cpu_renderer = true;

	Config config = Config();
	config.user_stylesheet = "html, body { background: trnsparent; }";

	app_ = App::Create(settings, config);

	auto main_monitor = app_->main_monitor();
	
	window_ = Window::Create(main_monitor, APP_WIDTH, APP_HEIGHT, false, kWindowFlags_Borderless | kWindowFlags_Hidden);
	window_->SetTitle("Ultralight Test");

	hwnd_ = (HWND)(window_->native_handle());
	//SetWindowLong(hwnd_, GWL_EXSTYLE, GetWindowLong(hwnd_, GWL_EXSTYLE) | WS_EX_COMPOSITED);

	//auto mica = Mica(hwnd_);

	ShowWindow(hwnd_, SW_SHOW);

	ViewConfig vwCfg = ViewConfig{
		main_monitor->display_id(), // display_id
	};
	vwCfg.initial_device_scale = window_->scale();
	vwCfg.is_accelerated = window_->is_accelerated();
	vwCfg.is_transparent = true;
	vwCfg.user_agent = "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/130.0.0.0 Safari/537.36";

	auto vwSession = app_->renderer()->CreateSession(true, "UltralightTestSession");

	view_ = app_->renderer()->CreateView(APP_WIDTH, APP_HEIGHT, vwCfg, vwSession);

	overlay_ = Overlay::Create(window_, view_, 0, 0);

	//overlay_ = Overlay::Create(window_, APP_WIDTH, APP_HEIGHT, 0, 0);

	overlay_->Resize(window_->width(), window_->height());

	overlay_->view()->LoadURL("file:///apps/test/index.html");
}

void MainApp::Run()
{
	app_->Run();
}

MainApp::~MainApp() {
	app_->Quit();
}
