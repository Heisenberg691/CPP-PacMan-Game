// Copyright © Veselin Dafchev 2022 All Rights Reserved.
#pragma once

#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "Globals.h"
#include "PathFinder.h"

class Game;

class Ghost : public Entity {
public:
	Ghost();
	~Ghost();

	void Draw(sf::RenderWindow* screen);
	DIRECTION GetDirection();
	sf::Sprite* Shape();
	virtual void Behaviour();
	void SetDirection(DIRECTION dir);
	void SetPosition(sf::Vector2f pos);
	uint32_t GetAnimByDirection(DIRECTION dir);
	void Update();
	void SetMode(GhostModes mode);
	void SetMoving(bool isMoving);
	void CheckModesExpireTime();
	void DoModeBehaviour(GhostModes mode);
	void TaskGoToRandomLocation();
	void TaskGoToGhostHouse();
	void ScatterBehaviour();
	void PlayDeadSound();
	bool CanGotoOppositeDirection();
	GhostModes GetMode();
protected:
	void UpdateMovement();
	void UpdateAnim();
	bool CanGotoDirection(DIRECTION dir);
	DIRECTION GetOptimalTargetDirection();
	sf::Sprite* m_shape;
	sf::RenderWindow* m_screen;
	Game* m_gameInstance;
	DIRECTION m_dir;
	bool m_isDead;
	bool m_isMoving;
	bool m_isFlashing;
	uint32_t m_animFrame;
	uint32_t m_animFrameNum;
	std::vector<DIRECTION> blockedDirs;
	sf::Clock m_deltaT;
	sf::Clock m_deltaTMode;
	sf::Clock m_deltaTFlashing;
	PathFinder::CoordinateList m_optimalPath;
	uint32_t m_currentPathIndex;
	std::vector<Ghost*> m_debugGhostPathShapes;
	std::string m_deadSound;
	sf::Sprite* m_faceShape;//
	GhostModes m_mode;
	GhostType m_ghostType;
	sf::Vector2f m_targetLocation;
	MapCoords m_targetMapLocation;
	bool m_isOnFinalPathDestination;
	MapCoords m_ghostMapLocation;


};
