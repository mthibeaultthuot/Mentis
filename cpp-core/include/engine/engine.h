

class Engine {
public:
  Engine();

  static Engine &getInstance();
  int Add(int x, int y);

  Engine(Engine const &) = delete;
  void operator=(Engine const &) = delete;
};
