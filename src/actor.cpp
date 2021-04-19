#include "actor.h"

static bool collide(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2);
static bool collide(Solid* solid, int x, int y, int w, int h);

void Actor::setX(int xNum)
{
    this->x = xNum;
}

void Actor::setY(int yNum)
{
    this->y = yNum;
}

void Actor::setWidth(int widthNum)
{
    this->width = widthNum;
}

void Actor::setHeight(int heightNum)
{
    this->height = heightNum;
}

int Actor::getX()
{
    return x;
}

int Actor::getY()
{
    return y;
}

int Actor::getWidth()
{
    return width;
}

int Actor::getHeight()
{
    return height;
}

void Actor::moveX(float amount, std::vector<Solid*> solids)
{
    // https://maddythorson.medium.com/celeste-and-towerfall-physics-d24bd2ae0fc5
    int move = (int) amount;
    if (move != 0) {
        int sign = move > 0 ? 1 : -1;
        while (move != 0) {
            if (!collideAt(solids, sign, 0)) {
                this->x += sign;
                move -= sign;
            } else {
                collidedX = true;
                break;
            }
        }
    }
}

void Actor::moveY(float amount, std::vector<Solid*> solids)
{
    int move = (int) amount;
    if (move != 0) {
        int sign = move > 0 ? 1 : -1;
        while (move != 0) {
            if (!collideAt(solids, 0, sign)) {
                this->y += sign;
                move -= sign;
            } else {
                collidedY = true;
                break;
            }
        }
    }
}

// Colissions
bool Actor::collideAt(int xNum, int yNum, int w, int h) {
    return x < xNum + w && x + width > xNum && y < yNum + h && y + height > yNum;
}

bool Actor::collideAt(Solid *solid) {
    return collideAt(solid->getX(), solid->getY(), solid->getWidth(), solid->getHeight());
}

bool Actor::collideAt(std::vector<Solid *> solids, int xOffset, int yOffset) {
    for (auto & solid:solids) { // TODO clang-tidy
        if (collide(solid, this->getX() + xOffset, this->getY() + yOffset, this->width, this->height)) return true;
    }
    return false;
}

static bool collide(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2)
{
    return x1 < x2 + w2 && x1 + w1 > x2 && y1 < y2 + h2 && y1 + h1 > y2;
}

static bool collide(Solid* solid, int x, int y, int w, int h)
{
    return collide(solid->getX(), solid->getY(), solid->getWidth(), solid->getHeight(), x, y, w, h);
}