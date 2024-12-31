#include "sys.h"
#include "imgui/imgui_impl_opengl3.h"
#include "imgui/imgui_impl_sdl2.h"
#include "imgui/imgui.h"

namespace game {
    
    void MenuState::init() {
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

        selected.init("select");


    }

    void MenuState::handleEvent(SDL_Event* e) {

    }

    void MenuState::update(float delta) {

        if(this->gameSpeedPass == GameSpeed::GS_SLOW) {
            this->speed = 32.0f;
        } else if(this->gameSpeedPass == GameSpeed::GS_NORMAL) {
            this->speed = 64.0f;
        } else if(this->gameSpeedPass == GameSpeed::GS_FAST) {
            this->speed = 128.0f;
        } else if(this->gameSpeedPass == GameSpeed::GS_SPEEDY_BOY) {
            this->speed = 256.0f;
        } else if(this->gameSpeedPass == GameSpeed::GS_LUDICROUS_SPEED) {
            this->speed = 512.0f;
        } else if(this->gameSpeedPass == GameSpeed::GS_RANDOM_SPEED) {
            this->speed = this->toRandomSpeed(delta);
        }

        this->bg01Manager.update(delta);
        this->bg02Manager.update(delta);
        this->bg03Manager.update(delta);
    }

    void MenuState::render() {
        render::enableBlend();

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

        render::model(
            glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 2.0f)) *
            glm::scale(glm::mat4(1.0f), glm::vec3(app::getWidth(), app::getHeight(), 0.0f))
        );

        render::texture::bind("title_text", GL_TEXTURE0);
        render::draw();
        render::texture::unbind("title_text", GL_TEXTURE0);

        render::disableBlend();

        // Menu
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL2_NewFrame();
        ImGui::NewFrame();

        if(this->setupMenu) {
            ImGui::Begin("Setup Menu");

            // Timer
            if(ImGui::BeginCombo("Timer", currentTimer.data())) {
                for(int i = 0; i < timerList.size(); i++) {
                    bool is_selected = (currentTimer == timerList[i]);

                    if(ImGui::Selectable(timerList[i].data(), is_selected)) {
                        currentTimer = timerList[i];
                        this->timerTypePass = (TimerType)(i);
                    }

                    if(is_selected) {
                        ImGui::SetItemDefaultFocus();
                    }
                }
                ImGui::EndCombo();
            }

            // Game Speed
            if(ImGui::BeginCombo("Game Speed", currentGameSpeed.data())) {
                for(int i = 0; i < gameSpeedList.size(); i++) {
                    bool is_selected = (currentGameSpeed == gameSpeedList[i]);

                    if(ImGui::Selectable(gameSpeedList[i].data(), is_selected)) {
                        currentGameSpeed = gameSpeedList[i];
                        this->gameSpeedPass = (GameSpeed)(i);
                    }

                    if(is_selected) {
                        ImGui::SetItemDefaultFocus();
                    }
                }
                ImGui::EndCombo();
            }

            // Spike Amount
            if(ImGui::BeginCombo("Spike Amount", currentSpikeAmount.data())) {
                for(int i = 0; i < spikeAmountList.size(); i++) {
                    bool is_selected = (currentSpikeAmount == spikeAmountList[i]);

                    if(ImGui::Selectable(spikeAmountList[i].data(), is_selected)) {
                        currentSpikeAmount = spikeAmountList[i];
                        this->spikeAmountPass = (SpikeAmount)(i);
                    }

                    if(is_selected) {
                        ImGui::SetItemDefaultFocus();
                    }
                }
                ImGui::EndCombo();
            }

            // Coin Amount
            if(ImGui::BeginCombo("Coin Amount", currentCoinAmount.data())) {
                for(int i = 0; i < coinAmountList.size(); i++) {
                    bool is_selected = (currentCoinAmount == coinAmountList[i]);

                    if(ImGui::Selectable(coinAmountList[i].data(), is_selected)) {
                        currentCoinAmount = coinAmountList[i];
                        this->coinAmountPass = (CoinAmount)(i);
                    }

                    if(is_selected) {
                        ImGui::SetItemDefaultFocus();
                    }
                }
                ImGui::EndCombo();
            }

            // Heart Amount
            if(ImGui::BeginCombo("Heart Amount", currentHeartAmount.data())) {
                for(int i = 0; i < heartAmountList.size(); i++) {
                    bool is_selected = (currentHeartAmount == heartAmountList[i]);

                    if(ImGui::Selectable(heartAmountList[i].data(), is_selected)) {
                        currentHeartAmount = heartAmountList[i];
                        this->heartAmountPass = (HeartAmount)(i);
                    }

                    if(is_selected) {
                        ImGui::SetItemDefaultFocus();
                    }
                }
                ImGui::EndCombo();
            }

            if(ImGui::Button("Start Game")) {
                selected.play(-1, 0);

                state::param::setInteger("timerType", this->timerTypePass);
                state::param::setInteger("gameSpeed", this->gameSpeedPass);
                state::param::setInteger("spikeAmount", this->spikeAmountPass);
                state::param::setInteger("coinAmount", this->coinAmountPass);
                state::param::setInteger("heartAmount", this->heartAmountPass);
                state::changeState("game");
            }

            if(ImGui::Button("Back")) {
                this->setupMenu = false;
                selected.play(-1, 0);
            }
            ImGui::End();
        } else {
            ImGui::Begin("Main Menu");
            if(ImGui::Button("Start")) {
                selected.play(-1, 0);
                this->setupMenu = true;
            }

            if(ImGui::Button("Exit")) {
                selected.play(-1, 0);
                app::exit();
            }
            ImGui::End();
        }
        ImGui::EndFrame();
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    }

    void MenuState::release() {
        this->bg01Manager.release();
        this->bg02Manager.release();
        this->bg03Manager.release();
    }

    float MenuState::toRandomSpeed(float delta) {
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