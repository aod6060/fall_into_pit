#include "SDL_image.h"
#include "SDL_surface.h"
#include "SDL_ttf.h"
#include "sys.h"
#include <algorithm>
#include <fstream>
#include <vector>


namespace render {

    // Shaders
    uint32_t main_vertex_shader = 0;
    uint32_t main_fragment_shader = 0;

    // Program
    uint32_t main_program = 0;

    // Vertex Array
    uint32_t main_va = 0;

    // Uniforms
    uint32_t u_proj = 0;
    uint32_t u_view = 0;
    uint32_t u_model = 0;
    uint32_t u_tex0 = 0;
    uint32_t u_alpha = 0;
    uint32_t u_color = 0;
    uint32_t u_use_texture = 0;

    // Attributes
    const uint32_t A_VERTICES = 0;
    const uint32_t A_TEXCOORDS = 1;

    std::vector<float> vb_list;
    uint32_t vb_id = 0;

    std::vector<float> tb_list;
    uint32_t tb_id = 0;

    void vb_set2f(std::vector<float>& list, float x, float y) {
        list.push_back(x);
        list.push_back(y);
    }

    void vb_set3f(std::vector<float>& list, float x, float y, float z) {
        list.push_back(x);
        list.push_back(y);
        list.push_back(z);
    }

    uint32_t createShader(GLenum type, std::string path);
    
    uint32_t createProgram(const std::vector<uint32_t>& shaders);
    void destroyProgram(uint32_t id, const std::vector<uint32_t>& shaders);

    void init() {
        glEnable(GL_DEPTH_TEST);

        main_vertex_shader = createShader(GL_VERTEX_SHADER, "data/shaders/main.vert.glsl");
        main_fragment_shader = createShader(GL_FRAGMENT_SHADER, "data/shaders/main.frag.glsl");

        main_program = createProgram({main_vertex_shader, main_fragment_shader});

        glGenVertexArrays(1, &main_va);

        bind();

        u_proj = glGetUniformLocation(main_program, "proj");
        u_view = glGetUniformLocation(main_program, "view");
        u_model = glGetUniformLocation(main_program, "model");
        u_tex0 = glGetUniformLocation(main_program, "tex0");
        glUniform1i(u_tex0, 0);
        u_alpha = glGetUniformLocation(main_program, "alpha");
        glUniform1f(u_alpha, 1.0f);
        u_color = glGetUniformLocation(main_program, "color");
        glUniform3f(u_color, 1.0f, 1.0f, 1.0f);
        u_use_texture = glGetUniformLocation(main_program, "useTexture");
        glUniform1i(u_use_texture, true);

        glBindVertexArray(main_va);
        glEnableVertexAttribArray(A_VERTICES);
        glEnableVertexAttribArray(A_TEXCOORDS);
        glBindVertexArray(0);

        unbind();

        // Vertices
        glGenBuffers(1, &vb_id);

        vb_set3f(vb_list, 0.0f, 0.0f, 0.0f);
        vb_set3f(vb_list, 1.0f, 0.0f, 0.0f);
        vb_set3f(vb_list, 0.0f, 1.0f, 0.0f);

        vb_set3f(vb_list, 0.0f, 1.0f, 0.0f);
        vb_set3f(vb_list, 1.0f, 0.0f, 0.0f);
        vb_set3f(vb_list, 1.0f, 1.0f, 0.0f);

        glBindBuffer(GL_ARRAY_BUFFER, vb_id);
        glBufferData(GL_ARRAY_BUFFER, vb_list.size() * sizeof(float), vb_list.data(), GL_DYNAMIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        // TexCoords
        glGenBuffers(1, &tb_id);

        vb_set2f(tb_list, 0.0f, 0.0f);
        vb_set2f(tb_list, 1.0f, 0.0f);
        vb_set2f(tb_list, 0.0f, 1.0f);

        vb_set2f(tb_list, 0.0f, 1.0f);
        vb_set2f(tb_list, 1.0f, 0.0f);
        vb_set2f(tb_list, 1.0f, 1.0f);

        glBindBuffer(GL_ARRAY_BUFFER, tb_id);
        glBufferData(GL_ARRAY_BUFFER, tb_list.size() * sizeof(float), tb_list.data(), GL_DYNAMIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        font::init();
    }

    void release() {
        font::release();

        texture::release();

        glDeleteBuffers(1, &tb_id);
        glDeleteBuffers(1, &vb_id);

        glDeleteVertexArrays(1, &main_va);

        destroyProgram(main_program, {main_vertex_shader, main_fragment_shader});
        glDeleteShader(main_vertex_shader);
        glDeleteShader(main_fragment_shader);
    }

    void clear(const glm::vec4& color) {
        glClearColor(color.r, color.g, color.b, color.a);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void bind() {
        glUseProgram(main_program);
    }

    void unbind() {
        glUseProgram(0);
    }

    void projection(const glm::mat4& m) {
        //glUniform4fv(u_proj, 1, &m[0][0]);
        glUniformMatrix4fv(u_proj, 1, GL_FALSE, &m[0][0]);
    }

    void view(const glm::mat4& m) {
        //glUniform4fv(u_view, 1, &m[0][0]);
        glUniformMatrix4fv(u_view, 1, GL_FALSE, &m[0][0]);
    }

    void model(const glm::mat4& m) {
        //glUniform4fv(u_model, 1, &m[0][0]);
        glUniformMatrix4fv(u_model, 1, GL_FALSE, &m[0][0]);
    }
    
    void setAlpha(float alpha) {
        glUniform1f(u_alpha, alpha);
    }

    void setColor(float r, float g, float b) {
        glUniform3f(u_color, r, g, b);
    }
    
    void useTexture(bool useTexture) {
        glUniform1i(u_use_texture, useTexture);
    }

    void draw() {
        glBindVertexArray(main_va);

        glBindBuffer(GL_ARRAY_BUFFER, vb_id);
        glVertexAttribPointer(A_VERTICES, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        glBindBuffer(GL_ARRAY_BUFFER, tb_id);
        glVertexAttribPointer(A_TEXCOORDS, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        glDrawArrays(GL_TRIANGLES, 0, vb_list.size() / (3));

        glBindVertexArray(0);
    }

    void enableBlend() {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }

    void disableBlend() {
        glDisable(GL_BLEND);
    }


    uint32_t createShader(GLenum type, std::string path) {
        uint32_t temp = glCreateShader(type);

        std::string contents;

        std::ifstream in(path);
        in.seekg(0, std::ios::end);
        contents.resize(in.tellg());
        in.seekg(0, std::ios::beg);
        in.read((char*)contents.data(), contents.size());
        in.close();

        const char* c_src = contents.c_str();

        glShaderSource(temp, 1, &c_src, nullptr);
        glCompileShader(temp);

        int32_t len;
        glGetShaderiv(temp, GL_INFO_LOG_LENGTH, &len);

        if(len > 0) {
            std::string log;
            log.resize(len);
            glGetShaderInfoLog(temp, log.size(), nullptr, (char*)log.data());
            std::cout << log << "\n";
            log.clear();
        }

        return temp;
    }

    uint32_t createProgram(const std::vector<uint32_t>& shaders) {
        uint32_t temp = glCreateProgram();

        std::for_each(shaders.begin(), shaders.end(), [&](uint32_t id) {
            glAttachShader(temp, id);
        });

        glLinkProgram(temp);

        int32_t len;
        glGetProgramiv(temp, GL_INFO_LOG_LENGTH, &len);

        if(len > 0) {
            std::string log;
            log.resize(len);
            glGetProgramInfoLog(temp, log.size(), nullptr, (char*)log.data());
            std::cout << log << "\n";
            log.clear();
        }

        return temp;
    }

    void destroyProgram(uint32_t id, const std::vector<uint32_t>& shaders) {
        std::for_each(shaders.begin(), shaders.end(), [&](uint32_t shader) {
            glDetachShader(id, shader);
        });
        glDeleteProgram(id);
    }


    namespace texture {
        struct Texture2D {
            uint32_t id = 0;
            uint32_t width;
            uint32_t height;
        };

        std::map<std::string, Texture2D> textures;

        void createTextureFromFile(std::string name, std::string path) {
            Texture2D temp;

            SDL_Surface* surf = IMG_Load(path.c_str());

            if(surf == nullptr) {
                std::cout << path << ": doesn't exist. \n";
                return;
            }

            temp.width = surf->w;
            temp.height = surf->h;

            glGenTextures(1, &temp.id);

            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, temp.id);

            glTexImage2D(
                GL_TEXTURE_2D, 
                0, 
                GL_RGBA, 
                temp.width, 
                temp.height, 
                0, 
                GL_RGBA, 
                GL_UNSIGNED_BYTE, 
                surf->pixels);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, 0);

            SDL_FreeSurface(surf);

            textures[name] = temp;
        }

        void bind(std::string name, GLenum textype) {
            glActiveTexture(textype);
            glBindTexture(GL_TEXTURE_2D, textures.at(name).id);
        }

        void unbind(std::string name, GLenum textype) {
            glActiveTexture(textype);
            glBindTexture(GL_TEXTURE_2D, 0);
        }

        void release() {
            for(std::map<std::string, Texture2D>::iterator it = textures.begin(); it != textures.end(); it++) {
                glDeleteTextures(1, &it->second.id);
            }
        }
    }

    namespace font {

        struct Font {
            TTF_Font* font;
            uint32_t id;
            int32_t width;
            int32_t height;
        };

        std::map<std::string, Font> fonts;

        void init() {
            TTF_Init();
        }

        void release() {

            for(std::map<std::string, Font>::iterator it = fonts.begin(); it != fonts.end(); it++) {
                glDeleteTextures(1, &it->second.id);
                TTF_CloseFont(it->second.font);
            }

            fonts.clear();

            TTF_Quit();
        }
        
        void createFont(std::string name, std::string path, int size) {
            fonts[name].font = TTF_OpenFont(path.c_str(), size);
            glGenTextures(1, &fonts.at(name).id);
        }

        void bind(std::string name, GLenum tex) {
            glActiveTexture(tex);
            glBindTexture(GL_TEXTURE_2D, fonts.at(name).id);
        }

        
        void getSize(std::string name, std::string text, int* width, int* height) {
            TTF_SizeText(fonts.at(name).font, text.c_str(), width, height);
        }

        void draw(std::string name, std::string text) {
            SDL_Color color = {255, 255, 255, 255};

            SDL_Surface* surface = TTF_RenderText_Blended(fonts.at(name).font, text.c_str(), color);

            if(surface == nullptr) {
                return;
            }


            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, fonts.at(name).id);

            
            glTexImage2D(
                GL_TEXTURE_2D, 
                0, 
                GL_RGBA, 
                surface->w, 
                surface->h, 
                0, GL_RGBA, 
                GL_UNSIGNED_BYTE, 
                surface->pixels);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, 0);

            SDL_FreeSurface(surface);

            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, fonts.at(name).id);

            render::draw();

            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, 0);
        }

        void unbind(std::string name, GLenum tex) {
            glActiveTexture(tex);
            glBindTexture(GL_TEXTURE_2D, 0);
        }

    }

}