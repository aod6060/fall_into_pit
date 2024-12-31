#include "sys.h"
#include <map>

namespace state {

    std::map<std::string, IState*> states;
    std::string currentState;

    void addState(std::string name, IState* state) {
        states[name] = state;
    }

    void setDefaultState(std::string name) {
        currentState = name;
    }

    void changeState(std::string name) {
        states.at(currentState)->release();
        currentState = name;
        states.at(currentState)->init();
    }

    void init() {
        states.at(currentState)->init();
    }

    void handleEvent(SDL_Event* e) {
        states.at(currentState)->handleEvent(e);
    }

    void update(float delta) {
        states.at(currentState)->update(delta);
    }

    void render() {
        states.at(currentState)->render();
    }

    void release() {
        states.at(currentState)->release();
    }

    namespace param {
        std::map<std::string, bool> bools;
        std::map<std::string, int32_t> integers;
        std::map<std::string, uint32_t> unsignedIntegers;
        std::map<std::string, float> floats;
        std::map<std::string, double> doubles;

        void setBool(std::string name, bool value) {
            bools[name] = value;
        }

        void setInteger(std::string name, int32_t value) {
            integers[name] = value;
        }

        void setUnsignedInteger(std::string name, uint32_t value) {
            unsignedIntegers[name] = value;
        }

        void setFloat(std::string name, float value) {
            floats[name] = value;
        }

        void setDouble(std::string name, double value) {
            doubles[name] = value;
        }

        bool isBool(std::string name) {
            return bools.at(name);
        }

        int32_t isInteger(std::string name) {
            return integers.at(name);
        }

        uint32_t isUnsignedInteger(std::string name) {
            return unsignedIntegers.at(name);
        }

        float isFloat(std::string name) {
            return floats.at(name);
        }

        double isDouble(std::string name) {
            return doubles.at(name);
        }

    }
}