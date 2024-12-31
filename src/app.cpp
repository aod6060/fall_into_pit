#include "SDL.h"
#include "SDL_events.h"
#include "SDL_timer.h"
#include "SDL_video.h"
#include "sys.h"


namespace app {
    std::string caption = "Fall into Pit!";
    uint32_t screen_width = 640;
    uint32_t screen_height = 480;

    SDL_Window* g_window = nullptr;
    SDL_GLContext g_context = nullptr;

    bool g_running = true;

    SDL_Event g_event;

    uint32_t pre_time = 0;
    uint32_t curr_time = 0;
    float delta = 0.0f;

    int app_main(int argc, char** argv) {
        SDL_Init(SDL_INIT_EVERYTHING);

        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);


        g_window = SDL_CreateWindow(
            caption.c_str(), 
            SDL_WINDOWPOS_UNDEFINED, 
            SDL_WINDOWPOS_UNDEFINED, 
            screen_width, 
            screen_height, 
            SDL_WINDOW_OPENGL);

        g_context = SDL_GL_CreateContext(g_window);
        glewInit();

        input::init();
        render::init();
        sound::init();
        gui::init();

        game::init();

        pre_time = SDL_GetTicks();

        while(g_running) {
            curr_time = SDL_GetTicks();
            delta = (curr_time - pre_time) / 1000.0f;
            pre_time = curr_time;

            while(SDL_PollEvent(&g_event)) {
                if(g_event.type == SDL_QUIT) {
                    g_running = false;
                }

                input::handleEvent(&g_event);

                game::handleEvent(&g_event);
            }

            game::update(delta);
            game::render();

            input::update();

            SDL_GL_SwapWindow(g_window);
        }

        game::release();

        gui::release();
        
        sound::release();
        render::release();
        input::release();

        SDL_GL_DeleteContext(g_context);
        SDL_DestroyWindow(g_window);

        SDL_Quit();
        return 0;
    }

    uint32_t getWidth() {
        return screen_width;
    }

    uint32_t getHeight() {
        return screen_height;
    }

    float getAspect() {
        return (float)screen_width / (float)screen_height;
    }

    void exit() {
        g_running = false;
    }

    SDL_Window* getWindow() {
        return g_window;
    }

    SDL_GLContext getContext() {
        return g_context;
    }
}