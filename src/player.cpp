#include "glm/ext/matrix_transform.hpp"
#include "glm/ext/quaternion_common.hpp"
#include "glm/geometric.hpp"
#include "glm/gtc/constants.hpp"
#include "sys.h"


namespace game {


    void Player::init(Level* level) {
        this->level = level;

        this->size = glm::vec2(32.0f, 32.0f);

        this->position = glm::vec2(app::getWidth(), app::getHeight()) * 0.5f - this->size * 0.5f;

        this->velocity = glm::vec2(0.0f);

        this->speed = 128.0f;

        this->maxTime = 2.0f;
    }

    void Player::update(float delta) {

        float x_dir = input::getKeyPressedAxis(input::Keyboard::KEYS_LEFT, input::Keyboard::KEYS_RIGHT);

        this->velocity.x = x_dir * speed;

        this->position += this->velocity * delta;

        if(this->position.x < 32.0f || this->position.x + this->size.x > app::getWidth() - 32.0f) {
            this->position.x -= this->velocity.x * delta;
        }


        float y_dir = input::getKeyPressedAxis(input::Keyboard::KEYS_UP, input::Keyboard::KEYS_DOWN);

        float range = (y_dir + 1.0f) * 0.5f;

        float r = glm::mix(0.5f, 3.0f, range);

        this->level->speed = this->level->actualSpeed * r;

        if(range < 0.25f) {
            this->texture = "player_float";

        } else if(range > 0.75f) {
            this->texture = "player_speed";

        } else {
            this->texture = "player";
        }

        if(this->env) {
            if(this->time >= this->maxTime) {
                this->env = false;
                this->time = 0.0f;
            } else {
                this->time += delta;
            }
        } else {
            this->time = 0.0f;
        }
    }

    void Player::render() {
        static bool anim = false;

        render::model(
            glm::translate(glm::mat4(1.0f), glm::vec3(this->position, zpos)) *
            glm::scale(glm::mat4(1.0f), glm::vec3(this->size, 0.0f))
        );

        if(this->env) {
            if(anim) {
                render::setAlpha(1.0f);
                //render::setColor(1.0f, 1.0f, 1.0f);
            } else {
                render::setAlpha(0.5f);
                //render::setColor(1.0f, 0.0f, 0.0f);
            }
            anim = !anim;
            
        } else {
            render::setAlpha(1.0f);
            render::setColor(1.0f, 1.0f, 1.0f);
        }

        render::texture::bind(texture, GL_TEXTURE0);
        render::draw();
        render::texture::unbind(texture, GL_TEXTURE0);

        render::setAlpha(1.0f);
        render::setColor(1.0f, 1.0f, 1.0f);
    }

    void Player::release() {
        // Not sure what I'll be needing here

        this->level = nullptr;
    }

    collision::Rect Player::toRect() {
        collision::Rect r;

        glm::vec2 p = glm::vec2(position.x + 4.0f, position.y + 6.0f);
        glm::vec2 s = glm::vec2(size.x - 8.0f, size.y - 12.0f);

        r.init(p, s);
        return r;
    }

    void Player::enableEnv() {
        this->env = true;
    }

    bool Player::isEnv() {
        return this->env;
    }
}