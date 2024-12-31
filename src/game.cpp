#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_float4x4.hpp"
#include "sys.h"
#include <chrono>
#include <random>
#include "imgui/imgui.h"
#include "imgui/imgui_impl_sdl2.h"
#include "imgui/imgui_impl_opengl3.h"

namespace game {

    MenuState menuState;
    GameState gameState;

    std::mt19937 _mrand;

    //Level level;

    void init() {

        _mrand = std::mt19937(std::chrono::steady_clock::now().time_since_epoch().count());

        render::texture::createTextureFromFile("player", "data/textures/player.png");
        render::texture::createTextureFromFile("player_float", "data/textures/player_float.png");
        render::texture::createTextureFromFile("player_speed", "data/textures/player_speed.png");
        render::texture::createTextureFromFile("spike", "data/textures/spikes.png");
        render::texture::createTextureFromFile("bg01", "data/textures/bg01.png"); // 64
        render::texture::createTextureFromFile("bg02", "data/textures/bg02.png"); // 32
        render::texture::createTextureFromFile("bg03", "data/textures/bg03.png"); // 16
        render::texture::createTextureFromFile("bg04", "data/textures/bg04.png"); // 0
        render::texture::createTextureFromFile("coin_pt1", "data/textures/Coin_pt1.png");
        render::texture::createTextureFromFile("coin_pt5", "data/textures/Coin_pt5.png");
        render::texture::createTextureFromFile("coin_pt10", "data/textures/Coin_pt10.png");
        render::texture::createTextureFromFile("heart", "data/textures/heart.png");
        render::texture::createTextureFromFile("title_text", "data/textures/title_text.png");
        
        render::font::createFont("regular", "data/font/font.ttf", 48);

        sound::addSoundFXStream("coins", "data/sound/sfx/coins.wav");
        sound::addSoundFXStream("damage", "data/sound/sfx/damaged.wav");
        sound::addSoundFXStream("damage2", "data/sound/sfx/damage2.wav");
        sound::addSoundFXStream("heart", "data/sound/sfx/heart.wav");
        sound::addSoundFXStream("select", "data/sound/sfx/select.wav");

        sound::addSoundFXStream("one", "data/sound/sfx/one.wav");
        sound::addSoundFXStream("two", "data/sound/sfx/two.wav");
        sound::addSoundFXStream("three", "data/sound/sfx/three.wav");
        
        sound::addSoundFXStream("you_win", "data/sound/sfx/you_win_congrats.wav");
        sound::addSoundFXStream("game_set", "data/sound/sfx/game_set_aka_0.wav");

        sound::addSoundFXStream("you_loose", "data/sound/sfx/you_loose.wav");
        sound::addSoundFXStream("you_loose_ack", "data/sound/sfx/you_loose/ack.wav");
        sound::addSoundFXStream("you_loose_fart", "data/sound/sfx/you_loose/fart-with-reverb.wav");

        //level.init();
        // Implement ImGui
        IMGUI_CHECKVERSION();

        ImGui::CreateContext();

        ImGuiIO& io = ImGui::GetIO();

        ImGui::StyleColorsDark();

        ImGui_ImplSDL2_InitForOpenGL(app::getWindow(), app::getContext());
        ImGui_ImplOpenGL3_Init("#version 400");

        state::addState("menu", &menuState);
        state::addState("game", &gameState);

        state::setDefaultState("menu");

        state::init();
    }

    void handleEvent(SDL_Event* e) {
        //level.handleEvent(e);
        ImGui_ImplSDL2_ProcessEvent(e);

        state::handleEvent(e);
    }

    void update(float delta) {
        //level.update(delta);
        state::update(delta);
    }

    void render() {
        render::clear(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
        render::bind();

        render::projection(glm::ortho(0.0f, (float)app::getWidth(), (float)app::getHeight(), 0.0f, -1024.0f, 1024.0f));
        render::view(glm::mat4(1.0f));

        //level.render();
        state::render();

        render::unbind();
    }

    void release() {
        //level.release();
        state::release();

        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplSDL2_Shutdown();
        ImGui::DestroyContext();
    }

    uint32_t m_rand() {
        return _mrand();
    }
}