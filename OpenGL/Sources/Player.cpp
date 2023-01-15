#include <Player.hpp>

void Player::Update(const float deltaTime, const LowRenderer::Camera& cam)
{
    PlayerControl->Update(deltaTime, cam);
}

Player::Player(Resources::ResourceManager* resource)
{
    PlayerControl = resource->Get<Resources::Script>("PlayerControls");
}

Player::Player()
{

}