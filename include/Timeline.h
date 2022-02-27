#pragma once

#define  TIMELINE_BMP_WIDTH   1200
#define  TIMELINE_BMP_HEIGHT  600

#include "Types.h"
#include "EventTypes.h"

class Timeline {
  HBITMAP bitmap;
  HDC     buffer;

public:
  Timeline() = default;
  Timeline(Timeline&&) = delete;
  Timeline(Timeline const&) = delete;
  ~Timeline();

  void intialize(HWND);
  void draw(HDC dest, Point drawpos);

  void mouse_down(MouseEvent);
  void mouse_move(MouseEvent);
  void mouse_up(MouseEvent);
};
