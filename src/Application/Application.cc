#include "videoe.h"

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
      timeline.reset(new Timeline(hwnd));
      break;
    }

    case WM_DESTROY: {
      timeline.reset();
      PostQuitMessage(0);
      break;
    }

    case WM_PAINT: {
      hdc = BeginPaint(hwnd, &ps);
      
      timeline->draw(hdc, tl_drawpos);

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
  WNDCLASS winc {
    .style = CS_HREDRAW | CS_VREDRAW,
    .lpfnWndProc = wnd_proc_wrap,
    .cbClsExtra = 0,
    .cbWndExtra = 0,
    .hInstance = hInstance,
    .hIcon = LoadIcon(NULL, IDI_APPLICATION),
    .hCursor = LoadCursor(NULL, IDC_ARROW),
    .hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH),
    .lpszMenuName = NULL,
    .lpszClassName = TEXT("KITTY")
  };

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
