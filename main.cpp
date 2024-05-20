#include <iostream>
#include <conio.h>    // Windows용 비차단 입력 함수 포함
#include <windows.h>  // Sleep 함수를 사용하기 위한 헤더
#include <cstdlib>    // 일반적인 유틸리티 함수 포함
#include <ctime>      // 시간 관련 함수들 포함
#include <chrono>     // 시간 관련 라이브러리

using namespace std;
using namespace chrono;

// 플레이어의 위치와 모양을 저장하는 변수
int PlayerX = 1;
int PlayerY = 1;
char PlayerShape = 'P';

// 몬스터의 위치와 모양을 저장하는 변수
int MonsterX = 5;
int MonsterY = 5;
char MonsterShape = 'M';

// 목표의 위치와 모양을 저장하는 변수
int GoalX = 8;
int GoalY = 8;
char GoalShape = 'G';

// 바닥과 벽의 모양을 저장하는 변수
char FloorShape = ' ';
char WallShape = '*';

// 사용자가 입력한 값을 저장하는 변수
int Key = 0;

// 맵을 저장하는 배열
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

// 게임의 상태를 저장하는 변수
bool IsRunning = true;
bool Win = false;
bool Lose = false;

void clear_screen() {
    system("cls");
}

void sleep_ms(int milliseconds) {
    Sleep(milliseconds);
}

// 0에서 4 사이의 랜덤 숫자를 생성하는 함수
int Random0to4() {
    return rand() % 5;
}

// 사용자의 입력을 처리하는 함수
void Input() {
    if (_kbhit()) {
        Key = _getch();
    }
    else {
        Key = 0;
    }
}

// 게임의 논리를 처리하는 함수
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

// 몬스터의 랜덤 이동을 처리하는 함수
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

// 현재 게임 상태를 화면에 렌더링하는 함수
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