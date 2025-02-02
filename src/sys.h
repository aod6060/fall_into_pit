#ifndef SYS_H
#define SYS_H



#include "SDL_video.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <functional>
#include <algorithm>
#include <random>
#include <chrono>


#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>


namespace app {
    int app_main(int argc, char** argv);

    uint32_t getWidth();
    uint32_t getHeight();
    float getAspect();

    void exit();

    SDL_Window* getWindow();
    SDL_GLContext getContext();

}

namespace input {
    enum InputState {
        IS_RELEASED = 0,
        IS_PRESSED_ONCE,
        IS_PRESSED,
        IS_RELEASED_ONCE,
        IS_MAX_INPUTSTATE
    };

    enum Keyboard {
        KEYS_UNKNOWN = 0,
        KEYS_A = 4,
        KEYS_B = 5,
        KEYS_C = 6,
        KEYS_D = 7,
        KEYS_E = 8,
        KEYS_F = 9,
        KEYS_G = 10,
        KEYS_H = 11,
        KEYS_I = 12,
        KEYS_J = 13,
        KEYS_K = 14,
        KEYS_L = 15,
        KEYS_M = 16,
        KEYS_N = 17,
        KEYS_O = 18,
        KEYS_P = 19,
        KEYS_Q = 20,
        KEYS_R = 21,
        KEYS_S = 22,
        KEYS_T = 23,
        KEYS_U = 24,
        KEYS_V = 25,
        KEYS_W = 26,
        KEYS_X = 27,
        KEYS_Y = 28,
        KEYS_Z = 29,
        KEYS_1 = 30,
        KEYS_2 = 31,
        KEYS_3 = 32,
        KEYS_4 = 33,
        KEYS_5 = 34,
        KEYS_6 = 35,
        KEYS_7 = 36,
        KEYS_8 = 37,
        KEYS_9 = 38,
        KEYS_0 = 39,
        KEYS_RETURN = 40,
        KEYS_ESCAPE = 41,
        KEYS_BACKSPACE = 42,
        KEYS_TAB = 43,
        KEYS_SPACE = 44,
        KEYS_MINUS = 45,
        KEYS_EQUALS = 46,
        KEYS_LEFTBRACKET = 47,
        KEYS_RIGHTBRACKET = 48,
        KEYS_BACKSLASH = 49,
        KEYS_NONUSHASH = 50,
        KEYS_SEMICOLON = 51,
        KEYS_APOSTROPHE = 52,
        KEYS_GRAVE = 53,
        KEYS_COMMA = 54,
        KEYS_PERIOD = 55,
        KEYS_SLASH = 56,
        KEYS_CAPSLOCK = 57,
        KEYS_F1 = 58,
        KEYS_F2 = 59,
        KEYS_F3 = 60,
        KEYS_F4 = 61,
        KEYS_F5 = 62,
        KEYS_F6 = 63,
        KEYS_F7 = 64,
        KEYS_F8 = 65,
        KEYS_F9 = 66,
        KEYS_F10 = 67,
        KEYS_F11 = 68,
        KEYS_F12 = 69,
        KEYS_PRINTSCREEN = 70,
        KEYS_SCROLLLOCK = 71,
        KEYS_PAUSE = 72,
        KEYS_INSERT = 73,
        KEYS_HOME = 74,
        KEYS_PAGEUP = 75,
        KEYS_DELETE = 76,
        KEYS_END = 77,
        KEYS_PAGEDOWN = 78,
        KEYS_RIGHT = 79,
        KEYS_LEFT = 80,
        KEYS_DOWN = 81,
        KEYS_UP = 82,
        KEYS_NUMLOCKCLEAR = 83,
        KEYS_KP_DIVIDE = 84,
        KEYS_KP_MULTIPLY = 85,
        KEYS_KP_MINUS = 86,
        KEYS_KP_PLUS = 87,
        KEYS_KP_ENTER = 88,
        KEYS_KP_1 = 89,
        KEYS_KP_2 = 90,
        KEYS_KP_3 = 91,
        KEYS_KP_4 = 92,
        KEYS_KP_5 = 93,
        KEYS_KP_6 = 94,
        KEYS_KP_7 = 95,
        KEYS_KP_8 = 96,
        KEYS_KP_9 = 97,
        KEYS_KP_0 = 98,
        KEYS_KP_PERIOD = 99,
        KEYS_NONUSBACKSLASH = 100,
        KEYS_APPLICATION = 101,
        KEYS_POWER = 102,
        KEYS_KP_EQUALS = 103,
        KEYS_F13 = 104,
        KEYS_F14 = 105,
        KEYS_F15 = 106,
        KEYS_F16 = 107,
        KEYS_F17 = 108,
        KEYS_F18 = 109,
        KEYS_F19 = 110,
        KEYS_F20 = 111,
        KEYS_F21 = 112,
        KEYS_F22 = 113,
        KEYS_F23 = 114,
        KEYS_F24 = 115,
        KEYS_EXECUTE = 116,
        KEYS_HELP = 117,
        KEYS_MENU = 118,
        KEYS_SELECT = 119,
        KEYS_STOP = 120,
        KEYS_AGAIN = 121,
        KEYS_UNDO = 122,
        KEYS_CUT = 123,
        KEYS_COPY = 124,
        KEYS_PASTE = 125,
        KEYS_FIND = 126,
        KEYS_MUTE = 127,
        KEYS_VOLUMEUP = 128,
        KEYS_VOLUMEDOWN = 129,
        KEYS_KP_COMMA = 133,
        KEYS_KP_EQUALSAS400 = 134,
        KEYS_INTERNATIONAL1 = 135,
        KEYS_INTERNATIONAL2 = 136,
        KEYS_INTERNATIONAL3 = 137,
        KEYS_INTERNATIONAL4 = 138,
        KEYS_INTERNATIONAL5 = 139,
        KEYS_INTERNATIONAL6 = 140,
        KEYS_INTERNATIONAL7 = 141,
        KEYS_INTERNATIONAL8 = 142,
        KEYS_INTERNATIONAL9 = 143,
        KEYS_LANG1 = 144,
        KEYS_LANG2 = 145,
        KEYS_LANG3 = 146,
        KEYS_LANG4 = 147,
        KEYS_LANG5 = 148,
        KEYS_LANG6 = 149,
        KEYS_LANG7 = 150,
        KEYS_LANG8 = 151,
        KEYS_LANG9 = 152,
        KEYS_ALTERASE = 153,
        KEYS_SYSREQ = 154,
        KEYS_CANCEL = 155,
        KEYS_CLEAR = 156,
        KEYS_PRIOR = 157,
        KEYS_RETURN2 = 158,
        KEYS_SEPARATOR = 159,
        KEYS_OUT = 160,
        KEYS_OPER = 161,
        KEYS_CLEARAGAIN = 162,
        KEYS_CRSEL = 163,
        KEYS_EXSEL = 164,
        KEYS_KP_00 = 176,
        KEYS_KP_000 = 177,
        KEYS_THOUSANDSSEPARATOR = 178,
        KEYS_DECIMALSEPARATOR = 179,
        KEYS_CURRENCYUNIT = 180,
        KEYS_CURRENCYSUBUNIT = 181,
        KEYS_KP_LEFTPAREN = 182,
        KEYS_KP_RIGHTPAREN = 183,
        KEYS_KP_LEFTBRACE = 184,
        KEYS_KP_RIGHTBRACE = 185,
        KEYS_KP_TAB = 186,
        KEYS_KP_BACKSPACE = 187,
        KEYS_KP_A = 188,
        KEYS_KP_B = 189,
        KEYS_KP_C = 190,
        KEYS_KP_D = 191,
        KEYS_KP_E = 192,
        KEYS_KP_F = 193,
        KEYS_KP_XOR = 194,
        KEYS_KP_POWER = 195,
        KEYS_KP_PERCENT = 196,
        KEYS_KP_LESS = 197,
        KEYS_KP_GREATER = 198,
        KEYS_KP_AMPERSAND = 199,
        KEYS_KP_DBLAMPERSAND = 200,
        KEYS_KP_VERTICALBAR = 201,
        KEYS_KP_DBLVERTICALBAR = 202,
        KEYS_KP_COLON = 203,
        KEYS_KP_HASH = 204,
        KEYS_KP_SPACE = 205,
        KEYS_KP_AT = 206,
        KEYS_KP_EXCLAM = 207,
        KEYS_KP_MEMSTORE = 208,
        KEYS_KP_MEMRECALL = 209,
        KEYS_KP_MEMCLEAR = 210,
        KEYS_KP_MEMADD = 211,
        KEYS_KP_MEMSUBTRACT = 212,
        KEYS_KP_MEMMULTIPLY = 213,
        KEYS_KP_MEMDIVIDE = 214,
        KEYS_KP_PLUSMINUS = 215,
        KEYS_KP_CLEAR = 216,
        KEYS_KP_CLEARENTRY = 217,
        KEYS_KP_BINARY = 218,
        KEYS_KP_OCTAL = 219,
        KEYS_KP_DECIMAL = 220,
        KEYS_KP_HEXADECIMAL = 221,
        KEYS_LCTRL = 224,
        KEYS_LSHIFT = 225,
        KEYS_LALT = 226,
        KEYS_LGUI = 227,
        KEYS_RCTRL = 228,
        KEYS_RSHIFT = 229,
        KEYS_RALT = 230,
        KEYS_RGUI = 231,
        KEYS_MODE = 257,
        KEYS_AUDIONEXT = 258,
        KEYS_AUDIOPREV = 259,
        KEYS_AUDIOSTOP = 260,
        KEYS_AUDIOPLAY = 261,
        KEYS_AUDIOMUTE = 262,
        KEYS_MEDIASELECT = 263,
        KEYS_WWW = 264,
        KEYS_MAIL = 265,
        KEYS_CALCULATOR = 266,
        KEYS_COMPUTER = 267,
        KEYS_AC_SEARCH = 268,
        KEYS_AC_HOME = 269,
        KEYS_AC_BACK = 270,
        KEYS_AC_FORWARD = 271,
        KEYS_AC_STOP = 272,
        KEYS_AC_REFRESH = 273,
        KEYS_AC_BOOKMARKS = 274,
        KEYS_BRIGHTNESSDOWN = 275,
        KEYS_BRIGHTNESSUP = 276,
        KEYS_DISPLAYSWITCH = 277,
        KEYS_KBDILLUMTOGGLE = 278,
        KEYS_KBDILLUMDOWN = 279,
        KEYS_KBDILLUMUP = 280,
        KEYS_EJECT = 281,
        KEYS_SLEEP = 282,
        KEYS_APP1 = 283,
        KEYS_APP2 = 284,
        KEYS_AUDIOREWIND = 285,
        KEYS_AUDIOFASTFORWARD = 286,
        KEYS_SOFTLEFT = 287,
        KEYS_SOFTRIGHT = 288,
        KEYS_ENDCALL = 290,
        KEYS_MAX_SIZE = 512
    };

    void init();
    void handleEvent(SDL_Event* e);
    void update();
    void release();

    // Keyboard
    bool isKeyReleased(const Keyboard& key);
    bool isKeyPressedOnce(const Keyboard& key);
    bool isKeyPressed(const Keyboard& key);
    bool isKeyReleasedOnce(const Keyboard& key);

    float getKeyReleasedValue(const Keyboard& key);
    float getKeyPressedOnceValue(const Keyboard& key);
    float getKeyPressedValue(const Keyboard& key);
    float getKeyReleasedOnceValue(const Keyboard& key);

    float getKeyReleasedAxis(const Keyboard& negative, const Keyboard& positive);
    float getKeyPressedOnceAxis(const Keyboard& negative, const Keyboard& positive);
    float getKeyPressedAxis(const Keyboard& negative, const Keyboard& positive);
    float getKeyReleasedOnceAxis(const Keyboard& negative, const Keyboard& positive);

}

namespace render {

    void init();
    void release();

    void clear(const glm::vec4& color);
    void bind();
    void unbind();

    void projection(const glm::mat4& m);
    void view(const glm::mat4& m);
    void model(const glm::mat4& m);
    void setAlpha(float alpha); // 0.0f invisable 1.0f visible
    void setColor(float r, float g, float b); // Default 1.0f, 1.0f, 1.0f
    void useTexture(bool useTexture); // Default = true

    void draw();

    void enableBlend();
    void disableBlend();

    namespace texture {
        void createTextureFromFile(std::string name, std::string path);

        void bind(std::string name, GLenum textype);

        void unbind(std::string name, GLenum textype);

        void release();
    }


    namespace font {

        void init();
        void release();
        
        void createFont(std::string name, std::string path, int size);

        void bind(std::string name, GLenum tex);

        void getSize(std::string name, std::string text, int* width, int* height);

        void draw(std::string name, std::string text);

        void unbind(std::string name, GLenum tex);
    }
}

namespace sound {


    struct MusicPlayer {
        std::string name;

        void init(std::string name);
        void release();

        void play(int numLoops);
        void stop();

        void resume();
        void puase();

        bool isPlaying();
        bool isPaused();

        void rewind();

        void setPosition(double position);
        double getPolision();

    };

    struct SoundFXPlayer {
        std::string name;
        int channel;

        void init(std::string name);
        void release();

        void play(int channel, int loop);
        void stop();

        void resume();
        void pause();
        void rewind();

        bool isPlaying();
        bool isPaused();
    };


    void init();
    void release();

    void addMusicStream(std::string name, std::string path);
    void addSoundFXStream(std::string name, std::string path);

    void setMasterVolume(float volume);
    void setMusicVolume(float volume);
    void setSoundFXVolume(float volume);
};

namespace collision {

    struct Rect {
        glm::vec2 position;
        glm::vec2 size;

        void init(glm::vec2 p, glm::vec2 s);

        float left();
        float right();
        float top();
        float bottom();

        bool collide(Rect& r);

        bool collide(const glm::vec2& p);
    };

};

namespace state {
    struct IState {
        virtual void init() = 0;
        virtual void handleEvent(SDL_Event* e) = 0;
        virtual void update(float delta) = 0;
        virtual void render() = 0;
        virtual void release() = 0;
    };

    void addState(std::string name, IState* state);
    void setDefaultState(std::string name);
    void changeState(std::string name);

    void init();
    void handleEvent(SDL_Event* e);
    void update(float delta);
    void render();
    void release();
    
    namespace param {
        void setBool(std::string name, bool value);
        void setInteger(std::string name, int32_t value);
        void setUnsignedInteger(std::string name, uint32_t value);
        void setFloat(std::string name, float value);
        void setDouble(std::string name, double value);

        bool isBool(std::string name);
        int32_t isInteger(std::string name);
        uint32_t isUnsignedInteger(std::string name);
        float isFloat(std::string name);
        double isDouble(std::string name);

    }
}

namespace gui {

    struct IComponent {
        virtual void init() = 0;
        virtual void handleEvent(SDL_Event* e) = 0;
        virtual void update(float delta) = 0;
        virtual void render() = 0;
        virtual void release() = 0;
    };

    struct Label {

    };

    void init();
    void release();
}

namespace game {

    struct Level;

    struct Player {
        Level* level = nullptr;

        glm::vec2 position;
        glm::vec2 velocity;
        float speed = 128.0f;
        glm::vec2 size;
        float zpos = 0.0f;

        std::string texture = "player";

        bool env = false;

        float time = 0.0f;
        float maxTime = 1.0f;

        void init(Level* level);
        void update(float delta);
        void render();
        void release();

        collision::Rect toRect();

        // This will enable envarnibility
        void enableEnv();

        bool isEnv();
        
    };

    struct Spike {
        glm::vec2 position;
        glm::vec2 velocity;
        //float speed = 64.0f;
    };

    struct SpikeManager {
        Level* level = nullptr;

        std::vector<Spike> spikes;

        void init(Level* level, size_t amount);
        void update(float delta);
        void render();
        void release();

        void reset(int index);

        collision::Rect toRect(int index);

        size_t size();
    };

    enum CoinType {
        CT_1_PT = 0, // 50%
        CT_5_PT, // 35%
        CT_10_PT, // 15%
        CT_MAX_SIZE
    };

    struct Coin {
        glm::vec2 position;
        glm::vec2 velocity;
        CoinType type;
    };

    struct CoinManager {
        Level* level = nullptr;

        std::vector<Coin> coins;

        void init(Level* level, size_t amount);
        void update(float delta);
        void render();
        void release();

        void reset(int index);
        collision::Rect toRect(int index);

        size_t size();
    };

    // These will keep you alive longer :)
    struct Heart {
        glm::vec2 position;
        glm::vec2 velocity;
    };

    struct HeartManager {
        Level* level = nullptr;
        std::vector<Heart> hearts;

        void init(Level* level, size_t amount);
        void update(float delta);
        void render();
        void release();

        void reset(int index);
        collision::Rect toRect(int index);

        size_t size();
    };

    enum BackgroundSpeed {
        BG_SPEED_NORMAL = 0,
        BG_SPEED_SLOW,
        BG_SPEED_SLOWER
    };

    struct Background {
        glm::vec2 position;
        glm::vec2 velocity;
    };

    struct BackgroundManager {
        Level* level = nullptr;

        std::vector<Background> backgrounds;
        //float speed = 64.0f;
        BackgroundSpeed bgSpeed = BackgroundSpeed::BG_SPEED_NORMAL;

        float zpos = 0.0f;

        void init(Level* level);
        void update(float delta);
        void render(std::string name);
        void release();

        void reset(int index);
    };

    struct MenuState;

    struct BackgroundMenuStateManager {
        MenuState* ms = nullptr;

        std::vector<Background> backgrounds;
        //float speed = 64.0f;
        BackgroundSpeed bgSpeed = BackgroundSpeed::BG_SPEED_NORMAL;

        float zpos = 0.0f;

        void init(MenuState* level);
        void update(float delta);
        void render(std::string name);
        void release();

        void reset(int index);
    };

    enum TimerType {
        TT_3_MINUTES,
        TT_5_MINUTES,
        TT_10_MINUTES,
        TT_15_MINUTES,
        TT_MAX_SIZE
    };

    struct Timer {
        Level* level = nullptr;
        float time = 0.0f;

        int oldTime = -1;

        void init(Level* level, TimerType timerType);
        void update(float delta);
        void render();
        void release();

        bool isZero();

        float toTime(TimerType type);
    };

    enum GameSpeed {
        GS_SLOW = 0,        // 32.0f
        GS_NORMAL,          // 64.0f
        GS_FAST,            // 128.0f
        GS_SPEEDY_BOY,      // 256.0f
        GS_LUDICROUS_SPEED,  // 512.0f
        GS_RANDOM_SPEED, // 32, 64, 128, 256, 512 ~ On a random time interval
        GS_MAX_NUM
    };

    enum SpikeAmount {
        SA_NOT_MUCH = 0,
        SA_NORMAL,
        SA_MORE_THEN_NORMAL,
        SA_METRIC_CRAP_TON_OF_THEM,
        SA_YOU_MUST_BE_A_MASOCHIST,
        SA_MAX_NUM
    };

    enum CoinAmount {
        CA_FRUGAL = 0,
        CA_NORMAL,
        CA_MORE,
        CA_GREEDY,
        CA_SCRUGE_MC_DUCK,
        CA_MAX_NUM
    };

    enum HeartAmount {
        HA_NORMAL_AMOUNT = 0,
        HA_MID_AMOUNT,
        HA_LARGE_AMOUNT,
        HA_EX_LARGE_AMOUNT,
        HA_EXTREME_AMOUNT,
        HA_MAX_NUM
    };

    
    struct GameState;

    struct Level {
        GameState* state = nullptr;

        Player player;
        SpikeManager spikeManager;
        CoinManager coinManager;
        HeartManager heartManager;

        BackgroundManager bg01Manager;
        BackgroundManager bg02Manager;
        BackgroundManager bg03Manager;

        Timer timer;

        int score = 0;
        int heart = 0;

        // 32.0f -> 512.0f
        float actualSpeed;

        float speed = 64.0f;

        int numSpikes = 16; // 8 -> 32
        int numCoins = 8; // 4 -> 32
        int numHearts = 1; // 1 -> 5

        TimerType timerType;
        GameSpeed gameSpeed;
        SpikeAmount spikeAmount;
        CoinAmount coinAmount;
        HeartAmount heartAmount;

        float maxTime = 0.0f;
        float time = 1.0f;
        int index = 0;

        sound::SoundFXPlayer coinsSFX;
        sound::SoundFXPlayer damangeSFX;
        sound::SoundFXPlayer damange2SFX;
        sound::SoundFXPlayer heartSFX;

        sound::SoundFXPlayer oneSFX;
        sound::SoundFXPlayer twoSFX;
        sound::SoundFXPlayer threeSFX;

        sound::SoundFXPlayer youWinSFX;
        sound::SoundFXPlayer gameSetSFX;

        sound::SoundFXPlayer youLooseSFX;
        sound::SoundFXPlayer youLooseAckSFX;
        sound::SoundFXPlayer youLooseFartSFX;

        void init(
            TimerType timerType,
            GameSpeed gameSpeed,
            SpikeAmount spikeAmount,
            CoinAmount coinAmount,
            HeartAmount heartAmount,
            GameState* state
        );

        void handleEvent(SDL_Event* e);
        void update(float delta);
        void render();
        void release();

        void restart();

        float toRandomSpeed(float delta);
    };

    struct MenuState : public state::IState {
        bool setupMenu = false;

        // Timer 
        std::vector<std::string> timerList = {
            "3 Minutes",
            "5 Minutes",
            "10 Minutes",
            "15 Minutes"
        };

        std::string currentTimer = "3 Minutes";
        TimerType timerTypePass = TimerType::TT_3_MINUTES;

        // Game Speed
        std::vector<std::string> gameSpeedList = {
            "Slow",
            "Normal",
            "Fast",
            "Speedy Boy",
            "Ludicrous Speed",
            "Random Speed"
        };

        std::string currentGameSpeed = "Normal";
        GameSpeed gameSpeedPass = GameSpeed::GS_NORMAL;

        // Spike Amount
        std::vector<std::string> spikeAmountList = {
            "Not Much",
            "Normal",
            "More The Normal",
            "Metric Crap Ton of Them",
            "You Must Be A Masochist"
        };

        std::string currentSpikeAmount = "Normal";
        SpikeAmount spikeAmountPass = SpikeAmount::SA_NORMAL;

        // Coin Amount
        std::vector<std::string> coinAmountList = {
            "Frugal",
            "Normal",
            "More",
            "Greedy",
            "Scruge Mc Duck"
        };

        std::string currentCoinAmount = "Normal";
        CoinAmount coinAmountPass = CoinAmount::CA_NORMAL;

        // Heart Amount
        std::vector<std::string> heartAmountList = {
            "Normal",
            "Mid",
            "Large",
            "Ex Large",
            "Extreme"
        };

        std::string currentHeartAmount = "Normal";
        HeartAmount heartAmountPass = HeartAmount::HA_NORMAL_AMOUNT;

        BackgroundMenuStateManager bg01Manager;
        BackgroundMenuStateManager bg02Manager;
        BackgroundMenuStateManager bg03Manager;

        float speed = 64.0f;

        float maxTime = 0.0f;
        float time = 1.0f;
        int index = 0;

        sound::SoundFXPlayer selected;

        virtual void init();
        virtual void handleEvent(SDL_Event* e);
        virtual void update(float delta);
        virtual void render();
        virtual void release();

        float toRandomSpeed(float delta);
    };

    struct GameState : public state::IState {
        Level level;

        bool contextMenu = false;
        bool loseMenu = false;
        bool winMenu = false;

        sound::SoundFXPlayer selected;

        virtual void init();
        virtual void handleEvent(SDL_Event* e);
        virtual void update(float delta);
        virtual void render();
        virtual void release();
    };

    void init();
    void handleEvent(SDL_Event* e);
    void update(float delta);
    void render();
    void release();

    uint32_t m_rand();
}

#endif