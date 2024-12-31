#include "sys.h"


namespace game {


    void BackgroundManager::init(Level* level) {
        this->level = level;

        this->backgrounds.resize(2);

        // 1
        this->backgrounds[0].position = glm::vec2(0.0f);
        this->backgrounds[0].velocity = glm::vec2(0.0f, -1.0f);

        // 2
        this->backgrounds[1].position = glm::vec2(0.0f, app::getHeight());
        this->backgrounds[1].velocity = glm::vec2(0.0f, -1.0f);
    }

    void BackgroundManager::update(float delta) {
        for(int i = 0; i < this->backgrounds.size(); i++) {
            float speed = this->level->speed;
            if(this->bgSpeed == BackgroundSpeed::BG_SPEED_SLOW) {
                speed *= 0.5f;
            } else if(this->bgSpeed == BackgroundSpeed::BG_SPEED_SLOWER) {
                speed *= 0.25f;
            }

            this->backgrounds[i].position += this->backgrounds[i].velocity * speed * delta;

            if(this->backgrounds[i].position.y + app::getHeight() < 0.0f) {
                this->reset(i);
            }
        }
    }

    void BackgroundManager::render(std::string name) {
        render::texture::bind(name, GL_TEXTURE0);

        for(int i = 0; i < this->backgrounds.size(); i++) {
            render::model(
                glm::translate(glm::mat4(1.0f), glm::vec3(this->backgrounds[i].position, this->zpos)) *
                glm::scale(glm::mat4(1.0f), glm::vec3(app::getWidth(), app::getHeight(), 0.0f))
            );

            render::draw();
        }

        render::texture::unbind(name, GL_TEXTURE0);
    }

    void BackgroundManager::release() {
        this->level = nullptr;
    }

    void BackgroundManager::reset(int index) {
        int index2;

        if(index == 0) {
            index2 = 1;
        } else {
            index2 = 0;
        }

        int pos = this->backgrounds[index2].position.y + app::getHeight();

        this->backgrounds[index].position = glm::vec2(0.0f, pos);
    }




    // MenuState BackgroundManager
    void BackgroundMenuStateManager::init(MenuState* ms) {
        //this->level = level;
        this->ms = ms;

        this->backgrounds.resize(2);

        // 1
        this->backgrounds[0].position = glm::vec2(0.0f);
        this->backgrounds[0].velocity = glm::vec2(0.0f, -1.0f);

        // 2
        this->backgrounds[1].position = glm::vec2(0.0f, app::getHeight());
        this->backgrounds[1].velocity = glm::vec2(0.0f, -1.0f);
    }

    void BackgroundMenuStateManager::update(float delta) {
        for(int i = 0; i < this->backgrounds.size(); i++) {
            float speed = this->ms->speed;

            if(this->bgSpeed == BackgroundSpeed::BG_SPEED_SLOW) {
                speed *= 0.5f;
            } else if(this->bgSpeed == BackgroundSpeed::BG_SPEED_SLOWER) {
                speed *= 0.25f;
            }

            this->backgrounds[i].position += this->backgrounds[i].velocity * speed * delta;

            if(this->backgrounds[i].position.y + app::getHeight() < 0.0f) {
                this->reset(i);
            }
        }
    }

    void BackgroundMenuStateManager::render(std::string name) {
        render::texture::bind(name, GL_TEXTURE0);

        for(int i = 0; i < this->backgrounds.size(); i++) {
            render::model(
                glm::translate(glm::mat4(1.0f), glm::vec3(this->backgrounds[i].position, this->zpos)) *
                glm::scale(glm::mat4(1.0f), glm::vec3(app::getWidth(), app::getHeight(), 0.0f))
            );

            render::draw();
        }

        render::texture::unbind(name, GL_TEXTURE0);
    }

    void BackgroundMenuStateManager::release() {
        this->ms = nullptr;
    }

    void BackgroundMenuStateManager::reset(int index) {
        int index2;

        if(index == 0) {
            index2 = 1;
        } else {
            index2 = 0;
        }

        int pos = this->backgrounds[index2].position.y + app::getHeight();

        this->backgrounds[index].position = glm::vec2(0.0f, pos);
    }

}