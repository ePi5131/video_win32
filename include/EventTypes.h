#pragma once

struct MouseEvent {
  enum class Kind {
    Down,
    Up,
    Move
  };

  Kind kind;
  Point pos;
};
