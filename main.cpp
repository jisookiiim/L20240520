#include <iostream>

using namespace std;


//custom DataType
struct Vector2D
{
	int X;
	int Y;
	//int�� 4����Ʈ = 8����Ʈ 
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
	//3����Ʈ 
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
	Player->name = "�ٺ�";

	cout << Player->Position.X << endl;

	delete Player;

	return 0;
}

