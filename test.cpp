#define BOOST_TEST_MODULE basic_test
#include <time.h>
#include "Struct.h"
#include "Functions.h"
#include <boost/test/unit_test.hpp>

bool ifout(fish* fish1)
{
	if ((fish1->x < 0) || (fish1->x > (ScreenHeight - 50)))
	{
		return true;
	}
	if ((fish1->y < 0) || (fish1->y > (ScreenWidth - 50)))
	{
		return true;
	}
	else
	{
		return false;
	}
}

BOOST_AUTO_TEST_SUITE(some_suite)

BOOST_AUTO_TEST_CASE(test_struct_init)
{
	BOOST_TEST_MESSAGE("Start test struct...");
}

BOOST_AUTO_TEST_CASE(player1)
{
	BOOST_TEST_MESSAGE("test1 for struct player initalization.");
	player init;
	BOOST_TEST(init.x == NULL, "var player pos.x doesnot initalize.");
	BOOST_TEST(init.y == NULL, "var player pos.x doesnot initalize.");
	BOOST_TEST(init.live == true, "judge player living which should be true when initalizing.");
	BOOST_TEST(init.size == 1, "player size which should be 1.");
	BOOST_TEST(init.score == 0, "player size which should be 0.");
}

BOOST_AUTO_TEST_CASE(player2)
{
	BOOST_TEST_MESSAGE("test2 for struct player initalization.");
	player init;
	BOOST_TEST(init.x == 1, "var player pos.x doesnot define.");
	BOOST_TEST(init.y == 1, "var player pos.x doesnot define.");
	BOOST_TEST(init.live == false, "judge player living which should be true when initalizing.");
	BOOST_TEST(init.size == 0, "player size which should be 1.");
	BOOST_TEST(init.score > 0, "player size which should be 0.");
}

BOOST_AUTO_TEST_CASE(fish1)
{
	BOOST_TEST_MESSAGE("test3 for struct fish initalization.");
	fish init;
	BOOST_TEST(init.x == NULL, "var fish pos.x doesnot initalize.");
	BOOST_TEST(init.y == NULL, "var fish pos.y doesnot initalize.");
	BOOST_TEST(init.live == true, "judge fish living which should be true when initalizing.");
	BOOST_TEST(init.size == 1, "fish size which should be 1.");
}

BOOST_AUTO_TEST_CASE(fish2)
{
	BOOST_TEST_MESSAGE("test4 for struct player initalization.");
	fish init;
	BOOST_TEST(init.x == 1, "var fish pos.x doesnot defined.");
	BOOST_TEST(init.y == 1, "var fish pos.y doesnot defined.");
	BOOST_TEST(init.live == false, "judge fish living which should be true when initalizing.");
	BOOST_TEST(init.size > 1, "fish size which should be 1.");
}

BOOST_AUTO_TEST_CASE(test_struct_end)
{
	BOOST_TEST_MESSAGE("End test struct...");
}

BOOST_AUTO_TEST_CASE(test_functions_init)
{
	BOOST_TEST_MESSAGE("Start test functions...");
}

BOOST_AUTO_TEST_CASE(game_init)
{
	BOOST_TEST_MESSAGE("test5 for game functions.");
	player player1;
	fish bigfish[numB];
	fish littlefish[numL];
	fish shrimp[numS];
	srand(unsigned(time(0)));
	// Player initial position
	BOOST_TEST_MESSAGE("Start to initalize player's pos...");
	player* player2 = &player1;
	player2->x = rand() % (ScreenHeight - 50);
	player2->y = rand() % (ScreenWidth - 50);
	BOOST_TEST_MESSAGE("Detect the pos of player in screen...");
	BOOST_CHECK(player2->x > 0 && player2->x < 640, "Detect the pos.x of player between 0 and 640.");
	BOOST_CHECK(player2->y > 0 && player2->y < 480, "Detect the pos.y of player between 0 and 480.");
	BOOST_TEST_MESSAGE("End detect the pos of player in screen...");
	BOOST_TEST_MESSAGE("Detect the struct of different kinds of fishes...");
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
	BOOST_TEST_MESSAGE("Detect the shrimp1.");
	for (int i = 0; i < numS; i++)
	{
		//shrimp1[i] = &shrimp[i];
		BOOST_CHECK(shrimp1[i] == &shrimp[i], "Check if the pointer of shrimp is useful.");
		//shrimp1[i]->x = rand() % (ScreenHeight - 50);
		BOOST_CHECK(shrimp1[i]->x > 0 && shrimp1[i]->x < 640, "Judge if the pos.x of shrimp is between 0 and 640.");
		//shrimp1[i]->y = rand() % (ScreenWidth - 50);
		BOOST_CHECK(shrimp1[i]->y > 0 && shrimp1[i]->y < 480, "Judge the pos.y of shrimp is between 0 and 480.");
		//shrimp1[i]->size = 0;
		BOOST_CHECK(shrimp1[i]->size == 0, "Judge the size of shrimp is 0.");
	}
	BOOST_TEST_MESSAGE("End detect the shrimp1.");
	BOOST_TEST_MESSAGE("Detect the littlefish1.");
	for (int i = 0; i < numL; i++)
	{
		/*littlefish1[i] = &littlefish[i];
		littlefish1[i]->x = rand() % (ScreenHeight - 50);
		littlefish1[i]->y = rand() % (ScreenWidth - 50);
		littlefish1[i]->size = 1;*/
		BOOST_CHECK(littlefish1[i] == &littlefish[i], "Check if the pointer of shrimp is useful.");
		BOOST_CHECK(littlefish1[i]->x > 0 && littlefish1[i]->x < 640, "Judge if the pos.x of littlefish1 is between 0 and 640.");
		BOOST_CHECK(littlefish1[i]->y > 0 && littlefish1[i]->y < 480, "Judge the pos.y of littlefish1 is between 0 and 480.");
		BOOST_CHECK(littlefish1[i]->size == 1, "Judge the size of littlefish1 is 1.");
	}
	BOOST_TEST_MESSAGE("End detect the littlefish1.");
	BOOST_TEST_MESSAGE("Detect the bigfish1.");
	for (int i = 0; i < numB; i++)
	{
		/*bigfish1[i] = &bigfish[i];
		bigfish1[i]->x = rand() % (ScreenHeight - 50);
		bigfish1[i]->y = rand() % (ScreenWidth - 50);
		bigfish1[i]->size = 2;*/
		BOOST_CHECK(bigfish1[i] == &bigfish[i], "Check if the pointer of shrimp is useful.");
		BOOST_CHECK(bigfish1[i]->x > 0 && bigfish1[i]->x < 640, "Judge if the pos.x of littlefish1 is between 0 and 640.");
		BOOST_CHECK(bigfish1[i]->y > 0 && bigfish1[i]->y < 480, "Judge the pos.y of littlefish1 is between 0 and 480.");
		BOOST_CHECK(bigfish1[i]->size == 2, "Judge the size of littlefish1 is 1.");
	}
	BOOST_TEST_MESSAGE("End detect the bigfish1.");
}
BOOST_AUTO_TEST_CASE(game)
{
	BOOST_TEST_MESSAGE("Game initalizing...");
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
	BOOST_TEST_MESSAGE("End initalizing...");
	BOOST_TEST_MESSAGE("Start test...");
	BOOST_TEST_MESSAGE("Judge if shrimp1 is in screen...");
	BOOST_TEST_MESSAGE("If any shrimp1 out of screen then reborn a fish instrad.");
	while (shrimp1[0]->x > 0 && shrimp1[0]->x < 640 && shrimp1[0]->y > 0 && shrimp1[0]->y < 480)
	{
		BOOST_TEST_MESSAGE("Random move fish...");
		movefish(shrimp1[0]);
		BOOST_CHECK(shrimp1[0]->x > 0 && shrimp1[0]->x < 640 && shrimp1[0]->y > 0 && shrimp1[0]->y < 480);
	}
	BOOST_TEST_MESSAGE("Fish doesnot in screen...");
	BOOST_TEST_MESSAGE("End test.");
}

BOOST_AUTO_TEST_CASE(test_functions_end)
{
	BOOST_TEST_MESSAGE("End test functions...");
}

BOOST_AUTO_TEST_SUITE_END();
