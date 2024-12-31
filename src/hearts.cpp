#include "glm/ext/matrix_transform.hpp"
#include "sys.h"


namespace game {


    void HeartManager::init(Level* level, size_t amount) {
        this->level = level;
        this->hearts.resize(amount);
        for(int i = 0; i < this->hearts.size(); i++) {
            this->reset(i);
        }
    }

    void HeartManager::update(float delta) {
        for(int i = 0; i < this->hearts.size(); i++) {
            this->hearts[i].position += this->hearts[i].velocity * level->speed * delta;

            if(this->hearts[i].position.y + 32.0f < 0.0f) {
                this->reset(i);
            }
        }
    }

    void HeartManager::render() {
        for(int i = 0; i < this->hearts.size(); i++) {
            render::model(
                glm::translate(glm::mat4(1.0f), glm::vec3(this->hearts.at(i).position, -1.0f)) *
                glm::scale(glm::mat4(1.0f), glm::vec3(32.0f, 32.0f, 0.0f))
            );

            render::texture::bind("heart", GL_TEXTURE0);
            render::draw();
            render::texture::unbind("heart", GL_TEXTURE0);
        }
    }

    void HeartManager::release() {
        this->hearts.clear();
        this->level = nullptr;
    }

    void HeartManager::reset(int index) {
        this->hearts.at(index).position.x = ((m_rand() % 18) + 1) * 32;
        this->hearts.at(index).position.y = (m_rand() % (15 * 5)) * 32 + app::getHeight();
        this->hearts.at(index).velocity = glm::vec2(0.0f, -1.0f);
    }

    collision::Rect HeartManager::toRect(int index) {
        collision::Rect r;
        r.init(this->hearts.at(index).position, glm::vec2(32.0f));
        return r;
    }

    size_t HeartManager::size() {
        return this->hearts.size();
    }

}