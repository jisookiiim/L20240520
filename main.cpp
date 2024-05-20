#include <iostream>
#include <string>

using namespace std; 

int PlayerCard[10] = { 0, };
int ComputerCard[10] = { 0, };

int PlayerTotal = 0; 
int ComputerTotal = 0; 

int Cards[52] = { 0, };

string CardType[4] = {"¡ß", "¢¼", "¢À", "¢¾"};


void Shuffle()
{
	for (int i = 0; i < 52; i++)
	{
		Cards[i] = i;
	}
	for (int i = 0; i < 10000; i++)
	{
		int FirstCard = rand() % 52; 
		int SecondCard = rand() % 52;
		int Temp = Cards[FirstCard]; 
		Cards[FirstCard] = Cards[SecondCard]; 
		Cards[SecondCard] = Temp; 

	}
	
}

int DefineType(int CardNumber)
{
	return CardNumber / 13;

}

int DefineCard(int CardNumber)
{
	return ((CardNumber % 12) + 1);
}

void DrawCard()
{
	int CardCount = 0;
	for (int i = 0; i < 2; i++)
	{
		PlayerCard[i] = Cards[CardCount]; 
		PlayerTotal += DefineCard(PlayerCard[i]);
		CardCount++;
	}

	for (int i = 0; i < 2; i++)
	{
		ComputerCard[i] = Cards[CardCount];
		ComputerTotal += DefineCard(ComputerCard[i]);
		CardCount++;
	}
	
}

void DetermineGame()
{

	if (ComputerTotal > 21)
	{
		cout << "You Win" << endl;
	}
	else if (ComputerTotal <= 21 && PlayerTotal > 21)
	{
		cout << "You Lose" << endl;
	}
	else //(ComputerTotal <= 21 && PlayerTotal <= 21)
	{
		if (ComputerTotal > PlayerTotal)
		{
			cout << "You Lose" << endl;
		}
		else
		{
			cout << "You Win" << endl;
		}
	}
}

void ShowCard()
{


	cout << "Player" << endl;
	for (int i = 0; i < 2; i++)
	{
		cout << CardType[DefineType(PlayerCard[i])];
		cout << DefineCard(PlayerCard[i]) << endl;

	}

	cout << "Computer" << endl;
	for (int i = 0; i < 2; i++)
	{
		cout << CardType[DefineType(ComputerCard[i])];
		cout << DefineCard(ComputerCard[i]) << endl;
	}

}

int main()
{
	srand(unsigned int((time_t*)nullptr)); 

	Shuffle();
	DrawCard(); 
	ShowCard();
	DetermineGame();

	return 0;
}