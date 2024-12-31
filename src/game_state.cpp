#include "sys.h"
#include "3rd/imgui.h"
#include "3rd/imgui_impl_opengl3.h"
#include "3rd/imgui_impl_sdl2.h"

namespace game {
    

    void GameState::init() {
        this->level.init(
            (TimerType)state::param::isInteger("timerType"),
            (GameSpeed)state::param::isInteger("gameSpeed"),
            (SpikeAmount)state::param::isInteger("spikeAmount"),
            (CoinAmount)state::param::isInteger("coinAmount"),
            (HeartAmount)state::param::isInteger("heartAmount"),
            this
        );

        this->contextMenu = false;
        this->loseMenu = false;
        this->winMenu = false;

        this->selected.init("select");
    }

    void GameState::handleEvent(SDL_Event* e) {
        this->level.handleEvent(e);
    }

    void GameState::update(float delta) {

        if(!this->contextMenu && !this->loseMenu && !this->winMenu) {
            this->level.update(delta);
        }

        if(input::isKeyPressedOnce(input::Keyboard::KEYS_ESCAPE) && !(this->loseMenu || this->winMenu)) {
            contextMenu = !contextMenu;
        }

    }

    void GameState::render() {
        this->level.render();


        // Exit Menu
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL2_NewFrame();
        ImGui::NewFrame();

        if(contextMenu && !(loseMenu || winMenu)) {
            ImGui::Begin("Context Menu");

            if(ImGui::Button("Continue")) {
                this->contextMenu = false;
                this->selected.play(-1, 0);
            }

            if(ImGui::Button("Restart")) {
                this->level.restart();
                this->contextMenu = false;
                this->selected.play(-1, 0);
            }

            if(ImGui::Button("Exit")) {
                state::changeState("menu");
                this->selected.play(-1, 0);
            }

            ImGui::End();
        }

        if(loseMenu) {
            ImGui::Begin("You Lose!");
            std::stringstream ss;

            ss << "Score: " << this->level.score;

            ImGui::Text("%s", ss.str().c_str());

            if(ImGui::Button("Restart")) {
                level.restart();
                this->loseMenu = false;
                this->selected.play(-1, 0);
            }

            if(ImGui::Button("Exit")) {
                state::changeState("menu");
                this->selected.play(-1, 0);
            }

            ImGui::End();
        }

        if(winMenu) {
            ImGui::Begin("You Win! :D");
            
            std::stringstream ss;

            ss << "Score: " << this->level.score;

            ImGui::Text("%s", ss.str().c_str());

            if(ImGui::Button("Restart")) {
                level.restart();
                this->winMenu = false;
                this->selected.play(-1, 0);
            }

            if(ImGui::Button("Exit")) {
                state::changeState("menu");
                this->selected.play(-1, 0);
            }

            ImGui::End();
        }

        ImGui::EndFrame();
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

    void GameState::release() {
        this->level.release();
    }

}