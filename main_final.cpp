/*
Amit Sant and Ronuk Ray

Vintage spaceship video game. Objective of game is to shoot  down falling asteroids and stop them from hitting the planet below.
*/


#include <iostream>
#include <windows.h>
#include <time.h>
#include <fstream>
#include <string>

bool gameOver;
int score;
int pos;
int projectiles[20][100];
int lives;
int highscore;

using namespace std;

//TESTING FUNCTION TO PRINT OUT GAME ARRAY

void PrintArray()
{
	for(int i = 0; i<20;i++)
    {
		for(int j=0;j<100;j++)
        {
			cout<<projectiles[i][j];
		}
		cout<<endl;
	}
}
void HandleKeyStrokes()
{
	if(GetKeyState('D') & 0x8000)
	{
		if(pos <= 100) //right bound
        {
			pos += 5;
		}
	}
	if(GetKeyState('A') & 0x8000)
	{
		if(pos >= 0) //left bound
        {
		 pos -= 5;
		}
	}
}
//random number, top row
void SpawnEnemies()
{
	srand(time(NULL));
	if(rand() % 5 == 0)
    {
		projectiles[0][rand() % 99] = -1; 
	}	
}
void DrawShip()
{
	string adder = "";
    for(int i=0;i<pos;i++)
    {
        adder+=" ";
    }
	cout<<adder<<"    ^"<<endl
        <<adder<<"   / \\"<<endl
        <<adder<<"  / * \\"<<endl
        <<adder<<" / o o \\"<<endl
        <<adder<<"/_______\\"<<endl
        <<adder<<"\\/\\/ \\/\\/"<<endl;
	cout << endl;
}
void DrawBoard()
{
	for(int i = 0; i < 20; i++) 
	{
		cout<<"    ";
		for(int j = 0; j < 100; j++) 
		{
			int id = projectiles[i][j];
			if(id == 1) 
			{
				cout << "|";
			}
			else if(id == -1) 
			{
				cout << "*";
			}
			else if(id == 0) 
			{
				cout << " ";
			}
		}
		cout << endl;
	}
	cout << endl;
}
void Setup()
{
    gameOver=false;
    score = 0;
	pos = 50;
	lives = 10;
	
	//read in high score
	ifstream highscore_f;
	highscore_f.open("high.score");
	highscore_f >> highscore;
}

void Draw()
{
	//clear last frame
	system("cls");
	
	DrawBoard();
	
	//draw ship
	
    DrawShip();
	
	//Update score and lives
	cout << "Score: " << score << endl;
	cout << "Lives: " << lives << endl;
	cout << "High Score: " << highscore << endl;
}
void UpdateProjectilePosition()
{
    //moving down enemies
    for (int j = 0; j<100; j++)
    {
        for (int i = 19; i>-1; i--)
        {
            if (projectiles[i][j]==-1&&i<19)
            {
                projectiles[i+1][j]-=1;
                if(projectiles[i+1][j]==0)
                {
                    score+=100;
                }
                projectiles[i][j]++;
            }
            else if (projectiles[i][j]==-1)
            {
                projectiles[i][j]-=-1;
                lives--;
            }
        }
    }
    
    
    //moving up pipes
    for (int j = 0; j < 100; j++)
    {
        for (int i = 0; i < 20; i++)
        {
            if(projectiles[i][j]== 1 && i > 0)
            {
                projectiles[i-1][j] = 1;
                if(projectiles[i-1][j]==0)
                {
                    score+=100;
                }
                projectiles[i][j] = 0;
            }
            else if(projectiles[i][j]== 1 && i == 0)
            {
                projectiles[i][j] = 0;
            }
        }
    }
}
void ShootGun()
{
    if(pos != 0)
    {
        projectiles[19][pos - 1] = 1;
    }
    projectiles[19][pos] = 1;
    if(pos != 99)
    {
        projectiles[19][pos + 1] = 1;
    }
}
void CheckIfGameOver()
{
    if(lives <= 0)
    {
        gameOver = true;
    }
}
void Update()
{
	HandleKeyStrokes();
	SpawnEnemies();
    UpdateProjectilePosition();
    ShootGun();
    CheckIfGameOver();
    Draw();
}

void showGameOver()
{
	ifstream message;
	message.open("game_over.txt");
	string line;
	while (getline(message, line))
	{
		cout << line << endl;
	}
}
void ProcessHighScores()
{
    if(score > highscore) {
        highscore = score;
		ofstream score_f;
		score_f.open("high.score");
		score_f << score;
		cout<<endl<<endl<<"Congrats! You set the HIGH SCORE"<<endl;
    }
}


int main(int argc, const char * argv[])
{
	Setup();
    //game loop
    while(!gameOver)
    {
		Sleep(100);
        Update();
    }
	showGameOver();
    ProcessHighScores();
	
    return 0;
}
