#include "SDL_events.h"
#include "sys.h"
#include <algorithm>
#include <vector>


namespace input {

    std::vector<InputState> keys;


    void init() {
        keys.resize(Keyboard::KEYS_MAX_SIZE);

        std::for_each(keys.begin(), keys.end(), [&](InputState& state) {
            state = InputState::IS_RELEASED;
        });

    }

    void handleEvent(SDL_Event* e) {
        if(e->type == SDL_KEYDOWN) {
            if(keys[e->key.keysym.scancode] == InputState::IS_RELEASED) {
                keys[e->key.keysym.scancode] = InputState::IS_PRESSED_ONCE;
            }
        } else if(e->type == SDL_KEYUP) {
            if(keys[e->key.keysym.scancode] == InputState::IS_PRESSED) {
                keys[e->key.keysym.scancode] = InputState::IS_RELEASED_ONCE;
            }
        }
    }

    void update() {
        std::for_each(keys.begin(), keys.end(), [](InputState& state) {
            if(state == InputState::IS_PRESSED_ONCE) {
                state = InputState::IS_PRESSED;
            }

            if(state == InputState::IS_RELEASED_ONCE) {
                state = InputState::IS_RELEASED;
            }

        });
    }

    void release() {
        keys.clear();
    }

    // Keyboard
    bool isKeyReleased(const Keyboard& key) {
        return keys[key] == InputState::IS_RELEASED || keys[key] == InputState::IS_RELEASED_ONCE;
    }

    bool isKeyPressedOnce(const Keyboard& key) {
        return keys[key] == InputState::IS_PRESSED_ONCE;
    }

    bool isKeyPressed(const Keyboard& key) {
        return keys[key] == InputState::IS_PRESSED || keys[key] == InputState::IS_PRESSED_ONCE;
    }

    bool isKeyReleasedOnce(const Keyboard& key) {
        return keys[key] == InputState::IS_RELEASED_ONCE;
    }

    float getKeyReleasedValue(const Keyboard& key) {
        return isKeyReleased(key) ? 1.0f : 0.0f;
    }

    float getKeyPressedOnceValue(const Keyboard& key) {
        return isKeyPressedOnce(key) ? 1.0f : 0.0f;
    }

    float getKeyPressedValue(const Keyboard& key) {
        return isKeyPressed(key) ? 1.0f : 0.0f;
    }

    float getKeyReleasedOnceValue(const Keyboard& key) {
        return isKeyReleasedOnce(key) ? 1.0f : 0.0f;
    }

    float getKeyReleasedAxis(const Keyboard& negative, const Keyboard& positive) {
        return getKeyReleasedValue(positive) - getKeyReleasedValue(negative);
    }

    float getKeyPressedOnceAxis(const Keyboard& negative, const Keyboard& positive) {
        return getKeyPressedOnceValue(positive) - getKeyPressedOnceValue(negative);
    }

    float getKeyPressedAxis(const Keyboard& negative, const Keyboard& positive) {
        return getKeyPressedValue(positive) - getKeyPressedValue(negative);
    }

    float getKeyReleasedOnceAxis(const Keyboard& negative, const Keyboard& positive) {
        return getKeyReleasedOnceValue(positive) - getKeyReleasedOnceValue(negative);
    }

}