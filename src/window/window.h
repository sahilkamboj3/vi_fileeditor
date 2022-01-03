#include <SDL2/SDL.h>
#include <string>

namespace window {
class Window {
public:
  void Run();
  void RunPythonScript(const std::string &filepath);

private:
  bool _Init();
  void _CreateSurface(SDL_Window *&window);
  void _Destroy(SDL_Window *&window);
};
} // namespace window
