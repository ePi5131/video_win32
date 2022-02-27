#include <Windows.h>
#include "Timeline.h"

void Timeline::intialize(HWND hwnd) {
  HDC hdc = GetDC(hwnd);

  bitmap = CreateCompatibleBitmap(hdc, TIMELINE_BMP_WIDTH, TIMELINE_BMP_HEIGHT);
  buffer = CreateCompatibleDC(hdc);

  SelectObject(buffer, bitmap);
  SelectObject(buffer, GetStockObject(NULL_PEN));

  ReleaseDC(hwnd, hdc);
}

Timeline::~Timeline() {
  DeleteObject(bitmap);
  DeleteDC(buffer);
}

void Timeline::draw(HDC dest, Point drawpos) {

  // background
  PatBlt(buffer, 0, 0, TIMELINE_BMP_WIDTH, TIMELINE_BMP_HEIGHT, BLACKNESS);

  

  BitBlt(
    dest,
    drawpos.x, drawpos.y,
    TIMELINE_BMP_WIDTH, TIMELINE_BMP_HEIGHT,
    buffer,
    0, 0,
    SRCCOPY
  );
}

void Timeline::mouse_down(MouseEvent e) {

}

void Timeline::mouse_move(MouseEvent e) {

}

void Timeline::mouse_up(MouseEvent e) {

}