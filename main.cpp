#include <iostream>

using namespace std;


//custom DataType
struct Vector2D
{
	int X;
	int Y;
	//int는 4바이트 = 8바이트 
};

struct Actor
{
	Vector2D Position;
	char Shape; 
	string name; 
};

struct Color
{
	unsigned char R; 
	unsigned char G;
	unsigned char B;
	//3바이트 
};


struct Color
{
	float R; 
	float G;
	float B;
};

struct World
{
	Actor* 
};

int main()
{
	Actor* Player = new Actor;

	(*Player).Position.X;
	Player->Position.X = 10;
	Player->Position.Y = 10;
	Player->Shape = 'P';
	Player->name = "바보";

	cout << Player->Position.X << endl;

	delete Player;

	return 0;
}

