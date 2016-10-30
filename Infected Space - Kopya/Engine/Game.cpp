/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.cpp																			  *
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
#include "MainWindow.h"
#include "Game.h"
#include <stdio.h>
#include <dos.h>
#include <time.h>

Game::Game(MainWindow& wnd)
	:
	wnd(wnd),
	gfx(wnd)
{
	
	for (int x = 0; x <= 39; x++) {
		for (int y = 1; y <= 1000; y++) {
			SetGridState(x, y, black);
		}

	}


}

void Game::Go()
{
	gfx.BeginFrame();	
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel()
{
	
}



void Game::DrawCircle(int mx, int my, int rad,int r, int g , int b) {
	for (int X = -rad; X < rad; X++) {
		// rad*rad = X*X + Y*Y
		// Y*Y = rad*rad - X*X
		int Y = sqrt(rad*rad - X*X) + 0.5f;

		gfx.PutPixel  (X + mx, Y + my, r, g, b);
		gfx.PutPixel (X + mx, -Y + my, r, g, b);
									   
		gfx.PutPixel  (Y + mx, X + my, r, g, b);
		gfx.PutPixel (Y + mx, -X + my, r, g, b);

		gfx.PutPixel (-Y + mx, X + my, r, g, b);
		gfx.PutPixel(-Y + mx, -X + my, r, g, b);

	}
}
void Game::DrawLine(int x1, int y1, int x2, int y2,int r ,int g , int b) {
	float dx = x2 - x1;
	float dy = y2 - y1;
	float m = dy / dx;
	// m  = (Y-y1)/(X-x1)
	// m*(X - x1) + y1 = Y
	// (Y-y1)/m + x1 = X
	// int Y = m*(X - x1) + y1 + 0.5f;
	// int X = (Y - y1) / m + x1 + 0.5f;
	if (x1 > x2) {
		int temp;
		temp = x2;
		x2 = x1;
		x1 = temp;
		temp = y2;
		y2 = y1;
		y1 = temp;
	}
	for (int X = x1; X < x2; X++) {
		int Y = m*(X - x1) + y1 + 0.5f;
		gfx.PutPixel(X, Y, r, g, b);
	}
	if (y1 > y2) {
		int temp;
		temp = x2;
		x2 = x1;
		x1 = temp;
		temp = y2;
		y2 = y1;
		y1 = temp;
	}
	for (int Y = y1; Y < y2; Y++) {
		int X = (Y - y1) / m + x1 + 0.5f;
		gfx.PutPixel(X, Y, r, g, b);
	}

}

void Game::DrawX(int x, int y) {
	DrawLine(0 + x, 0+y, 100+x, 100 +y, 255, 255, 255);
	DrawLine(100 + x, 0+y, 0+x, 100 +y, 255, 255, 255);
}
void Game::DrawO(int x, int y) {
	DrawCircle(x + 50, y + 50,50, 255, 255, 255);
}
void Game::DrawWave(int x, int y) {

}

void Game::DrawParticle(int r, int g, int b) {

	

	ParticleVY[particleNUM] = ParticleVY[particleNUM] + gForce/10;

	if (ParticleVX[particleNUM] >= 0) { ParticleVX[particleNUM] = ParticleVX[particleNUM] - AirResistance; }
	if (ParticleVX[particleNUM] <  0) { ParticleVX[particleNUM] = ParticleVX[particleNUM] + AirResistance; }
	if (ParticleVY[particleNUM] >= 0) { ParticleVY[particleNUM] = ParticleVY[particleNUM] - AirResistance; }
	if (ParticleVY[particleNUM] <  0) { ParticleVY[particleNUM] = ParticleVY[particleNUM] + AirResistance; }


	ParticleX[particleNUM] = ParticleX[particleNUM] + ParticleVX[particleNUM];
	ParticleY[particleNUM] = ParticleY[particleNUM] + ParticleVY[particleNUM];


	if (ParticleRad[particleNUM] <= 10) {

		DrawCircle(ParticleX[particleNUM], ParticleY[particleNUM], ParticleRad[particleNUM], r, g, b);
	}



	else if (ParticleRad[particleNUM] == 11) {
		ParticleX[particleNUM] = -1000000;
		ParticleY[particleNUM] = -1000000;
		ParticleVX[particleNUM] = 0;
		ParticleVY[particleNUM] = 0;
	}
}
void Game::DrawThruster(int x, int y, int vx, int vy) {
	

	if (time % 5 == 2) {
		int no = rand() % 500;

		ParticleRad[no] = 1;
		ParticleX[no] = x;
		ParticleY[no] = y;

		float VX = (float)vx + SpaceshipVX - 1 + rand()%3;
		float VY = (float)vy + SpaceshipVY - 1 + rand()%3;

		ParticleVX[no] = VX;
		ParticleVY[no] = VY;

	}

	
}
void Game::DrawSpaceship(int x, int y) {

	DrawCircle(x, y, 20, 30, 255, 100);
	
	DrawCircle(x + 25, y + 8, 9, 30, 255, 100);
	
	DrawCircle(x - 25, y + 8, 9, 30, 255, 100);
	
	if (RightEngineOn == true) {
		DrawThruster(x + 25, y + 8, 5, 5);
	}
	if (LeftEngineOn == true) {
		DrawThruster(x -25, y + 8, -5, 5);
	}
	
}

Game::GridState Game::GetGridState(int GridX, int GridY) {

	return Grid[GridX][GridY];
}
void Game::SetGridState(int GridX, int GridY, GridState state) {

	Grid[GridX][GridY] = state;

}

void Game::DrawBlock(int GridX, int GridY) {

	if (GridX <= 40 && GridX >= 0) {
		int x = GridX * 20 + 10;
		int y = GridY * 20 + 10 - 20 * 1000;

		if (x >= -10 && x <= 810 && y + BlocksMoved <= 610 && y + BlocksMoved >= -10) {

			DrawCircle(x, y + BlocksMoved, 9, 255, 0, 0);
		}
	}
}
void Game::SpawnBlock(int GridX, int GridY) {
	SetGridState(GridX, GridY, green);

}

void Game::SpaceShipShoot() {
	BulletVX = SpaceshipVX * 1.5f;
	BulletVY = SpaceshipVY - 10;
	BulletX = SpaceshipX;
	BulletY = SpaceshipY;

}
void Game::DestroyParticle(int particleNUM) {
	ParticleX[particleNUM] = -1000000;
	ParticleY[particleNUM] = -1000000;
	ParticleVX[particleNUM] = 0;
	ParticleVY[particleNUM] = 0;
	
}

bool Game::BlockIsShot(int GridX, int GridY) {
	float BlockX = GridX * 20 + 10;
	float BlockY = GridY * 20 + 10 - 20 * 1000 + BlocksMoved;
	
	float distance = sqrt((BlockY - BulletY)*(BlockY - BulletY) + (BlockX - BulletX)*(BlockX - BulletX));

	if (distance <= 20) {	return true;    }
	if (distance >  20)  {	return false;	}

}

void Game::DrawBullet(int r,int g,int b) {
	BulletVY = BulletVY + gForce / 10;

	if (BulletVX >= 0) { BulletVX = BulletVX - AirResistance; }
	if (BulletVX <  0) { BulletVX = BulletVX + AirResistance; }
	if (BulletVY >= 0) { BulletVY = BulletVY - AirResistance; }
	if (BulletVY <  0) { BulletVY = BulletVY + AirResistance; }


	BulletX = BulletX + BulletVX;
	BulletY = BulletY + BulletVY;


	

		DrawCircle(BulletX, BulletY, 10, r, g, b);
	
	
		
	
}
//  !!
bool Game::PlayerIsCrushedToBlock(int GridX, int GridY) {
	
	float BlockX = GridX * 20 + 10;
	float BlockY = GridY * 20 + 10 - 20 * 1000 + BlocksMoved;

	float distance = sqrt((BlockY - SpaceshipY)*(BlockY - SpaceshipY) + (BlockX - SpaceshipX)*(BlockX - SpaceshipX));

	if (distance <= 40) { return true; }
	if (distance >  40) { return false; }

}

void Game::ComposeFrame()
{
	LeftEngineOn = false;
	RightEngineOn = false;

	if (wnd.kbd.KeyIsPressed(VK_UP))    {  }
	if (wnd.kbd.KeyIsPressed(VK_DOWN))  {  }
	if (wnd.kbd.KeyIsPressed(VK_LEFT)) { 
		RightEngineOn = true;
		SpaceshipVX = SpaceshipVX - 0.1f;
		SpaceshipVY = SpaceshipVY - 0.1f;
	}
	if (wnd.kbd.KeyIsPressed(VK_RIGHT)) { 
		LeftEngineOn = true;
		SpaceshipVX = SpaceshipVX + 0.1f;
		SpaceshipVY = SpaceshipVY - 0.1f;
	
	}
	if (wnd.kbd.KeyIsPressed(VK_RIGHT) && wnd.kbd.KeyIsPressed(VK_LEFT)) {
		SpaceshipVY = SpaceshipVY - 0.1f;
	}

	SpaceshipVY = SpaceshipVY + gForce;

	SpaceshipX = SpaceshipX + SpaceshipVX;
	SpaceshipY = SpaceshipY + SpaceshipVY;

	DrawSpaceship(SpaceshipX, SpaceshipY);

	//DrawThruster(50, 450, 5, -5);
	//DrawThruster(750, 450, -5, -5);
	
	
	for (int cycler = 0; cycler < 500; cycler++) {

		particleNUM = cycler;
		DrawParticle(255, 200, 200);

	}
	for (int index = 0; index < 500; index++) {
		ParticleRad[index] = ParticleRad[index] + 0.1f;
	}

	
	//spawn all blocks once
	if (time == 5) {
		for (int GridY = 1; GridY <= 1000; GridY++) {
			for (int GridX = 0; GridX <= 39; GridX++) {
				SpawnBlock(GridX, GridY);
			}
		}
	}
	//Check bullets and player colliding with blocks
	 	for (int GridY = 1; GridY <= 1000; GridY++) {
			for (int GridX = 0; GridX <= 39; GridX++) {
				if (BlockIsShot(GridX, GridY) == true) {
					SetGridState(GridX, GridY, black);
				}
				if (PlayerIsCrushedToBlock(GridX, GridY) == true) {
					GameOver == true;
				}

			}
		}
	

	
	
	
	//Block drawing cycle
	for (int GridY = 1; GridY <= 1000; GridY++) {
		for (int GridX = 0; GridX <= 39; GridX++) {	
			if (GetGridState(GridX, GridY) == green) {	
				DrawBlock(GridX, GridY);
			}
			if (GetGridState(GridX, GridY) == black) {
				if (GetGridState(GridX - 1, GridY) == green || GetGridState(GridX + 1, GridY) == green || GetGridState(GridX, GridY + 1) == green || GetGridState(GridX, GridY - 1) == green) {
					if (rand() % 3000 == 1) {
						SetGridState(GridX, GridY, green);
					}
				}
			}
		}

	}

	//shootin'
	if (time % 60 == 1) {
		SpaceShipShoot();
	}
	DrawBullet(255,255,255);
	

	BlocksMoved = BlocksMoved + 0.5f;
	time++;

	//check for gameover
	if (GameOver == true) {
		for (int x = 0; x < 800; x++) {
			for (int y = 0; y < 600; y++) {
				gfx.PutPixel(x, y, 255, 0, 0);
			}
		}

	}

}
