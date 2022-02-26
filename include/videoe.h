#pragma once

#define UNICODE
#include <Windows.h>

#include <iostream>
#include <string>
#include <vector>
#include <memory>

using i8 = int8_t;
using i16 = int16_t;
using i32 = int32_t;
using i64 = int64_t;

using u8 = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;

inline constexpr u32 TIMELINE_BMP_WIDTH  = 2000;
inline constexpr u32 TIMELINE_BMP_HEIGHT = 1000;

struct Point {
  i64 x;
  i64 y;
};

struct Size {
  i64 width;
  i64 height;
};

struct MouseEvent {
  enum class Kind {
    Down,
    Up,
    Move
  };

  Kind kind;
  Point pos;
};

class Timeline {
  HBITMAP bitmap;
  HDC     buffer;

public:
  explicit Timeline(HWND);
  ~Timeline();

  Timeline(Timeline&&) = delete;
  Timeline(Timeline const&) = delete;

  void draw(HDC dest, Point drawpos);

  void mouse_down(MouseEvent);
  void mouse_move(MouseEvent);
  void mouse_up(MouseEvent);
};

class Application {
  HINSTANCE hInstance;
  WINDOWINFO window_info;

  std::unique_ptr<Timeline> timeline;
  Point tl_drawpos; // timeline

public:
  explicit Application(HINSTANCE);
  Application(Application&&) = delete;
  Application(Application const&) = delete;

  LRESULT CALLBACK wnd_proc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp);

  int main(std::vector<std::wstring> args);
};
