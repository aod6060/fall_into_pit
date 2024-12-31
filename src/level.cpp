#include "glm/ext/matrix_transform.hpp"
#include "sys.h"
#include <sstream>
#include <vector>



namespace game {

    void Level::init(
        TimerType timerType,
        GameSpeed gameSpeed,
        SpikeAmount spikeAmount,
        CoinAmount coinAmount,
        HeartAmount heartAmount,
        GameState* state
    ) {

        this->timerType = timerType;
        this->gameSpeed = gameSpeed;
        this->spikeAmount = spikeAmount;
        this->coinAmount = coinAmount;
        this->heartAmount = heartAmount;
        this->state = state;

        this->score = 0;
        this->heart = 0;

        // Init Plyaer
        this->player.init(this);

        // Init Spike Manager
        if(gameSpeed == GameSpeed::GS_SLOW) {
            this->actualSpeed = 32.0f;
        } else if(gameSpeed == GameSpeed::GS_NORMAL) {
            this->actualSpeed = 64.0f;
        } else if(gameSpeed == GameSpeed::GS_FAST) {
            this->actualSpeed = 128.0f;
        } else if(gameSpeed == GameSpeed::GS_SPEEDY_BOY) {
            this->actualSpeed = 256.0f;
        } else if(gameSpeed == GameSpeed::GS_LUDICROUS_SPEED) {
            this->actualSpeed = 512.0f;
        } else if(gameSpeed == GameSpeed::GS_RANDOM_SPEED) {
            this->actualSpeed = this->toRandomSpeed(0.0f);
        }

        int amount = 0;
        if(spikeAmount == SpikeAmount::SA_NOT_MUCH) {
            amount = 8;
        } else if(spikeAmount == SpikeAmount::SA_NORMAL) {
            amount = 16;
        } else if(spikeAmount == SpikeAmount::SA_MORE_THEN_NORMAL) {
            amount = 24;
        } else if(spikeAmount == SpikeAmount::SA_METRIC_CRAP_TON_OF_THEM) {
            amount = 32;
        } else if(spikeAmount == SpikeAmount::SA_YOU_MUST_BE_A_MASOCHIST) {
            amount = 64;
        }

        this->spikeManager.init(this, amount); // 8 -> 32

        amount = 0;

        if(coinAmount == CoinAmount::CA_FRUGAL) {
            amount = 4;
        } else if(coinAmount == CoinAmount::CA_NORMAL) {
            amount = 8;
        } else if(coinAmount == CoinAmount::CA_MORE) {
            amount = 12;
        } else if(coinAmount == CoinAmount::CA_GREEDY) {
            amount = 16;
        } else if(coinAmount == CoinAmount::CA_SCRUGE_MC_DUCK) {
            amount = 64;
        }

        // Init Coin Manager
        this->coinManager.init(this, amount); // 4 -> 16

        amount = 0;

        if(heartAmount == HeartAmount::HA_NORMAL_AMOUNT) {
            amount = 1;
        } else if(heartAmount == HeartAmount::HA_MID_AMOUNT) {
            amount = 2;
        } else if(heartAmount == HeartAmount::HA_LARGE_AMOUNT) {
            amount = 3;
        } else if(heartAmount == HeartAmount::HA_EX_LARGE_AMOUNT) {
            amount = 4;
        } else if(heartAmount == HeartAmount::HA_EXTREME_AMOUNT) {
            amount = 10;
        }

        // Init Heart Manager
        this->heartManager.init(this, amount); // 1 -> 5

        // Init Background Manager 1
        this->bg01Manager.zpos = -2.0f;
        this->bg01Manager.init(this);

        // Init Background Manager 2
        this->bg02Manager.zpos = -3.0f;
        this->bg02Manager.bgSpeed = BackgroundSpeed::BG_SPEED_SLOW;
        this->bg02Manager.init(this);

        // Init Background Manager 3
        this->bg03Manager.zpos = -4.0f;
        this->bg03Manager.bgSpeed = BackgroundSpeed::BG_SPEED_SLOWER;
        this->bg03Manager.init(this);

        this->timer.init(this, timerType);

        this->coinsSFX.init("coins");
        this->damangeSFX.init("damage");
        this->damange2SFX.init("damage2");
        this->heartSFX.init("heart");

        oneSFX.init("one");
        twoSFX.init("two");
        threeSFX.init("three");

        youWinSFX.init("you_win");
        gameSetSFX.init("game_set");

        youLooseSFX.init("you_loose");
        youLooseAckSFX.init("you_loose_ack");
        youLooseFartSFX.init("you_loose_fart");
    }

    void Level::handleEvent(SDL_Event* e) {
    }

    void Level::update(float delta) {
        this->player.update(delta);
        this->spikeManager.update(delta);
        this->coinManager.update(delta);
        this->heartManager.update(delta);

        this->bg01Manager.update(delta);
        this->bg02Manager.update(delta);
        this->bg03Manager.update(delta);

        this->timer.update(delta);

        collision::Rect pr = this->player.toRect();

        if(!this->player.isEnv()) {
            for(int i = 0; i < this->spikeManager.size(); i++) {
                collision::Rect smr = this->spikeManager.toRect(i);

                if(pr.collide(smr)) {
                    if(this->heart < 1) {
                        this->state->loseMenu = true;
                        //this->youLooseSFX.play(-1, 0);

                        int value = m_rand() % 3;

                        if(value == 0) {
                            this->youLooseSFX.play(-1, 0);
                        } else if(value == 1) {
                            this->youLooseAckSFX.play(-1, 0);
                        } else if(value == 2) {
                            this->youLooseFartSFX.play(-1, 0);
                        }

                    } else {
                        this->heart -= 1;
                        this->player.enableEnv();

                    }

                    
                    //(m_rand() % 2 == 2) ? damangeSFX.play(-1, 0) | damange2SFX.play(-1, 0);
                    if(m_rand() % 2 == 0) {
                        damangeSFX.play(-1, 0);
                    } else {
                        damange2SFX.play(-1, 0);
                    }
                }    
            }
        }

        for(int i = 0; i < this->coinManager.size(); i++) {
            collision::Rect er = this->coinManager.toRect(i);

            if(pr.collide(er)) {
                if(this->coinManager.coins.at(i).type == CoinType::CT_1_PT) {
                    score += 1;
                }
                else if(this->coinManager.coins.at(i).type == CoinType::CT_5_PT) {
                    score += 5;
                }
                else if(this->coinManager.coins.at(i).type == CoinType::CT_10_PT) {
                    score += 10;
                }

                this->coinManager.reset(i);

                coinsSFX.play(-1, 0);
            }
        }

        for(int i = 0; i < this->heartManager.size(); i++) {
            collision::Rect er = this->heartManager.toRect(i);

            if(pr.collide(er)) {
                if(this->heart < 9) {
                    this->heart += 1;
                    this->heartManager.reset(i);
                } else {
                    this->score += 1;
                    this->heartManager.reset(i);
                }

                heartSFX.play(-1, 0);
            }
        }

        if(timer.isZero()) {
            //this->restart();
            this->state->winMenu = true;
        }

        if(this->gameSpeed == GameSpeed::GS_RANDOM_SPEED) {
            this->actualSpeed = this->toRandomSpeed(delta);
        }
    }

    void Level::render() {
        render::enableBlend();

        // Render Main Background
        render::model(
            glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -5.0f)) *
            glm::scale(glm::mat4(1.0f), glm::vec3(app::getWidth(), app::getHeight(), 0.0f))
        );

        render::texture::bind("bg04", GL_TEXTURE0);
        render::draw();
        render::texture::unbind("bg04", GL_TEXTURE0);

        bg03Manager.render("bg03");
        bg02Manager.render("bg02");
        bg01Manager.render("bg01");

        spikeManager.render();

        coinManager.render();

        heartManager.render();

        player.render();


        float o = app::getWidth() * 0.20;

        render::model(
            glm::translate(glm::mat4(1.0f), glm::vec3(o - 52.0f, 12.0f, 1.0f)) *
            glm::scale(glm::mat4(1.0f), glm::vec3(48, 48, 0.0f))
        );


        render::texture::bind("coin_pt1", GL_TEXTURE0);
        render::draw();
        render::texture::unbind("coin_pt1", GL_TEXTURE0);

        int width = 0;
        int height = 0;

        std::stringstream ss;

        ss << score;

        render::font::getSize("regular", ss.str(), &width, &height);

        render::model(
            glm::translate(glm::mat4(1.0f), glm::vec3(o, 0.0f, 1.0f)) *
            glm::scale(glm::mat4(1.0f), glm::vec3(width, height, 0.0f))
        );

        render::font::draw("regular", ss.str());

        // Draw Heart

        float offset = app::getWidth() * 0.8f;

        render::model(
            glm::translate(glm::mat4(1.0f), glm::vec3(offset - 48.0f, 12.0f, 1.0f)) *
            glm::scale(glm::mat4(1.0f), glm::vec3(48, 48, 0.0f))
        );


        render::texture::bind("heart", GL_TEXTURE0);
        render::draw();
        render::texture::unbind("heart", GL_TEXTURE0);

        ss.str("");

        ss << heart;

        render::font::getSize("regular", ss.str(), &width, &height);

        render::model(
            glm::translate(glm::mat4(1.0f), glm::vec3(offset, 0.0f, 1.0f)) *
            glm::scale(glm::mat4(1.0f), glm::vec3(width, height, 0.0f))
        );

        render::font::draw("regular", ss.str());

        timer.render();

        render::disableBlend();


    }

    void Level::release() {
        coinsSFX.release();
        damangeSFX.release();
        damange2SFX.release();
        heartSFX.release();

        timer.release();

        player.release();
        spikeManager.release();
        coinManager.release();
        heartManager.release();

        bg01Manager.release();
        bg02Manager.release();
        bg03Manager.release();
    }

    void Level::restart() {
        this->release();
        this->init(
            this->timerType,
            this->gameSpeed,
            this->spikeAmount,
            this->coinAmount,
            this->heartAmount,
            this->state
        );
    }

    float Level::toRandomSpeed(float delta) {
        static std::vector<float> _speeds = {
            32.0f,
            64.0f,
            128.0f,
            256.0f,
            512.0f
        };

        if(this->time >= this->maxTime) {
            this->index = game::m_rand() % _speeds.size();
            this->time = 0.0f;
            this->maxTime = 5.0f;
        } else {
            this->time += delta;
        }


        return _speeds.at(index);
    }
}