#pragma once

#include <string>
#include <vector>
#include <memory>
#include "Timeline.h"

class Application {
  HINSTANCE hInstance;
  WINDOWINFO window_info;

  Timeline timeline;
  Point tl_drawpos; // timeline

public:
  explicit Application(HINSTANCE);
  Application(Application&&) = delete;
  Application(Application const&) = delete;

  LRESULT CALLBACK wnd_proc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp);

  int main(std::vector<std::wstring> args);
};