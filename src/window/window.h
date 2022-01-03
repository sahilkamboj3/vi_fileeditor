#include <SDL2/SDL.h>
#include <string>

class window {
public:
  void run();

private:
  SDL_Window *_win = NULL;       // window
  SDL_Surface *_wsurface = NULL; // surface on window
  SDL_Surface *_image = NULL;    // surface for image
  bool _init();
  bool _loadimage(const char *filepath);
  void _blitsurface(SDL_Surface *src, SDL_Surface *dest);
  void _updatewindowsurface();
  void _delay(uint32_t delay);
  void _destroy();
};
