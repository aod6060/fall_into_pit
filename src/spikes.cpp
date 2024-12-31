#include "glm/ext/matrix_transform.hpp"
#include "sys.h"


namespace game {


    void SpikeManager::init(Level* level, size_t amount) {
        this->level = level;

        this->spikes.resize(amount);

        for(int i = 0; i < this->spikes.size(); i++) {
            this->reset(i);
        }
    }

    void SpikeManager::update(float delta) {
        for(int i = 0; i < this->spikes.size(); i++) {
            this->spikes[i].position += this->spikes[i].velocity * level->speed * delta;

            if(this->spikes[i].position.y + 32.0f < 0.0f) {
                this->reset(i);
            }
        }
    }

    void SpikeManager::render() {
        render::texture::bind("spike", GL_TEXTURE0);

        for(int i = 0; i < this->spikes.size(); i++) {
            render::model(
                glm::translate(glm::mat4(1.0f), glm::vec3(this->spikes[i].position, -1.0f)) *
                glm::scale(glm::mat4(1.0f), glm::vec3(32.0f, 32.0f, 0.0f))
            );

            render::draw();
        }

        render::texture::unbind("spike", GL_TEXTURE0);
    }

    void SpikeManager::release() {
        this->spikes.clear();
        this->level = nullptr;
    }

    void SpikeManager::reset(int index) {
        this->spikes[index].position.x = ((m_rand() % 18) + 1) * 32;
        this->spikes[index].position.y = (m_rand() % 15) * 32 + app::getHeight();
        this->spikes[index].velocity = glm::vec2(0.0f, -1.0f);
    }

    collision::Rect SpikeManager::toRect(int index) {
        collision::Rect temp;
        temp.init(this->spikes.at(index).position, glm::vec2(32.0f));
        return temp;
    }

    size_t SpikeManager::size() {
        return this->spikes.size();
    }
}