#ifndef __DISPLAY_H__
    #define __DISPLAY_H__

#include "Color.h"

class display{
    private:
        SDL_Window* window;
        SDL_Renderer* renderer;
    public:
        static bool init();
        static void quit();
        static bool get_init();
        //static Surface* set_mode(dimension, int, int);
        static void set_mode(Dimension, int, int);
        static void blit(Texture*, Point);
        static void fill(Color);
        //static Surface* get_surface();
        static void flip();
        //static void update(Rect*);
        // get_driver
        // info
        // get_wm_info
        // list_modes
        // mode_ok
        // gl_get_attribute
        // gl_set_attribute
        // get_active
        // iconify
        // toggle_fullscreen
        // set_gamma
        // set_gamma_ramp
        static void set_icon(Texture*);
        static void set_caption(string);
        static string get_caption();
        // set_palette
}

#endif