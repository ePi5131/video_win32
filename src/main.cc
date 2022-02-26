#include "videoe.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
  std::vector<std::wstring> args;
  std::wstring arg;

  for( CHAR* c = lpCmdLine; *c; c++ ) {
    if( *c == ' ' ) {
      args.emplace_back(arg);
      continue;
    }

    arg += *c;
  }

  return Application(hInstance).main(args);
}
