1. Linked the include/ and lib/ directories for sdl2 and sdl2_image to the local instances
2. Rendering:
    a. Copying image using textures and renderer.
        Load the image into a surface.
                     v
        Create renderer(represents the graphics card) that will draw to the window.
                     v
        Create a texture that maps from the surface.
                     v
        Copy the texture onto the renderer and allow the renderer to draw to the
        window.

        ex)
         SDL_Renderer *renderer = SDL_CreateRenderer(
             window, -1, 0); // create our renderer that will draw to the window
         SDL_Texture *texture = SDL_CreateTextureFromSurface(
             renderer, image); // create texture that will go onto renderer
         SDL_RenderCopy(renderer, texture, NULL,
                        NULL);        // copy the texture onto the renderer
         SDL_RenderPresent(renderer); // let the renderer draw to the window
    b. Blit surfaces.
        Load the image into a surface.
                     v
        Get the surface of the window.
                     v
        Blits the image surface onto the window surface.
                     v
        Update the window surface.
        
        ex)
         SDL_Surface *image = loadimagesurface(filepath);
         SDL_Surface *wsurface = getwindowsurface(window);
         blitsurface(image, wsurface);
         updatewindow(window);

