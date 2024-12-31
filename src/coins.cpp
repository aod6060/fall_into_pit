#include "glm/ext/matrix_transform.hpp"
#include "sys.h"



namespace game {

    void CoinManager::init(Level* level, size_t amount) {
        this->level = level;

        this->coins.resize(amount);

        for(int i = 0; i < this->coins.size(); i++) {
            this->reset(i);
        }
    }

    void CoinManager::update(float delta) {
        for(int i = 0; i < this->coins.size(); i++) {
            this->coins[i].position += this->coins[i].velocity * level->speed * delta;

            if(this->coins[i].position.y + 32.0f < 0.0f) {
                this->reset(i);
            }
        }
    }

    void CoinManager::render() {
        for(int i = 0; i < this->coins.size(); i++) {

            std::string c = "";

            if(this->coins.at(i).type == CoinType::CT_1_PT) {
                c = "coin_pt1";
            } else if(this->coins.at(i).type == CoinType::CT_5_PT) {
                c = "coin_pt5";
            } else if(this->coins.at(i).type == CoinType::CT_10_PT) {
                c = "coin_pt10";
            }

            render::model(
                glm::translate(glm::mat4(1.0f), glm::vec3(coins.at(i).position, -1.0f)) *
                glm::scale(glm::mat4(1.0f), glm::vec3(32.0f, 32.0f, 0.0f))
            );

            render::texture::bind(c, GL_TEXTURE0);
            render::draw();
            render::texture::unbind(c, GL_TEXTURE0);
        }
    }

    void CoinManager::release() {
        this->coins.clear();
        this->level = nullptr;
    }


    void CoinManager::reset(int index) {
        this->coins.at(index).position.x = ((m_rand() % 18) + 1) * 32;
        this->coins.at(index).velocity = glm::vec2(0.0f, -1.0f);
        this->coins.at(index).type = (CoinType)(m_rand() % CoinType::CT_MAX_SIZE); 

        int mul;

        switch(this->coins.at(index).type) {
            case game::CoinType::CT_1_PT:
                mul = 1;
                break;
            case game::CoinType::CT_5_PT:
                mul = 5;
                break;
            case game::CoinType::CT_10_PT:
                mul = 10;
                break;
            default:
                mul = 1;
                break;
        }

        this->coins.at(index).position.y = (m_rand() % (15 * mul)) * 32 + app::getHeight();
    }

    collision::Rect CoinManager::toRect(int index) {
        collision::Rect r;
        r.init(this->coins.at(index).position, glm::vec2(32.0f));
        return r;
    }

    size_t CoinManager::size() {
        return this->coins.size();
    }

}