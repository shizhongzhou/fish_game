/**@file Struct.h
* @brief      player and fish obj defined header of projecy
* @details  contained structs of player and fish
* @author      me
* @date        2024/06/20
**********************************************************************************
*/

#pragma once

/**
* @struct player
* @brief Save info of player
*/
struct player
{
	int x;
	int y;
	bool live = true;
	int size = 1;
	int score = 0;
};

/**
* @struct fish
* @brief Save info of player
*/
struct fish
{
	int x;
	int y;
	int size;
	bool live = true;
};