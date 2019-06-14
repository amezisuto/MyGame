#pragma once
class Game;
class GameManeger
{
public:
	GameManeger();
	~GameManeger();
public:
	static Game* m_game;
public:
	static void SetGame(Game* game) { m_game = game; }
	static Game* GetGame() { return m_game; }
};