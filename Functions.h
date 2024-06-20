/**@file  Functions.h
* @brief      main header of projecy
* @details  contained game functions
* @author      me
* @date        2024/06/20
**********************************************************************************
*/
// Functions.h
#ifndef _Functions_H
#define _Functions_H

#include "easyx/Include/easyx.h"
#include <conio.h>
#include <time.h>
#include <iostream>                // Header file
#pragma comment(lib,"winmm.lib")   // Link static library
#pragma comment(lib,"easyx/lib/VC2015/x64/EasyXw.lib")
#include "Struct.h"
using namespace std;

/***************************************Global Variables****************************************************/
const short ScreenWidth = 480;
const short ScreenHeight = 640;
short ret = 0;
int ToBig = 10;
/************** Number of NPC fish ****************/
const int numB = 1; // Number of big fish
const int numL = 2; // Number of small fish
const int numS = 3; // Number of shrimp
IMAGE Fish[3]; // Fish images
IMAGE lplayerfish[2]; // Player fish images (left)
IMAGE rplayerfish[2]; // Player fish images (right)
IMAGE background; // Background image
short Formerx = 0; // For turning
short Formery = 0; // For turning
const int N = 50; // Image size

/**
* @brief Loadimgs
*/
extern void loadImages() 
{
    loadimage(&Fish[2], L"bigfish.jpg", 2 * N, 2 * N);
    loadimage(&Fish[1], L"littlefish.jpg", N, N);
    loadimage(&Fish[0], L"shrimp.jpg", N, N);
    loadimage(&background, L"background.jpg", ScreenHeight, ScreenWidth);
    loadimage(&lplayerfish[0], L"lplayerlittlefish.jpg", N, N);
    loadimage(&lplayerfish[1], L"lplayerbigfish.jpg", 2 * N, 2 * N);
    loadimage(&rplayerfish[0], L"rplayerlittlefish.jpg", N, N);
    loadimage(&rplayerfish[1], L"rplayerbigfish.jpg", 2 * N, 2 * N);
}

/**
* @brief Create mask image
* @param[in] imagePut  Set the img obj u wanna mask
* @param[in] x screen pos of x that u wanna put
* @param[in] y screen pos of y that u wanna put
*/
// Create mask image
extern void changeImage(IMAGE imagePut, int x, int y)
{
    IMAGE image(N, N); // Store mask
    DWORD* pmemflower = GetImageBuffer(&imagePut);
    DWORD* image1 = GetImageBuffer(&image);
    DWORD* fish1 = GetImageBuffer(&imagePut);
    COLORREF backcolor = pmemflower[0];
    for (int i = 0; i < N * N; i++)
    {
        if (pmemflower[i] >= backcolor)
            image1[i] = WHITE;
        else
            image1[i] = BLACK;
    }
    for (int i = 0; i < N * N; i++)
    {
        if (pmemflower[i] >= backcolor)
            fish1[i] = BLACK;
    }
    putimage(x, y, &image, SRCAND);
    putimage(x, y, &imagePut, SRCPAINT);
}

/**
* @brief Create specific size mask image
* @param[in] imagePut  Set the img obj u wanna create
* @param[in] x screen pos of x that u wanna put
* @param[in] y screen pos of y that u wanna put
*/
// Create specific size mask image
extern void changeImage2(IMAGE imagePut, int x, int y)
{
    IMAGE image(100, 100); // Store mask
    DWORD* pmemflower = GetImageBuffer(&imagePut);
    DWORD* image1 = GetImageBuffer(&image);
    DWORD* fish1 = GetImageBuffer(&imagePut);
    COLORREF backcolor = pmemflower[0];
    for (int i = 0; i < 100 * 100; i++)
    {
        if (pmemflower[i] >= backcolor)
            image1[i] = WHITE;
        else
            image1[i] = BLACK;
    }
    for (int i = 0; i < 100 * 100; i++)
    {
        if (pmemflower[i] >= backcolor)
            fish1[i] = BLACK;
    }
    putimage(x, y, &image, SRCAND);
    putimage(x, y, &imagePut, SRCPAINT);
}

/**
* @brief Player movement function
* @param[in] player2 Put Player obj pointer
*/ 
// Player movement
extern void move(player* player2)
{
    if (GetAsyncKeyState(65) & 0x8000)  player2->x -= 10;    // Left
    if (GetAsyncKeyState(87) & 0x8000)  player2->y -= 10;    // Up
    if (GetAsyncKeyState(83) & 0x8000)  player2->y += 10;    // Down
    if (GetAsyncKeyState(68) & 0x8000)  player2->x += 10;    // Right
}

/**
* @brief NPC movement function
* @param[in] fish1 Put Fish obj pointer
*/
// NPC movement
extern void movefish(fish* fish1)
{
    fish1->x += (rand() % 21) - 10;
    fish1->y += (rand() % 21) - 10;
}

/**
* @brief Form upgrade
* @param[in] player2 Put Player obj pointer
*/
// Form upgrade
extern void biggerplayer(player* player2)
{
    if (player2->score > ToBig)
        player2->size = 2;
}

/**
* @brief NPC respawn function
* @param[in] fish1 Put Fish obj pointer
*/
// NPC respawn
extern void reborn(fish* fish1)
{
    fish1->x = rand() % (ScreenHeight - 50);
    fish1->y = rand() % (ScreenWidth - 50);
}

/**
* @brief Check if player is dead 
* @param[in] fish1 Put Fish obj pointer
* @param[in] player2 Put Player obj pointer
*/
// Check if player is dead
extern void ifDead(fish* fish1, player* player2)
{
    if (fish1->size < player2->size)
    {
        player2->score++;
        biggerplayer(player2);
        reborn(fish1);
    }
    else if (fish1->size >= player2->size)
    {
        player2->live = false;
    }
}

/**
* @brief Check if player and NPC meet
* @param[in] fish1 Put Fish obj pointer
* @param[in] player2 Put Player obj pointer
*/
// Check if player and NPC meet
extern void iftouch(fish* fish1, player* player2)
{
    if (((abs(fish1->x - player2->x) < N)) && (abs(fish1->y - player2->y) < N)) // If distance is less than N, they meet
        ifDead(fish1, player2);
}

extern void iftouch2(fish* fish1, player* player2)
{
    if (((abs(fish1->x - player2->x) < N)) && (abs(fish1->y - player2->y) < N)) // If distance is less than N, they meet
    {
        player2->score++;
        biggerplayer(player2);
        reborn(fish1);
    }
}

/**
* @brief Check if fish is out of bounds
* @param[in] fish1 Put Fish obj pointer
*/
// Check if fish is out of bounds
extern void out(fish* fish1)
{
    if ((fish1->x < 0) || (fish1->x > (ScreenHeight - 50)))
    {
        reborn(fish1);
    }
    if ((fish1->y < 0) || (fish1->y > (ScreenWidth - 50)))
    {
        reborn(fish1);
    }
}

/**
* @brief Check if player is out of bounds
* @param[in] player2 Put Player obj pointer
*/
// Check if player is out of bounds
extern void playerout(player* player2)
{
    if ((player2->x < 0) || (player2->x > ScreenHeight - 50))
        player2->live = false;
    if ((player2->y < 0) || (player2->y > ScreenWidth - 50))
        player2->live = false;
}

/**
* @brief Print scoreboard
* @param[in] player2 Put Player obj pointer
*/
// Print scoreboard
extern void ScorePrint(player* player2)
{
    setbkmode(TRANSPARENT); // Set font background color to transparent
    settextcolor(BLACK);    // Set font color to black
    TCHAR str[32] = { 0 };
    _stprintf_s(str, _T("Kills: %d"), player2->score);
    outtextxy(5, 5, str);
    _stprintf_s(str, _T("Size: %d"), player2->size);
    outtextxy(5, 25, str);
}

/**
* @brief Start game
*/
extern 
void start()
{
    player player1;
    fish bigfish[numB];
    fish littlefish[numL];
    fish shrimp[numS];
    srand(unsigned(time(0)));
    // Player initial position
    player* player2 = &player1;
    player2->x = rand() % (ScreenHeight - 50);
    player2->y = rand() % (ScreenWidth - 50);
    // Fish initial position
    fish* shrimp1[15]; // Shrimp pointer array
    for (int i = 0; i < numS; i++)
    {
        shrimp1[i] = &shrimp[i];
        shrimp1[i]->x = rand() % (ScreenHeight - 50);
        shrimp1[i]->y = rand() % (ScreenWidth - 50);
        shrimp1[i]->size = 0;
    }
    fish* littlefish1[numL]; // Little fish pointer array
    for (int i = 0; i < numL; i++)
    {
        littlefish1[i] = &littlefish[i];
        littlefish1[i]->x = rand() % (ScreenHeight - 50);
        littlefish1[i]->y = rand() % (ScreenWidth - 50);
        littlefish1[i]->size = 1;
    }
    fish* bigfish1[numB];
    for (int i = 0; i < numB; i++)
    {
        bigfish1[i] = &bigfish[i];
        bigfish1[i]->x = rand() % (ScreenHeight - 50);
        bigfish1[i]->y = rand() % (ScreenWidth - 50);
        bigfish1[i]->size = 2;
    }

    loadImages(); // Load images
    initgraph(ScreenHeight, ScreenWidth); // Load window interface
    putimage(0, 0, &background); // Place background image
    mciSendString(L"open  music.mp3 ", 0, NULL, NULL); // Place music file in the same directory as the source file, alias music means renaming this music file to music
    mciSendString(L"play music.mp3 repeat", NULL, NULL, NULL); // Play music, play means play, can also be replaced with pause: pause, stop: stop, close: close, Resume: continue. Repeat means repeat play.
    ////mciSendstring("stop music repeat", NULL, NULL, NULL); // Pause music.
    setbkmode(TRANSPARENT); // Set font background color to transparent
    settextcolor(BLACK);    // Set font color to black
    /*****************Game Rules*****************/
    outtextxy(290, 200, L"Game Rules:");
    outtextxy(290, 230, L"Player controls fish to eat fish of lower level");
    outtextxy(290, 260, L"Meeting fish of higher or same level leads to death");
    outtextxy(290, 290, L"Out of bounds leads to death");
    outtextxy(290, 320, L"Press Enter to start");
    outtextxy(290, 350, L"Press P to pause");
    outtextxy(290, 380, L"Press ESC to self-destruct");
    outtextxy(290, 410, L"Hold C to activate invincible mode");
    getchar(); // Make the start screen still, continue execution when user presses Enter

    // Program execution
    do
    {
        putimage(0, 0, &background); // Place game interface background
        ScorePrint(player2); // Print scoreboard

        // If user has not pressed C, run this mode
        if (!(GetAsyncKeyState('C') & 0x8000))
        {
            // Print NPC - Boss fish
            for (int i = 0; i < numS; i++)
            {
                movefish(shrimp1[i]); // NPC movement function
                changeImage(Fish[0], shrimp1[i]->x, shrimp1[i]->y); // Create mask image
                iftouch(shrimp1[i], player2); // Check if player and NPC meet
                out(shrimp1[i]); // Check if fish is out of bounds
            }
            // Print NPC - Small fish
            for (int i = 0; i < numL; i++)
            {
                movefish(littlefish1[i]);
                changeImage(Fish[1], littlefish1[i]->x, littlefish1[i]->y);
                iftouch(littlefish1[i], player2);
                out(littlefish1[i]);
            }
            // Print NPC - Big fish
            for (int i = 0; i < numB; i++)
            {
                movefish(bigfish1[i]);
                changeImage2(Fish[2], bigfish1[i]->x, bigfish1[i]->y);
                iftouch(bigfish1[i], player2);
                out(bigfish1[i]);
            }
        }
        // If user presses C, enter invincible mode
        else
        {
            setbkmode(TRANSPARENT); // Set font background color to transparent
            settextcolor(BLACK);    // Set font color to black
            TCHAR str[32] = { 0 };
            _stprintf_s(str, _T("Cheat mode activated")); // Notify the operator that invincible mode is activated
            outtextxy(5, 45, str);
            for (int i = 0; i < numS; i++)
            {
                movefish(shrimp1[i]);
                changeImage(Fish[0], shrimp1[i]->x, shrimp1[i]->y);
                iftouch2(shrimp1[i], player2); // If they meet, NPC dies
                out(shrimp1[i]);
            }
            for (int i = 0; i < numL; i++)
            {
                movefish(littlefish1[i]);
                changeImage(Fish[1], littlefish1[i]->x, littlefish1[i]->y);
                iftouch2(littlefish1[i], player2); // If they meet, NPC dies
                out(littlefish1[i]);
            }
            for (int i = 0; i < numB; i++)
            {
                movefish(bigfish1[i]);
                changeImage2(Fish[2], bigfish1[i]->x, bigfish1[i]->y);
                iftouch2(bigfish1[i], player2); // If they meet, NPC dies
                out(bigfish1[i]);
            }
        }

        // Player movement
        move(player2);
        if (Formerx > player2->x) // Check if turning
        {
            if (player2->size == 1)
                changeImage(lplayerfish[player2->size - 1], player2->x, player2->y);
            else changeImage2(lplayerfish[player2->size - 1], player2->x, player2->y);
        }
        else
        {
            if (player2->size == 1)
                changeImage(rplayerfish[player2->size - 1], player2->x, player2->y);
            else changeImage2(rplayerfish[1], player2->x, player2->y);
        }
        Formerx = player2->x;

        playerout(player2);
        if (GetAsyncKeyState('P') & 0x8000) // If P is pressed, pause
            ret = _getwch();
        Sleep(40); // Frame rate
    } while (player2->live == true && !(GetAsyncKeyState(VK_ESCAPE) & 0x8000)); // Continue execution as long as ESC is not pressed or player is not dead

    // Set end screen
    putimage(0, 0, &background);
    setbkmode(TRANSPARENT); // Set font background color to transparent
    settextcolor(BLACK);    // Set font color to black
    outtextxy(290, 290, L"Game Over:");
    outtextxy(290, 320, L"Press any key to exit:");
    while (_kbhit()) // Keyboard hit, exit after receiving any key
        ret = _getwch();
    ret = _getwch();
    closegraph();
}

#endif // !_Functions_H

