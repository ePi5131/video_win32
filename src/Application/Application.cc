#include <Windows.h>
#include "Application.h"

namespace {
  Application* instance;

  LRESULT CALLBACK wnd_proc_wrap(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) {
    return instance->wnd_proc(hwnd, msg, wp, lp);
  }
}

Application::Application(HINSTANCE hInstance)
  : hInstance(hInstance)
{
  instance = this;
}

LRESULT CALLBACK Application::wnd_proc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) {
	HDC hdc;
	PAINTSTRUCT ps;

	GetWindowInfo(hwnd, &window_info);

	tl_drawpos = {
		0,
		window_info.rcClient.bottom - window_info.rcClient.top - 240
	};

  switch( msg ) {
    case WM_CREATE: {
			timeline.intialize(hwnd);
      break;
    }

    case WM_DESTROY: {
      PostQuitMessage(0);
      break;
    }

		case WM_PAINT: {
			hdc = BeginPaint(hwnd, &ps);
			
			timeline.draw(hdc, tl_drawpos);

			EndPaint(hwnd, &ps);
			break;
		}

    default:
      return DefWindowProc(hwnd, msg, wp, lp);
  }

  return 0;
}

int Application::main(std::vector<std::wstring> args) {
  HWND hwnd;
	MSG msg;
	WNDCLASS winc;

	winc.style		= CS_HREDRAW | CS_VREDRAW;
	winc.lpfnWndProc	= wnd_proc_wrap;
	winc.cbClsExtra	= winc.cbWndExtra	= 0;
	winc.hInstance		= hInstance;
	winc.hIcon		= LoadIcon(NULL, IDI_APPLICATION);
	winc.hCursor		= LoadCursor(NULL, IDC_ARROW);
	winc.hbrBackground	= (HBRUSH)GetStockObject(WHITE_BRUSH);
	winc.lpszMenuName	= NULL;
	winc.lpszClassName	= TEXT("KITTY");

	if( !RegisterClass(&winc) ) {
    return -1;
  }

	hwnd = CreateWindow(
    TEXT("KITTY"), TEXT("Kitty on your lap") ,
    WS_OVERLAPPEDWINDOW | WS_VISIBLE,
    CW_USEDEFAULT, CW_USEDEFAULT,
    CW_USEDEFAULT, CW_USEDEFAULT,
    NULL, NULL,
    hInstance, NULL
	);

	if( hwnd == NULL ) {
    return -1;
  }

	while( GetMessage(&msg, NULL, 0, 0) ) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
  
	return msg.wParam;
}