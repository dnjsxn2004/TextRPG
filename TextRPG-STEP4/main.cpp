#include <iostream>
#include "player.h"
#include "Archer.h"
#include "warrior.h"
#include "Magician.h"
#include "Thief.h"
#include "Monster.h"
#include "Goblin.h"
#include "Slime.h"
#include <vector>
#include <cstdlib>
#include <ctime>



using namespace std;

// 플레이어 스탯 출력
void printStatus(string name, int stat[]) // 플레이어 스탯 출력
{

	cout << "================================" << endl;
	cout << "        " << name << "'s Stats" << endl;
	cout << "================================" << endl;

	cout << "HP : " << stat[0] << "      " << "MP : " << stat[1] << endl;
	cout << "Attack : " << stat[2] << "      " << "Defense : " << stat[3] << endl;

}
//stat[0] : HP
//stat[1] : MP
//stat[2] : AP - 공격력
//stat[3] : DP - 방어력

// 시작포션 지급 프린트
void PrintStatUp(int HPPotion, int MPPotion)
{
	cout << "* You recived " << HPPotion << " HP Potions and " << MPPotion << " MP Potions." << endl;
	cout << "================================" << endl;
	cout << "< Character Upgrade > " << endl;
	cout << "1. HP UP  " << " 2. MP UP  " << " 3. Attack x2  " << endl;
	cout << "4. Defense x2  " << " 5. Show Stats  " << " 0. Start Game  " << endl;
	cout << "================================" << endl;
	cout << "Choose:";
	
}

// 직업 선택 프린트
void PrintClassChange(string name)
{
	cout << "< Job Selection >" << endl;
	cout << name << ", choose your job!" << endl;
	cout << "1. Warrior  2. Mage  3. Rogue  4. Archer" << endl;
	cout << "choose: ";
}

// 직업별 공격 메세지 프린트
void PrintClassMessge(Player* player)
{
	cout << endl;
	player->printPlayerSelectionMessage();
	cout << endl;
	player->Attack();
	cout << endl;

}

// 메인메뉴 프린트
void PrintMainMenu()
{
	cout << "==============  Main Menu  ==============" << endl;
	cout << endl;
	cout << "1. Enter Dungeon" << endl;
	cout << "2. Check Inventory" << endl;
	cout << "3. alchemist's house" << endl;
	cout << "4. Potion Workshop" << endl;
	cout << "0. Quit" << endl;
	cout << "choice : ";
}

// 포션 하우스 프린트
void PrintAlchemyHouse()
{
	cout << " === Potion Shop === " << endl;
	cout << "1. Show all recipes" << endl;
	cout << "2. Search by potion name" << endl;
	cout << "3. Search by ingredient" << endl;
	cout << "0. Go back" << endl;

	cout << "choose : ";

}


// 아이템 구조체 (이름 , 가격)
struct Item
{
	string name;
	int price;

	void printInfo() const
	{
		cout << "Item name: " << name << endl;
		cout << "Item Price: " << price << endl;
	}
};


int main()
{
	srand(time(NULL));

	string yourname;
	string classname;
	string Potionname;
	string Ingredient;

	vector<Item> inventory(10);

	vector<Item> DropItems = { { "Slime Jelly", 100 }, { "Goblin Tendon", 50} };

	int HP;
	int MP;
	int AP;
	int DP;

	const int SIZE = 4;

	int stat[SIZE] = { 0 };

	bool isGameStart = false; // 게임 시작 버튼
	bool ClassSelection = false;// 직업 선택 버튼
	bool randomMonster = false; // 전투 시작 전
	bool OpenMainMenu = false; // 메인메뉴 오픈 확인
	bool OpenAlcemist = true; // 포션 레시피 메뉴 진입 확인

	int randomchoice = rand() % 2 + 1;
	int choice = 0;
	int HPPotion = 5;
	int MPPotion = 5;

	// 포션 레시피 구조체 (이름 , 재료1, 재료2)
	struct PotionRecipe
	{
		string name;
		string ingredient1;
		string ingredient2;


		void printPotionRecipe()//string name, string ingredient1, string ingredient2)
		{
			cout << "->  " << name << "( " << ingredient1 << " X 1 " << ingredient2 << " X 2 " << " )" << endl;

		}

	};

	vector<PotionRecipe> PotionRecipes = { { "HP_Potion", "Herb", "Water" }, { "MP_Potion", "Slime Jelly", "Water"}, { "Stamina_Potion", "Herb", "Goblin Tendon"}, { "Defence_Potion", "Slime Jelly", "Goblin Tendon"} };



	Player* player = nullptr;
	Monster* monster = nullptr;

	cout << "================================" << endl;
	cout << "[   Dungeon Escape Text RPG    ]" << endl;
	cout << "================================" << endl;
	cout << endl;

	cout << "Enter your's hero's name :";
	cin >> yourname;
	cout << endl;

	// HP, MP 입력
	while (true)
	{
		cout << "Enter HP and MP :";
		cin >> HP >> MP;

		if (HP + MP > 50)
			break;

		else
		{
			cout << "HP and MP combined must be greater than 50!" << endl;
		}
	}
	cout << endl;

	// AP, DP 입력
	while (true)
	{

		cout << "Enter Attack and Defense :";
		cin >> AP >> DP;

		if (AP + DP > 50)
			break;

		else
		{
			cout << "Attack Point and Defens Point combined must be greater than 50!" << endl;
		}
	}

	cout << endl;

	stat[0] = HP;
	stat[1] = MP;
	stat[2] = AP;
	stat[3] = DP;

	printStatus(yourname, stat);

	cout << endl;
	cout << endl;
	cout << endl;


	PrintStatUp(HPPotion, MPPotion);

	//기본 능력치 선택
	while (!isGameStart)
	{
		cin >> choice;

		switch (choice)
		{
		case 0:
			cout << "Start Game" << endl;
			isGameStart = true;
			break;

		case 1:
			if (HPPotion > 0)
			{
				--HPPotion;
				cout << "HP increased by 20.  (HP Potion used : " << HPPotion << " left)" << endl;
				cout << endl;
				stat[0] += 20;
			}
			else
			{
				cout << "You have no HP Potions left. " << endl;
			}
			break;

		case 2:
			if (MPPotion > 0)
			{
				--MPPotion;
				cout << "MP increased by 20.  (MP Potion used : " << MPPotion << " left)" << endl;
				cout << endl;
				stat[1] += 20;
			}
			else
			{
				cout << "You have no MP Potions left. " << endl;

			}
			break;

		case 3:
			stat[2] *= 2;
			cout << "Strength increased." << endl;
			cout << endl;
			break;

		case 4:
			stat[3] *= 2;
			cout << "Defense increased." << endl;
			cout << endl;
			break;

		case 5:
			printStatus(yourname, stat);
			cout << endl;
			break;

		default:
			cout << "Select a valid number" << endl;
			cout << endl;
			PrintStatUp(HPPotion, MPPotion);
			//cout << "Choose: ";
			break;
		}
	}

	cout << endl;
	cout << endl;

	PrintClassChange(yourname);

	cout << endl;
	cout << endl;

	//직업 선택
	while (!ClassSelection)
	{
		cin >> choice;

		switch (choice)
		{
		case 1:
			//Player* player = nullptr
			player = new Warrior(yourname, stat[0], stat[1], stat[2], stat[3]);
			PrintClassMessge(player);
			player->printplayerStatus();
			classname = "Warrior";
			cout << endl;
			ClassSelection = true;
			break;

		case 2:
			player = new Magician(yourname, stat[0], stat[1], stat[2], stat[3]);
			PrintClassMessge(player);
			player->printplayerStatus();
			classname = "Mage";
			cout << endl;
			ClassSelection = true;
			break;

		case 3:
			player = new Thief(yourname, stat[0], stat[1], stat[2], stat[3]);
			PrintClassMessge(player);
			player->printplayerStatus();
			classname = "Thief";
			cout << endl;
			ClassSelection = true;
			break;

		case 4:
			player = new Archer(yourname, stat[0], stat[1], stat[2], stat[3]);
			PrintClassMessge(player);
			player->printplayerStatus();
			classname = "Archer";
			cout << endl;
			ClassSelection = true;
			break;




		default:
			cout << "Select a valid number" << endl;
			cout << endl;
			PrintClassChange(yourname);

		}
	}

	cout << endl;
	cout << endl;

	//랜덤 몬스터 로직(나중에 함수로 따로 뺄것)
	while (!randomMonster)
	{
		switch (randomchoice)
		{
		case 1:
		{
			monster = new Slime();
			randomMonster = true;
			break;
		}

		case 2:
		{
			monster = new Goblin();
			randomMonster = true;
			break;
		}


		default:
			break;
		}
	}

	int PlayerDamage = player->getpower();
	int PlayerDefence = player->getdefence();
	string Playername = player->getname();
	int MonsterDefence = monster->getdefence();
	int MonsterDamage = monster->getpower();
	string Monstername = monster->getname();
	int beforMonsterHP = monster->gethp();
	int beforPlayerHP = player->gethp();
	


	//monster->damageTaken(PlayerDamage, MonsterDefence, Monstername);
	//player->damageTaken(MonsterDamage, PlayerDefence, Playername);

	// 전투 로직(나중에 함수로 따로 뺄것)
	while (player->gethp() > 0 && monster->gethp() > 0)
	{
		cout << "[ Battle Start! ]" << yourname << "(" << classname << ")" << " vs " << Monstername << endl;
		cout << endl;

		cout << "------ Player Turn ------" << endl;

		if (monster->gethp() > 0 && player->gethp() > 0)
		{
			player->Attack();
			monster->damageTaken(PlayerDamage, MonsterDefence, Monstername);

			cout << Monstername << " HP " << beforMonsterHP << " -> " << monster->gethp() << endl;

			beforMonsterHP = monster->gethp();

			cout << endl;
			cout << endl;

			monster->AttackMessage();
			player->damageTaken(MonsterDamage, PlayerDefence, Playername);

			cout << Playername << " HP " << beforPlayerHP << " -> " << player->gethp() << endl;

			beforPlayerHP = player->gethp();

			cout << endl;
			cout << endl;
		}


	}

	//else if (monster->gethp() <= 0)
	if (monster->gethp() <= 0)
	{
		cout << "Victory!!" << endl;
		cout << "-> Got: " << monster->getdropItemName() << endl;
		cout << "Save to inventory." << endl;

		for (int i = 0; i < inventory.size(); i++)
		{
			if (inventory[i].name.empty())
			{

				inventory[i] = { monster->getdropItemName(),monster->getdropItemPrice() };

				break;

			}
		}


		delete monster;


	}

	else
	{
		cout << "You Die" << endl;

		delete monster;

	}

	monster = nullptr;
	randomMonster = false;
	randomchoice = rand() % 2 + 1;

	while (!randomMonster)
	{
		switch (randomchoice)
		{
		case 1:
		{
			monster = new Slime();
			randomMonster = true;
			break;

		}

		case 2:
		{
			monster = new Goblin();
			randomMonster = true;
			break;
		}
		default:
			break;
		}
	}

	PlayerDamage = player->getpower();
	PlayerDefence = player->getdefence();
	Playername = player->getname();
	MonsterDefence = monster->getdefence();
	MonsterDamage = monster->getpower();
	Monstername = monster->getname();
	beforMonsterHP = monster->gethp();
	beforPlayerHP = player->gethp();


	cout << endl;
	cout << endl;
	cout << endl;

	//
	// PrintMainMenu();
	while (!OpenMainMenu)
	{
		PrintMainMenu();
		cin >> choice;

		switch (choice)
		{
			// 재전투 ( 전투 로직 / 승패로직 / 몬스터 재정의 로직 정비할것!)
		
		case 1:

			while (player->gethp() > 0 && monster->gethp() > 0)
			{
				cout << "[ Battle Start! ]" << yourname << "(" << classname << ")" << " vs " << Monstername << endl;
				cout << endl;

				cout << "------ Player Turn ------" << endl;

				if (monster->gethp() > 0 && player->gethp() > 0)
				{
					player->Attack();
					monster->damageTaken(PlayerDamage, MonsterDefence, Monstername);

					cout << Monstername << " HP " << beforMonsterHP << " -> " << monster->gethp() << endl;

					beforMonsterHP = monster->gethp();

					cout << endl;
					cout << endl;

					monster->AttackMessage();
					player->damageTaken(MonsterDamage, PlayerDefence, Playername);

					cout << Playername << " HP " << beforPlayerHP << " -> " << player->gethp() << endl;

					beforPlayerHP = player->gethp();

					cout << endl;
					cout << endl;
				}


			}

			//else if (monster->gethp() <= 0)
			if (monster->gethp() <= 0)
			{
				cout << "Victory!!" << endl;
				cout << "-> Got: " << monster->getdropItemName() << endl;
				cout << "Save to inventory." << endl;

				for (int i = 0; i < inventory.size(); i++)
				{
					if (inventory[i].name.empty())
					{
						inventory[i] = { monster->getdropItemName(),monster->getdropItemPrice() };

						break;
					}
				}
				delete monster;
			}

			else
			{
				cout << "You Die" << endl;

				delete monster;
			}

			monster = nullptr;
			randomMonster = false;
			randomchoice = rand() % 2 + 1;

			while (!randomMonster)
			{
				switch (randomchoice)
				{
				case 1:
				{
					monster = new Slime();
					randomMonster = true;
					break;

				}

				case 2:
				{
					monster = new Goblin();
					randomMonster = true;
					break;

				}

				default:
					break;
				}
			}

			PlayerDamage = player->getpower();
			PlayerDefence = player->getdefence();
			Playername = player->getname();
			MonsterDefence = monster->getdefence();
			MonsterDamage = monster->getpower();
			Monstername = monster->getname();
			beforMonsterHP = monster->gethp();
			beforPlayerHP = player->gethp();

			break;


		case 2:
			cout << "[ Inventory ( " << inventory.size() << " / " << inventory.capacity() << " )  ]" << endl;

			if (!inventory.empty())
			{
				//inventory.back().printInfo();
				for (auto& Item : inventory)
				{
					Item.printInfo();
				}
				cout << endl;
			}
			else
			{
				cout << " inventory is empty " << endl;
			}

			break;

		case 3:
			cout << endl;

			cout << "You head to the alchemist's house..." << endl;

			cout << endl;
			cout << endl;

			OpenMainMenu = true;
			OpenAlcemist = false;

			while (!OpenAlcemist)
			{


				PrintAlchemyHouse();
				
				cin >> choice;

				cout << endl;
				cout << endl;

				switch (choice)
				{

				case 1:
					for (int i = 0; i < PotionRecipes.size(); i++)
					{
						PotionRecipes[i].printPotionRecipe();
					}

					cout << endl;
					cout << endl;
					cout << endl;

					OpenAlcemist = false;

					break;

				case 2:
					cout << "Enter the potion's name. (HP_Potion, MP_Potion, Stamina_Potion, Defence_Potion)" << endl;
					cout << "name : ";
					cin >> Potionname;
					cout << endl;

					for (int i = 0; i < PotionRecipes.size(); i++)
					{
						if (Potionname == PotionRecipes[i].name)
						{
							PotionRecipes[i].printPotionRecipe();
						}
					}

					cout << endl;
					cout << endl;
					cout << endl;

					OpenAlcemist = false;

					break;


				case 3:
					cout << "Enter the Ingredient's name. (Herb, Water, Slime jelly, Goblin Tendon)" << endl;
					cout << "name : ";
					cin >> Ingredient;
					cout << endl;

					for (int i = 0; i < PotionRecipes.size(); i++)
					{
						if (Ingredient == PotionRecipes[i].ingredient1 || Ingredient == PotionRecipes[i].ingredient2)
						{
							PotionRecipes[i].printPotionRecipe();
						}
					}

					cout << endl;
					cout << endl;
					cout << endl;

					OpenAlcemist = false;

					break;

				case 0:
					cout << "You leave the alchemist's house." << endl;
					cout << endl;
					cout << endl;
					cout << endl;

					OpenAlcemist = true;
					OpenMainMenu = false;

					break;
				}

			}

			break;

		case 4:
			cout << "You go to the potion workshop. " << endl;

			break;


		case 0:
		{
			OpenMainMenu = true;

			break;
		}


		default:
			cout << "Select a valid number" << endl;
			cout << endl;
			PrintMainMenu();
			break;
		}
	}

	OpenMainMenu = false;


	cout << endl;
	cout << endl;
	cout << endl;

	delete player;

	return 0;

}

