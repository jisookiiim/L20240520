#include <iostream>
#include <conio.h>    // Windows�� ������ �Է� �Լ� ����
#include <windows.h>  // Sleep �Լ��� ����ϱ� ���� ���
#include <cstdlib>    // �Ϲ����� ��ƿ��Ƽ �Լ� ����
#include <ctime>      // �ð� ���� �Լ��� ����
#include <chrono>     // �ð� ���� ���̺귯��

using namespace std;
using namespace chrono;

// �÷��̾��� ��ġ�� ����� �����ϴ� ����
int PlayerX = 1;
int PlayerY = 1;
char PlayerShape = 'P';

// ������ ��ġ�� ����� �����ϴ� ����
int MonsterX = 5;
int MonsterY = 5;
char MonsterShape = 'M';

// ��ǥ�� ��ġ�� ����� �����ϴ� ����
int GoalX = 8;
int GoalY = 8;
char GoalShape = 'G';

// �ٴڰ� ���� ����� �����ϴ� ����
char FloorShape = ' ';
char WallShape = '*';

// ����ڰ� �Է��� ���� �����ϴ� ����
int Key = 0;

// ���� �����ϴ� �迭
int World[10][10] = {
    { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
    { 1, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
    { 1, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
    { 1, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
    { 1, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
    { 1, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
    { 1, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
    { 1, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
    { 1, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
    { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }
};

// ������ ���¸� �����ϴ� ����
bool IsRunning = true;
bool Win = false;
bool Lose = false;

void clear_screen() {
    system("cls");
}

void sleep_ms(int milliseconds) {
    Sleep(milliseconds);
}

// 0���� 4 ������ ���� ���ڸ� �����ϴ� �Լ�
int Random0to4() {
    return rand() % 5;
}

// ������� �Է��� ó���ϴ� �Լ�
void Input() {
    if (_kbhit()) {
        Key = _getch();
    }
    else {
        Key = 0;
    }
}

// ������ ���� ó���ϴ� �Լ�
void Tick() {
    int newX = PlayerX;
    int newY = PlayerY;

    if (Key == 'w') newY--;
    if (Key == 's') newY++;
    if (Key == 'a') newX--;
    if (Key == 'd') newX++;

    if (Key == 27) IsRunning = false;

    if (World[newY][newX] == 0) {
        PlayerX = newX;
        PlayerY = newY;
    }

    if (PlayerX == GoalX && PlayerY == GoalY) {
        Win = true;
        IsRunning = false;
    }

    if (PlayerX == MonsterX && PlayerY == MonsterY) {
        Lose = true;
        IsRunning = false;
    }
}

// ������ ���� �̵��� ó���ϴ� �Լ�
void MonsterMove() {
    int newX = MonsterX;
    int newY = MonsterY;
    int move = Random0to4();

    switch (move) {
    case 1: newY--; break;
    case 2: newY++; break;
    case 3: newX--; break;
    case 4: newX++; break;
    }

    if (World[newY][newX] == 0) {
        MonsterX = newX;
        MonsterY = newY;
    }

    if (MonsterX == PlayerX && MonsterY == PlayerY) {
        Lose = true;
        IsRunning = false;
    }
}

// ���� ���� ���¸� ȭ�鿡 �������ϴ� �Լ�
void Render() {
    clear_screen();

    for (int Y = 0; Y < 10; Y++) {
        for (int X = 0; X < 10; X++) {
            if (PlayerX == X && PlayerY == Y) {
                cout << PlayerShape;
            }
            else if (GoalX == X && GoalY == Y) {
                cout << GoalShape;
            }
            else if (MonsterX == X && MonsterY == Y) {
                cout << MonsterShape;
            }
            else if (World[Y][X] == 0) {
                cout << FloorShape;
            }
            else if (World[Y][X] == 1) {
                cout << WallShape;
            }
        }
        cout << endl;
    }

    if (Win) {
        cout << "\nYou win!" << endl;
    }
    else if (Lose) {
        cout << "\nYou lose!" << endl;
    }
}

int main() {
    srand(static_cast<unsigned int>(time(0)));
    auto lastMoveTime = steady_clock::now();

    while (IsRunning) {
        Input();
        Tick();
        Render();

        auto now = steady_clock::now();
        auto elapsed = duration_cast<milliseconds>(now - lastMoveTime).count();

        if (elapsed >= 500) {
            MonsterMove();
            lastMoveTime = now;
        }

        sleep_ms(100);
    }

    Render();

    return 0;
}