#include "Player.hpp"
#include "Settings.hpp"

// the first vector is the number of the sprite (column), second is the delay or speed for each
// vectors must be equal size!
std::map<PlayerState, std::pair<std::vector<int>, std::vector<float>>> Player::animationMap = {
   {PlayerState::NONE, {{3, 1, 3, 2, 3},{baseSpeed/2, baseSpeed, baseSpeed, baseSpeed, baseSpeed/2}}},
   {PlayerState::SHOOTING, {{3, 1, 3, 2, 3},{baseSpeed*2, baseSpeed*2, baseSpeed*2, baseSpeed*2, baseSpeed*2}}},
   {PlayerState::SLIDING, {{0, 1, 2},{baseSpeed*2, baseSpeed*3, baseSpeed*2}}},
   {PlayerState::FLYING, {{0, 1, 2, 1, 2, 1, 2, 3},{baseSpeed*2, baseSpeed*3, baseSpeed*3, baseSpeed*3, baseSpeed*3, baseSpeed*3, baseSpeed*3, baseSpeed*2}}},
   {PlayerState::JUMPING, {{0, 1, 2, 3, 4, 3},{baseSpeed*2, baseSpeed*2, baseSpeed*2, baseSpeed*2, baseSpeed*2, baseSpeed*2}}}
};

Player::Player(b2World& world): Entity("assets/sprites/dodo.png", sf::IntRect(0, 0, 64, 64), {100, 100}, {64*scaleFactor, 64*scaleFactor}, world) {
	state = PlayerState::NONE;
	body->SetLinearVelocity( b2Vec2(Settings::instance()->getFloatSetting("LevelSpeed"),0));
	animationIndex = 0;
	animationCounter = 0;
}

void Player::ActionSwap(PlayerState myState){}

void Player::ActionTrigger(PlayerState myState){}

Player::~Player(){}

void Player::update(float dt) {
	Entity::update(dt);
	// change animation after delaying it by the value given by a counter
	if (animationCounter >= animationMap[state].second[animationIndex] * dt) {
		++animationIndex;
		animationCounter = 0;
		if (animationIndex >= animationMap[state].first.size()) {
			animationIndex = 0;
			state = PlayerState::NONE;
		}
	}
	// TODO fix positions
	switch(state) {
		case PlayerState::NONE:
			this->setTextureRect(sf::IntRect(animationMap[state].first[animationIndex]*64, 0, 64, 64));
			break;
		case PlayerState::SHOOTING:
			this->setTextureRect(sf::IntRect(animationMap[state].first[animationIndex]*64, 1*64, 64, 64));
			break;
		case PlayerState::SLIDING:
			this->setTextureRect(sf::IntRect(animationMap[state].first[animationIndex]*64, 2*64, 64, 64));
			break;
		case PlayerState::FLYING:
			this->setTextureRect(sf::IntRect(animationMap[state].first[animationIndex]*64, 3*64, 64, 64));
			break;
		case PlayerState::JUMPING:
			this->setTextureRect(sf::IntRect(animationMap[state].first[animationIndex]*64, 4*64, 64, 64));
			break;
	}
	++animationCounter;
}

