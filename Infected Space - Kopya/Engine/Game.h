/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.h																				  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#pragma once

#include "Keyboard.h"
#include "Mouse.h"
#include "Graphics.h"
#include <math.h>

class Game
{
public:
	Game( class MainWindow& wnd );
	Game( const Game& ) = delete;
	Game& operator=( const Game& ) = delete;
	void Go();
private:
	
	

	enum GridState {
		green,
		black

	};
	GridState Grid[40][1000];

	float ParticleX[500];
	float ParticleY[500];

	float ParticleVX[500];
	float ParticleVY[500];

	float ParticleRad[500];

	float BulletX = 200;
	float BulletY = 500;
	float BulletVX = 1;
	float BulletVY = -10;

	
private:
	void ComposeFrame();
	void UpdateModel();
	
	void DrawCircle(int mx, int my, int rad, int r, int g, int b);
	void DrawLine(int x1, int y1, int x2, int y2,int r ,int g , int b);
	
	void DrawX(int x, int y);
	void DrawO(int x, int y);
	void DrawWave(int x, int y);
	
	void DrawParticle(int r, int g, int b);
	void DrawThruster(int x, int y, int vx, int vy);
	void DrawSpaceship(int x, int y);

	GridState GetGridState(int GridX, int GridY);
	void SetGridState(int GridX, int GridY, GridState state);

	void DrawBlock(int GridX, int GridY);
	void SpawnBlock(int GridX, int GridY);

	void SpaceShipShoot();
	void DestroyParticle(int particleNUM);

	bool BlockIsShot(int GridX, int GridY);

	void DrawBullet(int r, int g, int b);

	bool PlayerIsCrushedToBlock(int GridX, int GridY);
	
	/********************************/
	/*  User Functions              */
	/********************************/

private:
	
	
	MainWindow& wnd;
	Graphics gfx;
	
		
	float SpaceshipX = 400;
	float SpaceshipY = 200;
	float SpaceshipVX = 0;
	float SpaceshipVY = -3;

	bool RightEngineOn = false;
	bool LeftEngineOn = false;
	
	/********************************/
	/*  User Variables              */
	int ParticleCycle = 0;
	int particleNUM = 0;

	// AirResistance = 0.03f 
	float AirResistance = 0.03f;
	
	// gForce = 0.1f 
	float gForce = 0.1f;


	// 1 second = 60 time
	int time = 0;
	bool GameOver = false;
	
	float BlocksMoved = 0;
	/********************************/
};