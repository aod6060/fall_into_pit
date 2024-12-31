#include "sys.h"


namespace collision {

    void Rect::init(glm::vec2 p, glm::vec2 s) {
        this->position = p;
        this->size = s;
    }

    float Rect::left() {
        return this->position.x;
    }

    float Rect::right() {
        return this->position.x + this->size.x;
    }

    float Rect::top() {
        return this->position.y;
    }

    float Rect::bottom() {
        return this->position.y + this->size.y;
    }

    bool Rect::collide(Rect& r) {
        return 
            this->left() < r.right()    &&
            this->right() > r.left()    &&
            this->top() < r.bottom()    &&
            this->bottom() > r.top();
    }

    bool Rect::collide(const glm::vec2& p) {
        return 
            this->left() < p.x          &&
            this->bottom() > p.x        &&
            this->top() < p.y           &&
            this->bottom() > p.y;
    }

    
}