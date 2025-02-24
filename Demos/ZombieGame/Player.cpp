#include "Player.h"
#include <SDL/SDL.h>
#include <GangerEngine/ResourceManager.h>

#include "Gun.h"

Player::Player() :
    _currentGunIndex(-1) {
    // Empty
}

Player::~Player() {
    // Empty
}

void Player::init(float speed, glm::vec2 pos, GangerEngine::InputManager* inputManager, GangerEngine::Camera2D* camera, std::vector<Bullet>* bullets) {
    _speed = speed;
    _position = pos;
    _inputManager = inputManager;
    _bullets = bullets;
    _camera = camera;
    _color.r = 255;
    _color.g = 255;
    _color.b = 255;
    _color.a = 255;
    _health = 150;

    m_textureID = GangerEngine::ResourceManager::GetTexture("Textures/player.png").id;
}

void Player::addGun(Gun* gun) {
    // Add the gun to his inventory
    _guns.push_back(gun);

    // If no gun equipped, equip gun.
    if (_currentGunIndex == -1) {
        _currentGunIndex = 0;
    }
}

void Player::update(const std::vector<std::string>& levelData,
                    std::vector<Human*>& humans,
                    std::vector<Zombie*>& zombies,
                    float deltaTime) {

    if (_inputManager->IsKeyDown(SDLK_w)) {
        _position.y += _speed * deltaTime;
    } else if (_inputManager->IsKeyDown(SDLK_s)) {
        _position.y -= _speed * deltaTime;
    }
    if (_inputManager->IsKeyDown(SDLK_a)) {
        _position.x -= _speed * deltaTime;
    } else if (_inputManager->IsKeyDown(SDLK_d)) {
        _position.x += _speed * deltaTime;
    }

    if (_inputManager->IsKeyDown(SDLK_1) && _guns.size() >= 0) {
        _currentGunIndex = 0;
    } else if (_inputManager->IsKeyDown(SDLK_2) && _guns.size() >= 1) {
        _currentGunIndex = 1;
    } else if (_inputManager->IsKeyDown(SDLK_3) && _guns.size() >= 2) {
        _currentGunIndex = 2;
    }

    glm::vec2 mouseCoords = _inputManager->GetMouseCoords();
    mouseCoords = _camera->ConvertScreenToWorld(mouseCoords);

    glm::vec2 centerPosition = _position + glm::vec2(AGENT_RADIUS);

    m_direction = glm::normalize(mouseCoords - centerPosition);

    if (_currentGunIndex != -1) {
        _guns[_currentGunIndex]->update(_inputManager->IsKeyDown(SDL_BUTTON_LEFT),
                                        centerPosition,
                                        m_direction,
                                        *_bullets,
                                        deltaTime);
                                        

    }

    collideWithLevel(levelData);
}
