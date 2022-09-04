// Copyright © Veselin Dafchev 2022 All Rights Reserved.
#pragma once
#include "Entity.h"
#include "Globals.h"

class Game;

class Pacman: public Entity {

public:
	Pacman(Game* gameInstance);
	~Pacman();

	DIRECTION GetDirection();
	void Draw(sf::RenderWindow* screen);
	bool IsDead();
	void SetDead(bool dead);
	void HandleInput();
	void SetDirection(DIRECTION dir);
	bool CanGotoDirection(DIRECTION dir);
	void SetTexture(sf::Texture* texture);
	void Move();
	void UpdateAnim();
	uint32_t GetAnimByDirection(DIRECTION dir);
	sf::Sprite* Shape();
	void CheckInteraction();
	void SetCanMove(bool canMove);
	void PlayDeadSound();
	void PlayFruitEatenSound();
private:
	DIRECTION m_dir;
	sf::Sprite* m_shape;
	bool m_isDead;
	bool m_isMoving;
	uint32_t m_animFrame;
	uint32_t m_animFrameNum;
	sf::RenderWindow* m_screen;
	sf::Clock m_deltaT;
	Game* m_gameInstance;
};