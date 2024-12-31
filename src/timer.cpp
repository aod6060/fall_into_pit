#include "glm/ext/matrix_transform.hpp"
#include "sys.h"
#include <iomanip>
#include <sstream>


namespace game {

    void Timer::init(Level* level, TimerType timerType) {
        this->level = level;

        //this->time = this->toTime(timerType);
        this->time = 15.0f;

    }

    void Timer::update(float delta) {
        this->time -= delta;

        int t = this->time;

        int m = t / 60;
        int s = t % 60;

        if(m == 0 && s <= 3) {
            if(oldTime != s) {
                //this->level->coinsSFX.play(-1, 0);

                if(s == 3) {
                    this->level->threeSFX.play(-1, 0);
                } else if(s == 2) {
                    this->level->twoSFX.play(-1, 0);
                } else if(s == 1) {
                    this->level->oneSFX.play(-1, 0);
                } else if(s == 0) {
                    this->level->youWinSFX.play(-1, 0);
                }

                oldTime = s;
            }
        }
    }

    void Timer::render() {
        std::stringstream ss;

        int width;
        int height;

        int t = this->time;

        int m = t / 60;
        int s = t % 60;

        ss << m << ":" << std::setfill('0') << std::setw(2) << s;

        render::font::getSize("regular", ss.str(), &width, &height);

        if(m == 0 && s <= 3) {
            render::setColor(1.0f, 0.0f, 0.0f);
        } else {
            render::setColor(1.0f, 1.0f, 1.0f);
        }

        render::model(
            glm::translate(glm::mat4(1.0f), glm::vec3(320.0f - (width * 0.5f), 0.0f, 1.0f)) *
            glm::scale(glm::mat4(1.0f), glm::vec3(width, height, 0.0f))
        );

        render::font::draw("regular", ss.str());

        ss.str("");

        render::setColor(1.0f, 1.0f, 1.0f);
    }

    void Timer::release() {
        this->level = nullptr;
        this->oldTime = -1;
    }

    bool Timer::isZero() {
        return this->time <= 0.0f;
    }

    float Timer::toTime(TimerType type) {
        if(type == TT_3_MINUTES) {
            return 3.0f * 60.0f;
        } else if(type == TT_5_MINUTES) {
            return 5.0f * 60.0f;
        } else if(type == TT_10_MINUTES) {
            return 10.0f * 60.0f;
        } else if(type == TT_15_MINUTES) {
            return 15.0f * 60.0f;
        } else {
            return 3.0f * 60.0f;
        }
    }
}