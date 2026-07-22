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
#include <algorithm>
#include "inventory.h"
#include <map>
#include "Orc.h"
#include "Dragon.h"


using namespace std;

// 플레이어 스탯 출력
void printStatus(string name, int stat[], Player* player) // 플레이어 스탯 출력
{

	cout << "================================" << endl;
	cout << "        " << name << "'s Stats" << endl;
	cout << "================================" << endl;

	cout << "HP : " << player->getMaxHp() << "      " << "MP : " << player->getMaxMp() << endl;
	cout << "Attack : " << player->getpower() << "      " << "Defense : " << player->getdefence() << endl;
	cout << "Level :" << player->getlevel() << "      " << "Exp : " << player->getexp() << endl;

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
	cout << "5. Player Stat" << endl;
	cout << "6. Boss Dungeon" << endl;
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

// 플레이어 exp 출력
void PrintPlayerExp(Player* player, Monster* monster)
{
	cout << player->getname() << " gained " << monster->getexp() << " EXP !!" << endl;
	cout << "Total EXP : " << player->getexp() << endl;
}


// 아이템 구조체 (이름 , 가격)
struct Item
{
	string name;
	int price;
	int count;

	void printInfo() const
	{
		cout << "Item name: " << name << endl;
		cout << "Item Price: " << price << endl;
		cout << "Item Count: " << count << endl;
	}
};

void setPotion(int count, int* p_HPPotion, int* p_MPPotion)
{
	*p_HPPotion = count;
	*p_MPPotion = count;
}

void UseHPPotion(Player* player)
{
	int beforeHP = player->gethp();
	player->sethp(min(player->gethp() + 50, player->getMaxHp()));

	cout << "* HP Potion used! HP restored by 50 " << " ( " << beforeHP << " -> " << player->gethp() << " ) " << endl;
}

void UseMPPotion(Player* player)
{
	int beforeMP = player->getmp();

	player->setmp(min(player->getmp() + 50, player->getMaxMp()));

	cout << "* MP Potion used! MP restored by 50 " << " ( " << beforeMP << " -> " << player->getmp() << " ) " << endl;
}

//전투 중 사용가능 아이템 선택 및 사용
void UseItem(InventoryArry_T<Item>& inventory, int Itemindex, Player* player)
{
	if (Itemindex < 0 || Itemindex >= inventory.GetSize())
	{
		cout << "Invalid item choice." << endl;
		return;
	}

	Item ChoiceItem = inventory[Itemindex];

	if (ChoiceItem.name == "HP_Potion")
	{
		UseHPPotion(player);

		if (inventory[Itemindex].count > 1)
		{
			inventory[Itemindex].count--;
		}
		else
		{
			inventory.RemoveLastItem(Itemindex);
		}
	}
	else if (ChoiceItem.name == "MP_Potion")
	{
		UseMPPotion(player);
		if (inventory[Itemindex].count > 1)
		{
			inventory[Itemindex].count--;
		}
		else
		{
			inventory.RemoveLastItem(Itemindex);
		}
	}
	else
	{
		cout <<  " cannot be used in battle." << endl;
	}
}

//초기 포션 인벤토리 넣기 // 생각해보니 이럴 필요없음 하지만 던전에서 재료템 얻은거 카운트 상승 목적 연습
void StartPotionReset(InventoryArry_T<Item>& inventory, InventoryArry_T<Item>& Potion)
{
	bool foundHPPotion = false;
	bool foundMPPotion = false;

	for (int i = 0; i < inventory.GetSize(); i++)
	{
		if (inventory[i].name == "HP_Potion")
		{
			inventory[i].count += 5;
			foundHPPotion = true;
		}

		if (inventory[i].name == "MP_Potion")
		{
			inventory[i].count += 5;
			foundMPPotion = true;
		}
	}

	if (!foundHPPotion)
	{
		inventory.AddItem(Potion[0]);
		inventory.Back().count = 5;
	}

	if (!foundMPPotion)
	{
		inventory.AddItem(Potion[1]);
		inventory.Back().count = 5;
	}
}

//포션 인벤토리 추가(Potion Stock)
void AddPotionToInventory(InventoryArry_T<Item>& inventory, const Item& Potion)
{

	for (int i = 0; i < inventory.GetSize(); i++)
	{
		if (inventory[i].name == Potion.name && inventory[i].count < 5)
		{
			inventory[i].count += 1;

			return;
		}		
	}

	inventory.AddItem(Potion);
	inventory.Back().count = 1;
}

// 스위치 클래스 별 사용 이넘
enum ClassName
{
	WarriorClass,
	ArcherClass,
	MageClass,
	ThiefClass
};

// 포션 재고 마이너스
bool DispensePotion(map<string, int>& PotionStock_, string name)
{
	auto it = PotionStock_.find(name);

	if (it != PotionStock_.end())
	{
		if (it->second > 0)
		{
			it->second--;

			std::cout << "-> Dispensed    " << it->first << " (stock: " << it->second << ")" << std::endl;

			return true;
		}
		else
		{
			std::cout << "-> Dispense failed: out of stock!" << std::endl;
		}
	}
	else
	{
		std::cout << "No matching potion found." << std::endl;
	}

	return false;
}

// 포션 재고 플러스
void ReturnPotions(map<string, int>& PotionStock_, string name)
{
	auto it = PotionStock_.find(name);

	int MAX_STOCK = 5;

	if (it != PotionStock_.end())
	{

		if (it->second == MAX_STOCK)
		{
			std::cout << "Potion is full." << std::endl;
		}
		else
		{
			it->second++;

			std::cout << "-> Return empty bottle  " << it->first << " (stock: " << it->second << ")" << std::endl;
		}
	}
	else
	{
		std::cout << "No matching potion found." << std::endl;
	}
}

// 포션 재고 반환
void GetStock(map<string, int>& PotionStock_, string name)
{
	auto it = PotionStock_.find(name);

	if (it != PotionStock_.end())
	{
		std::cout << it->first << " : " << it->second << std::endl;
	}
	else
	{
		std::cout << "No matching potion found." << std::endl;
	}
}

// 보스 방 전투
bool BossDungeonBattle(Player* player, Monster* monster, InventoryArry_T<Item>& inventory, ClassName playerClass)
{
	int beforeMonsterHP = monster->gethp();
	int beforePlayerHP = player->gethp();

	while (player->gethp() > 0 && monster->gethp() > 0)
	{
		cout << endl;
		cout << "[ Battle Start! ] " << player->getname() << " vs " << monster->getname() << endl;
		cout << "------ Player Turn ------" << endl;
		cout << "1. Battle" << endl;
		cout << "2. Use Item" << endl;
		cout << "Choice: ";

		int battleChoice;
		cin >> battleChoice;

		switch (battleChoice)
		{
		case 1:
		{
			cout << "------ Attack Menu ------" << endl;
			cout << "1. Normal Attack" << endl;
			cout << "2. Skill Attack" << endl;
			cout << "Choice: ";

			int attackChoice;
			cin >> attackChoice;

			switch (attackChoice)
			{
			case 1:
			{
				// 일반 공격
				player->Attack();

				monster->damageTaken(player->getpower(), monster->getdefence(), monster->getname());

				if (monster->gethp() > 0)
				{
					cout << monster->getname() << " HP " << beforeMonsterHP << " -> " << monster->gethp() << endl;
				}
				else
				{
					cout << monster->getname() << " HP " << beforeMonsterHP << " -> 0" << endl;
				}

				beforeMonsterHP = monster->gethp();

				break;
			}

			case 2:
			{
				// 스킬 공격
				int playerSkillDamage = player->SkillAttack(monster, player);

				switch (playerClass)
				{
				case WarriorClass:
				{
					cout << "Warrior uses Power Slash!" << endl;

					monster->SkillDamageTaken(playerSkillDamage, monster->getname());

					if (monster->gethp() > 0)
					{
						cout << monster->getname() << " HP " << beforeMonsterHP << " -> " << monster->gethp() << endl;
					}
					else
					{
						cout << monster->getname() << " HP " << beforeMonsterHP << " -> 0" << endl;
					}

					beforeMonsterHP = monster->gethp();

					break;
				}

				case ArcherClass:
				{
					cout << "Archer uses Triple Shot!" << endl;

					for (int i = 0; i < 3; i++)
					{
						if (monster->gethp() <= 0)
						{
							break;
						}

						monster->SkillDamageTaken(playerSkillDamage, monster->getname());

						if (monster->gethp() > 0)
						{
							cout << monster->getname() << " HP " << beforeMonsterHP << " -> " << monster->gethp() << endl;
						}
						else
						{
							cout << monster->getname() << " HP " << beforeMonsterHP << " -> 0" << endl;
						}

						beforeMonsterHP = monster->gethp();
					}

					break;
				}

				case MageClass:
				{
					cout << "Mage uses Arcane Burst!" << endl;

					monster->SkillDamageTaken(playerSkillDamage, monster->getname());

					if (monster->gethp() > 0)
					{
						cout << monster->getname() << " HP " << beforeMonsterHP << " -> " << monster->gethp() << endl;
					}
					else
					{
						cout << monster->getname() << " HP " << beforeMonsterHP << " -> 0" << endl;
					}

					beforeMonsterHP = monster->gethp();

					break;
				}

				case ThiefClass:
				{
					cout << "Thief uses Shadow Flurry!" << endl;

					for (int i = 0; i < 5; i++)
					{
						if (monster->gethp() <= 0)
						{
							break;
						}

						monster->SkillDamageTaken(playerSkillDamage, monster->getname());

						if (monster->gethp() > 0)
						{
							cout << monster->getname() << " HP " << beforeMonsterHP << " -> " << monster->gethp() << endl;
						}
						else
						{
							cout << monster->getname() << " HP " << beforeMonsterHP << " -> 0" << endl;
						}

						beforeMonsterHP = monster->gethp();
					}

					break;
				}

				default:
				{
					cout << "Invalid class." << endl;
					break;
				}
				}

				break;
			}

			default:
			{
				cout << "Select a valid number." << endl;
				continue;
			}
			}

			// 몬스터가 살아있으면 반격
			if (monster->gethp() > 0)
			{
				cout << endl;
				monster->AttackMessage();

				player->damageTaken(monster->getpower(), player->getdefence(), player->getname());

				if (player->gethp() > 0)
				{
					cout << player->getname() << " HP " << beforePlayerHP << " -> " << player->gethp() << endl;
				}
				else
				{
					cout << player->getname() << " HP " << beforePlayerHP << " -> 0" << endl;
				}

				beforePlayerHP = player->gethp();
			}

			cin.ignore();
			cin.get();

			break;
		}

		case 2:
		{
			// 아이템 사용
			cout << "[ Inventory ( " << inventory.GetSize() << " / " << inventory.GetCapacity() << " ) ]" << endl;

			if (!inventory.IsEmpty())
			{
				int itemChoice;

				for (int i = 0; i < inventory.GetSize(); i++)
				{
					cout << i + 1 << ". ";
					inventory[i].printInfo();
				}

				cout << "Choose: ";
				cin >> itemChoice;

				UseItem(inventory, itemChoice - 1, player);
			}
			else
			{
				cout << "Inventory is empty." << endl;
			}

			cin.ignore();
			cin.get();

			break;
		}

		default:
		{
			cout << "Select a valid number." << endl;
			break;
		}
		}
	}

	if (player->gethp() <= 0)
	{
		return false;
	}

	return true;
}


int main()
{
	srand(static_cast<unsigned int>(time(NULL)));

	Player* player = nullptr;
	Monster* monster = nullptr;

	string yourname;
	string classname; // 클래스 이름
	string Potionname;
	string Ingredient;
	ClassName playerClass; //이넘-스위치 사용 클래스 이름

	InventoryArry_T<Item> inventory(10);


	// 몬스터 드롭 아이템
	InventoryArry_T<Item> DropItems(2);
	DropItems.AddItem({ "Slime Jelly", 100, 1 });
	DropItems.AddItem({ "Goblin Tendon", 50, 1 });


	// 포션 추가
	InventoryArry_T<Item> Potion(4);
	Potion.AddItem({ "HP_Potion", 60, 1 });
	Potion.AddItem({ "MP_Potion", 50, 1 });
	Potion.AddItem({ "Stemina_Potion", 40, 1 });
	Potion.AddItem({ "Defence_Potion", 30, 1 });

	int HP;
	int MP;
	int AP;
	int DP;

	const int MAX_STOCK = 5;

	const int SIZE = 4;

	int stat[SIZE] = { 0 };

	bool isGameStart = false; // 게임 시작 버튼
	bool ClassSelection = false;// 직업 선택 버튼
	bool randomMonster = false; // 전투 시작 전
	bool OpenMainMenu = false; // 메인메뉴 오픈 확인
	bool OpenAlcemist = true; // 포션 레시피 메뉴 진입 확인
	bool IsBattle = false; // 전투 중


	int randomchoice = rand() % 2 + 1;
	int choice = 0;
	int HPPotion;
	int MPPotion;

	//포션 갯수 초기화
	setPotion(5, &HPPotion, &MPPotion);

	StartPotionReset(inventory, Potion);

	map<string, int> potionStock_;


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

	vector<PotionRecipe> PotionRecipes = { { "HP_Potion", "Herb", "Water" }, { "MP_Potion", "Slime Jelly", "Water"}, { "Stemina_Potion", "Herb", "Goblin Tendon"}, { "Defence_Potion", "Slime Jelly", "Goblin Tendon"} };

	for (int i = 0; i < PotionRecipes.size(); i++)
	{
		potionStock_[PotionRecipes[i].name] = MAX_STOCK;
	}
	
	
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

	// 기본 능력치 선택 주석처리
	/*
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
	*/

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
			player = new Warrior(yourname, stat[0], stat[1], stat[2], stat[3], 0, 100, 1, stat[0], stat[1]);
			PrintClassMessge(player);
			playerClass = WarriorClass;
			classname = "Warrior";
			cout << endl;
			ClassSelection = true;
			player->setMaxHp(+30);

			break;

		case 2:
			player = new Magician(yourname, stat[0], stat[1], stat[2], stat[3], 0, 100, 1, stat[0], stat[1]);
			PrintClassMessge(player);
			playerClass = MageClass;
			classname = "Mage";
			cout << endl;
			player->setMaxMp(+30);
			player->setmp(player->getMaxMp());
			ClassSelection = true;
			break;

		case 3:
			player = new Thief(yourname, stat[0], stat[1], stat[2], stat[3], 0, 100, 1, stat[0], stat[1]);
			PrintClassMessge(player);
			playerClass = ThiefClass;
			classname = "Thief";
			cout << endl;
			ClassSelection = true;
			break;

		case 4:
			player = new Archer(yourname, stat[0], stat[1], stat[2], stat[3], 0, 100, 1, stat[0], stat[1]);
			PrintClassMessge(player);
			playerClass = ArcherClass;
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

	int playerExp = player->getexp();
	int playerLevel = player->getlevel();
	int playerMaxExp = player->getmaxExp();

	int MaxHP = player->getMaxHp();
	int MaxMp = player->getMaxMp();

	player->setMaxHp(+stat[0]);
	player->setMaxMp(+stat[1]);


	printStatus(yourname, stat, player);

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
	int PlayerSkillDamage = player->SkillAttack(monster, player);


	randomMonster = false;
	randomchoice = rand() % 2 + 1;


	cout << endl;
	cout << endl;
	cout << endl;

	// PrintMainMenu();
	// PrintMainMenu();
	while (!OpenMainMenu)
	{
		if (player->getexp() >= player->getmaxExp())
		{
			player->setlevel(player->getlevel() + 1);
			player->setMaxExp(player->getmaxExp() + 100);
			player->setMaxHp(player->getMaxHp() + 100);
			player->setMaxMp(player->getMaxMp() + 100);
			player->sethp(player->getMaxHp());
			player->setmp(player->getMaxMp());
			player->setExp(0);
			cout << "Level Up!!" << endl;
		}

		PrintMainMenu();
		cin >> choice;

		switch (choice)
		{
		case 1:
		{
			// 던전 / 전투 진입
			while (player->gethp() > 0 && monster->gethp() > 0)
			{
				cout << "[ Battle Start! ]" << yourname << "(" << classname << ")" << " vs " << Monstername << endl;
				cout << endl;

				cout << "------ Player Turn ------" << endl;
				cout << "1. Battle " << endl;
				cout << "2. Use Item " << endl;
				cout << "choice : ";

				int Battlechoice;
				cin >> Battlechoice;

				switch (Battlechoice)
				{
				case 1:
				{
					cout << "------ Player Turn ------" << endl;
					cout << "1. Normal Attack " << endl;
					cout << "2. Skill Attack " << endl;
					cout << "choice : ";

					int Attackchoice;
					cin >> Attackchoice;

					switch (Attackchoice)
					{
					case 1:
					{
						if (monster->gethp() > 0 && player->gethp() > 0)
						{
							player->Attack();
							monster->damageTaken(PlayerDamage, MonsterDefence, Monstername);

							if (monster->gethp() > 0)
							{
								cout << Monstername << " HP " << beforMonsterHP << " -> " << monster->gethp() << endl;
							}
							else
							{
								cout << Monstername << " HP " << beforMonsterHP << " -> 0" << endl;
							}

							beforMonsterHP = monster->gethp();

							cout << endl;
							cout << endl;

							if (monster->gethp() > 0)
							{
								monster->AttackMessage();
								player->damageTaken(MonsterDamage, PlayerDefence, Playername);

								if (player->gethp() > 0)
								{
									cout << Playername << " HP " << beforPlayerHP << " -> " << player->gethp() << endl;
								}
								else
								{
									cout << Playername << " HP " << beforPlayerHP << " -> 0" << endl;
								}

								beforPlayerHP = player->gethp();

								cout << endl;
								cout << endl;
							}

							cin.ignore();
							cin.get();
						}

						break;
					}

					case 2:
					{
						PlayerSkillDamage = player->SkillAttack(monster, player);

						switch (playerClass)
						{
						case WarriorClass:
						{
							if (monster->gethp() > 0 && player->gethp() > 0)
							{
								cout << "Warrior uses Power Slash!" << endl;

								monster->SkillDamageTaken(PlayerSkillDamage, Monstername);

								if (monster->gethp() > 0)
								{
									cout << Monstername << " HP " << beforMonsterHP << " -> " << monster->gethp() << endl;
								}
								else
								{
									cout << Monstername << " HP " << beforMonsterHP << " -> 0" << endl;
								}

								beforMonsterHP = monster->gethp();

								cout << endl;
								cout << endl;

								if (monster->gethp() > 0)
								{
									monster->AttackMessage();
									player->damageTaken(MonsterDamage, PlayerDefence, Playername);

									if (player->gethp() > 0)
									{
										cout << Playername << " HP " << beforPlayerHP << " -> " << player->gethp() << endl;
									}
									else
									{
										cout << Playername << " HP " << beforPlayerHP << " -> 0" << endl;
									}

									beforPlayerHP = player->gethp();

									cout << endl;
									cout << endl;
								}

								cin.ignore();
								cin.get();
							}

							break;
						}

						case ArcherClass:
						{
							if (monster->gethp() > 0 && player->gethp() > 0)
							{
								cout << "Archer uses Triple Shot!" << endl;

								for (int i = 0; i < 3; i++)
								{
									if (monster->gethp() <= 0)
									{
										break;
									}

									monster->SkillDamageTaken(PlayerSkillDamage, Monstername);

									if (monster->gethp() > 0)
									{
										cout << Monstername << " HP " << beforMonsterHP << " -> " << monster->gethp() << endl;
									}
									else
									{
										cout << Monstername << " HP " << beforMonsterHP << " -> 0" << endl;
									}

									beforMonsterHP = monster->gethp();

									cout << endl;
									cout << endl;
								}

								if (monster->gethp() > 0)
								{
									monster->AttackMessage();
									player->damageTaken(MonsterDamage, PlayerDefence, Playername);

									if (player->gethp() > 0)
									{
										cout << Playername << " HP " << beforPlayerHP << " -> " << player->gethp() << endl;
									}
									else
									{
										cout << Playername << " HP " << beforPlayerHP << " -> 0" << endl;
									}

									beforPlayerHP = player->gethp();

									cout << endl;
									cout << endl;
								}

								cin.ignore();
								cin.get();
							}

							break;
						}

						case MageClass:
						{
							if (monster->gethp() > 0 && player->gethp() > 0)
							{
								cout << "Mage uses Arcane Burst!" << endl;

								monster->SkillDamageTaken(PlayerSkillDamage, Monstername);

								if (monster->gethp() > 0)
								{
									cout << Monstername << " HP " << beforMonsterHP << " -> " << monster->gethp() << endl;
								}
								else
								{
									cout << Monstername << " HP " << beforMonsterHP << " -> 0" << endl;
								}

								beforMonsterHP = monster->gethp();

								cout << endl;
								cout << endl;

								if (monster->gethp() > 0)
								{
									monster->AttackMessage();
									player->damageTaken(MonsterDamage, PlayerDefence, Playername);

									if (player->gethp() > 0)
									{
										cout << Playername << " HP " << beforPlayerHP << " -> " << player->gethp() << endl;
									}
									else
									{
										cout << Playername << " HP " << beforPlayerHP << " -> 0" << endl;
									}

									beforPlayerHP = player->gethp();

									cout << endl;
									cout << endl;
								}

								cin.ignore();
								cin.get();
							}

							break;
						}

						case ThiefClass:
						{
							if (monster->gethp() > 0 && player->gethp() > 0)
							{
								cout << "Thief uses Shadow Flurry!" << endl;

								for (int i = 0; i < 5; i++)
								{
									if (monster->gethp() <= 0)
									{
										break;
									}

									monster->SkillDamageTaken(PlayerSkillDamage, Monstername);

									if (monster->gethp() > 0)
									{
										cout << Monstername << " HP " << beforMonsterHP << " -> " << monster->gethp() << endl;
									}
									else
									{
										cout << Monstername << " HP " << beforMonsterHP << " -> 0" << endl;
									}

									beforMonsterHP = monster->gethp();

									cout << endl;
									cout << endl;
								}

								if (monster->gethp() > 0)
								{
									monster->AttackMessage();
									player->damageTaken(MonsterDamage, PlayerDefence, Playername);

									if (player->gethp() > 0)
									{
										cout << Playername << " HP " << beforPlayerHP << " -> " << player->gethp() << endl;
									}
									else
									{
										cout << Playername << " HP " << beforPlayerHP << " -> 0" << endl;
									}

									beforPlayerHP = player->gethp();

									cout << endl;
									cout << endl;
								}

								cin.ignore();
								cin.get();
							}

							break;
						}

						default:
						{
							break;
						}
						}

						break;
					}

					default:
					{
						cout << "Select a valid number" << endl;
						break;
					}
					}

					break;
				}

				case 2:
				{
					cout << "[ Inventory ( " << inventory.GetSize() << " / " << inventory.GetCapacity() << " )  ]" << endl;

					if (!inventory.IsEmpty())
					{
						int Itemchoice;

						for (int i = 0; i < inventory.GetSize(); i++)
						{
							cout << i + 1 << ". ";
							inventory[i].printInfo();
						}

						cout << "choose: " << endl;
						cin >> Itemchoice;

						int ItemIndex = Itemchoice - 1;

						UseItem(inventory, ItemIndex, player);
					}
					else
					{
						cout << " inventory is empty " << endl;
					}

					cin.ignore();
					cin.get();

					break;
				}

				default:
				{
					cout << "Select a valid number" << endl;
					break;
				}
				}
			}

			if (monster->gethp() <= 0)
			{
				cout << Monstername << " defeated!" << endl;

				player->setExp(+monster->getexp());
				PrintPlayerExp(player, monster);

				if (Monstername == "Slime")
				{
					if (inventory.GetSize() < inventory.GetCapacity())
					{
						inventory.AddItem(DropItems[0]);
						cout << "You got " << DropItems[0].name << "!" << endl;
					}
					else
					{
						cout << "Inventory is full!" << endl;
						inventory.AddItem(DropItems[0]);
						cout << "You got " << DropItems[0].name << "!" << endl;
						
					}
				}
				else if (Monstername == "Goblin")
				{
					if (inventory.GetSize() < inventory.GetCapacity())
					{
						inventory.AddItem(DropItems[1]);
						cout << "You got " << DropItems[1].name << "!" << endl;
					}
					else
					{
						cout << "Inventory is full!" << endl;
						inventory.AddItem(DropItems[1]);
						cout << "You got " << DropItems[1].name << "!" << endl;
					}
				}

				delete monster;
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
					{
						break;
					}
					}
				}

				MonsterDefence = monster->getdefence();
				MonsterDamage = monster->getpower();
				Monstername = monster->getname();
				beforMonsterHP = monster->gethp();

				PlayerDamage = player->getpower();
				PlayerDefence = player->getdefence();
				Playername = player->getname();
				beforPlayerHP = player->gethp();

				cout << endl;
				cout << "A new monster appeared: " << Monstername << "!" << endl;
				cout << endl;

				cin.ignore();
				cin.get();
			}

			if (player->gethp() <= 0)
			{
				cout << Playername << " defeated!" << endl;
				cout << "Game Over" << endl;

				OpenMainMenu = true;

				cin.ignore();
				cin.get();
			}

			break;
		}

		case 2:
		{
			cout << "[ Inventory ( " << inventory.GetSize() << " / " << inventory.GetCapacity() << " )  ]" << endl;

			if (!inventory.IsEmpty())
			{
				inventory.PrintAllItem();
			}
			else
			{
				cout << " inventory is empty " << endl;
			}

			cin.ignore();
			cin.get();

			break;
		}

		case 3:
		{
			cout << endl;
			cout << "You head to the alchemist's house..." << endl;
			cout << endl;
			cout << endl;

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
				{
					for (int i = 0; i < PotionRecipes.size(); i++)
					{
						PotionRecipes[i].printPotionRecipe();
					}

					cout << endl;
					cout << endl;
					cout << endl;

					break;
				}

				case 2:
				{
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

					break;
				}

				case 3:
				{
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

					break;
				}

				case 0:
				{
					cout << "You leave the alchemist's house." << endl;
					cout << endl;
					cout << endl;
					cout << endl;

					OpenAlcemist = true;

					break;
				}

				default:
				{
					cout << "Select a valid number" << endl;
					break;
				}
				}
			}

			break;
		}

		case 4:
		{
			cout << "You go to the potion workshop. " << endl;

			bool OpenPotionWorkshop = false;

			while (!OpenPotionWorkshop)
			{
				cout << endl;
				cout << "===== Potion Storage =====" << endl;
				cout << "1. Check Stock" << endl;
				cout << "2. Take Out Potion" << endl;
				cout << "3. Return Empty Bottle" << endl;
				cout << "0. Go Back" << endl;
				cout << "Choice: ";

				int PotionworkshopChoice;
				string Potionname;

				cin >> PotionworkshopChoice;

				switch (PotionworkshopChoice)
				{
				case 1:
				{
					cout << "Enter potion name: ";
					cin >> Potionname;

					GetStock(potionStock_, Potionname);

					cin.ignore();
					cin.get();

					break;
				}

				case 2:
				{
					cout << "Enter potion name: ";
					cin >> Potionname;

					bool isDispensed = DispensePotion(potionStock_, Potionname);

					if (isDispensed)
					{
						for (int i = 0; i < Potion.GetSize(); i++)
						{
							if (Potion[i].name == Potionname)
							{
								AddPotionToInventory(inventory, Potion[i]);
								break;
							}
						} 
					}

					cin.ignore();
					cin.get();

					break;
				}

				case 3:
				{
					cout << "Enter potion name: ";
					cin >> Potionname;

					ReturnPotions(potionStock_, Potionname);

					cin.ignore();
					cin.get();

					break;
				}

				case 0:
				{
					cout << "Go Back." << endl;

					OpenPotionWorkshop = true;

					break;
				}

				default:
				{
					cout << "Select a valid number." << endl;

					cin.ignore();
					cin.get();

					break;
				}
				}
			}

			break;
		}

		case 5:
		{
			printStatus(yourname, stat, player);

			cin.ignore();
			cin.get();

			break;
		}

		case 6:
		{
			cout << endl;

			// 보스던전 고유 몬스터 벡터 배열
			vector<Monster*> BossDungeon;

			cout << "[ Dungeon Floor 1 ]" << endl;

			BossDungeon.push_back(new Slime("Slime", 30, 15, 5, "Slime Jelly", 5, 100, 1));
			BossDungeon.push_back(new Goblin("Goblin", 50, 25, 8, "Goblin Tendon", 50, 120, 2));
			BossDungeon.push_back(new Orc("Orc", 80, 35, 10, "Orc Tusk", 80, 150, 3));
			BossDungeon.push_back(new Dragon("Dragon", 200, 60, 20, "Dragon Scale", 500, 1000, 10));

			for (int i = 0; i < 3; i++)
			{
				cout << "Room " << i + 1 << ": " << BossDungeon[i]->getname()
					<< "    (HP " << BossDungeon[i]->gethp()
					<< ", Attack " << BossDungeon[i]->getpower() << ")" << endl;
			}

			cout << endl;


			int clear = 0;
			bool gameClear = false;
			bool gameOver = false;

			for (int i = 0; i < BossDungeon.size(); i++)
			{
				if (i == 3 && clear < 3)
				{
					cout << endl;
					cout << "Boss Room is locked." << endl;
					cout << "You must clear all normal rooms first." << endl;
					break;
				}

				// 보스몬스터 출력
				if (i == 3 && clear >= 3)
				{
					cout << endl;
					cout << "★ Boss Room Unlocked!" << endl;
					cout << "Boss Dragon appears! ";
					cout << "(HP " << BossDungeon[i]->gethp()
						<< ", Attack " << BossDungeon[i]->getpower()
						<< ", Defense " << BossDungeon[i]->getdefence() << ")" << endl;
				}

				// 일반 몬스터 출력
				else
				{
					cout << "Room " << i + 1 << ": " << BossDungeon[i]->getname()
						<< "    (HP " << BossDungeon[i]->gethp()
						<< ", Attack " << BossDungeon[i]->getpower() << ")" << endl;
				}

				//전투
				bool isWin = BossDungeonBattle(player, BossDungeon[i], inventory, playerClass);

				if (!isWin)
				{
					cout << endl;
					cout << "Game Over!" << endl;

					gameOver = true;
					OpenMainMenu = true;

					break;
				}

				if (BossDungeon[i]->gethp() <= 0)
				{
					if (i < 3)
					{
						clear++;

						cout << "Room " << i + 1 << ": " << BossDungeon[i]->getname() << " -> Clear!" << endl;
					}
					else
					{
						cout << endl;
						cout << "Dragon defeated!" << endl;
						cout << "=== GAME CLEAR! ===" << endl;

						gameClear = true;
						OpenMainMenu = true;

						break;
					}
				}
			}

			for (int i = 0; i < BossDungeon.size(); i++)
			{
				delete BossDungeon[i];
			}

			BossDungeon.clear();

			cin.ignore();
			cin.get();

			break;
		}

		case 0:
		{
			OpenMainMenu = true;
			break;
		}

		default:
		{
			cout << "Select a valid number" << endl;
			cout << endl;

			cin.ignore();
			cin.get();

			break;
		}
		}
	}

	OpenMainMenu = false;

	cout << endl;
	cout << endl;
	cout << endl;

	delete monster;
	delete player;

	return 0;
}
