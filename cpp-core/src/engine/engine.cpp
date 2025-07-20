#include "engine/engine.h"

Engine::Engine() {}

int Engine::Add(int x, int y) { return x + y; }

Engine &Engine::getInstance() {
  static Engine instance;
  return instance;
}
