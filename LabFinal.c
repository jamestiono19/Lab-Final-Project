#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <windows.h>

struct unit{
	int HP;
	int ATK;
	int DEF;
};

struct leaderboardStruct{
	int score;
	char name[20];
};

struct Character{
    char name[20];
    int HP;
    char* HP_grade;
    int ATK;
    char* ATK_grade;
    int DEF;
    char* DEF_grade;
    char* background;
    char* passiveSkill;
    char* skill1;
    char* skill2;
    char* skill3;
};

void bubbleSort(struct leaderboardStruct array[], int size) {
	int step, i;
  for (step = 0; step < size - 1; ++step) {
    for (i = 0; i < size - step - 1; ++i) {
      if (array[i].score < array[i + 1].score) {
        struct leaderboardStruct temp = array[i];
        array[i] = array[i + 1];
        array[i + 1] = temp;
      }
    }
  }
}

int leaderboard(struct leaderboardStruct array[]){
	system("cls");
	int i = 0;
	printf("LEADERBOARD\n");
	printf("=============================================================\n");
	for(i = 0; i < 5; i++){
		printf("%d. %s-%d\n", i+1, array[i].name, array[i].score);
	}
	printf("=============================================================\n");
	printf("\n");
	printf("Press any button to leave\n");
	getchar();
}

//Ini module untuk mission, ada character selection dan gameplay
int missionModule() {
	system("cls");
    int characterName;
    int HP, ATK, DEF, SPE, damage, damageReduction = 1, counter = 0,  point = 0, hitCount = 0, ATKBuff = 0, stun = 0, pointYield = 0;
    char playAgain = 'y';
    struct unit character;
    struct unit enemy;

    printf("Choose the Personnel you want to bring with you to this mission.\n");
    printf("1. Consecute (High-Survivability)\n");
    printf("2. Vindictor (High-Risk Lifestealer)\n");
    printf("3. Crescent (High-Damage Burst)\n");
    while(1){
    	printf("Make a choice, Captain (1, 2, or 3): ");
    	scanf("%d", &characterName); getchar();
    	if(characterName == 1 || characterName == 2 || characterName == 3){
    		break;
		} else {
			printf("Invalid input (only input 1, 2, or 3)\n");
		}
	}
	system("cls");
    // Initialize character stats
    switch (characterName) {
        case 1:
            character.HP = 150;
            character.ATK = 50;
            character.DEF = 70;
            break;
        case 2:
            character.HP = 75;
            character.ATK = 100;
            character.DEF = 60;
            break;
        case 3:
            character.HP = 80;
            character.ATK = 100;
            character.DEF = 50;
            break;
    }
	Sleep(1000);
	int maxHP =  character.HP, maxATK =  character.ATK, maxDEF =  character.DEF;
    char actionChoice;
	int heal;

//struct unit enemy;
	int randomEnemyNumber;

	while(playAgain == 'y'){
	randomEnemyNumber = rand() % 4;
	switch(randomEnemyNumber){
		case 1:
			printf(" A Termiten appeared.\n");
			enemy.HP = 150;
			enemy.ATK = 25;
			enemy.DEF = 20;
			pointYield = 1;
			break;
		case 2:	
			printf(" A Nibbler appeared.\n");	
			enemy.HP = 275;
			enemy.ATK = 15;
			enemy.DEF = 50;
			pointYield = 3;
			break;
		case 3:
			printf(" A Feller appeared.\n");
			enemy.HP = 400;
			enemy.ATK = 10;
			enemy.DEF =70;	
			pointYield = 5;
			break;	
	}
	int enemyMaxHP = enemy.HP;

    // Main battle loop
    
    while (enemy.HP > 0 && character.HP > 0) {
    	Sleep(1000);
		switch(characterName){

		case 1:
			// Action Prompt
			printf("\nConsecute: Next order, Cap?\n");
			Sleep(1000);
			printf("Your HP: %d//%d  ||  Enemy HP: %d//%d\n", character.HP, maxHP, enemy.HP, enemyMaxHP);
			printf("Passive Skill Charge: %d / 4\n", hitCount);
			Sleep(1000);
			printf("================================\n");
			printf("a. Singular Punch\n");
			printf("b. Heal\n");
			printf("c. Block\n");
			printf("Choose your action: ");

			// Input Handling
			scanf(" %c", &actionChoice); getchar();

			while (actionChoice != 'a' && actionChoice != 'b' && actionChoice != 'c') {
				printf("Invalid choice, Captain! Please choose a, b, or c.\n");
				scanf(" %c", &actionChoice);
			}

			// Clear console (platform-specific)
			system("cls");

			// Handle action choices
			if(hitCount > 4){
				damage = (character.ATK * 2) / (1 + enemy.DEF / 100);
				enemy.HP -= damage; 
				hitCount = 0;
				printf("Consecute goes for a follow-up Punch, dealing %d amount of damage! Enemy has %d HP left\n", damage, enemy.HP);
				Sleep(1000);
			}

			switch (actionChoice) {
				case 'a': // Basic Attack
					damage = character.ATK / (1 + enemy.DEF / 100);
					enemy.HP -= damage;
					hitCount += 2;
					if (enemy.HP < 0) enemy.HP = 0;
					printf("Consecute punched the enemy twice, dealing %d damage. Enemy HP: %d\n", damage, enemy.HP);
					break;

				case 'b': // Active Skill
					if((character.HP + maxHP/5) <= maxHP){
						heal = maxHP /5;
						character.HP += heal; // Skill penalty
						if (enemy.HP < 0) enemy.HP = 0;
					} else {
						heal = maxHP - HP;
						HP = maxHP;
					}
					// if (HP > maxHP) HP = maxHP;
					printf("Consecute heal, gaining %d to your HP. Your HP : %d | Enemy HP: %d\n",heal ,character.HP, enemy.HP);
					break;

				case 'c': // Block
					damageReduction = 2;
					counter = 1;
					printf("Consecute is blocking.\n");
					break;
				}
		break;
	
		
		case 2:
			printf("\nVindictor: I'm ready to move, captain.\n");
			Sleep(1000);
			printf("Your HP: %d//%d  ||  Enemy HP: %d//%d\n", character.HP, maxHP, enemy.HP, enemyMaxHP);
			printf("Passive Skill Charge: %d / 10\n", hitCount);
			Sleep(1000);
			printf("================================\n");
			printf("a. Triple Cut\n");
			printf("b. Vitality Drain\n");
			printf("c. A Slayer's Blade\n");
			printf("Choose your action: ");

			// Input Handling
			scanf(" %c", &actionChoice); getchar();

			while (actionChoice != 'a' && actionChoice != 'b' && actionChoice != 'c') {
				printf("Invalid choice, Captain! Please choose a, b, or c.\n");
				scanf(" %c", &actionChoice);
			}

			// Clear console (platform-specific)
			system("cls");

			// Handle action choices
			if(hitCount > 3){
				damage = (ATK * 3) / (1 + enemy.DEF / 100);
				enemy.HP -= damage; 
				hitCount = 0;
				if((character.HP + (damage / 2)) > maxHP){
					heal = maxHP - character.HP;
					character.HP = maxHP;
				} else {
					character.HP += damage / 2;
				}
				printf("Vindictor does a follow-up attack, reaping the enemy's life-force, dealing %d damage and healing %d HP for herself. Enemy has %d HP left, and Vindictor has %d HP.\n", damage, heal, enemy.HP, character.HP);
				Sleep(1000);
			}

			switch (actionChoice) {
			case 'a': // Basic Attack
					damage = character.ATK / (1 + enemy.DEF / 100);
					enemy.HP -= damage;
					hitCount += 3;
					if (enemy.HP < 0) enemy.HP = 0;
					printf("Vindictor slashed an enemy three times, dealing %d damage. Enemy has %d HP left.\n", damage, enemy.HP);
					break;

				case 'b': // Active Skill
					damage = (character.ATK/2) / (1 + enemy.DEF/100);
					enemy.HP -= damage;
					if((character.HP + (damage / 2)) > maxHP){
					heal = maxHP - character.HP;
					character.HP = maxHP;
				} else {
					HP += damage / 2;
				}
					hitCount += 1;
					// if (HP > maxHP) HP = maxHP;
					printf("Vindictor stole a bit of the enemy's blood, dealing %d damage and healing %d for herself. Enemy has %d HP left, and Vindictor has %d HP.\n", damage, heal, enemy.HP, character.HP);
					break;

				case 'c': // Block
					if(ATKBuff > 0){
						printf("Vindictor resharpened her Scythe. ATK Buff counter resets to 2 turns.\n");
					} else {
					character.ATK += maxATK / 2; 
					printf("Vindictor sharpens her Scythe, increasing her ATK by 50 %% for 2 turns.\n");
				}
					ATKBuff = 3;
					break;
				}
				break;
				
			case 3:
			if(stun != 1){			
			printf("\nCrescent: Do I shoot, captain?\n");
			Sleep(1000);
			printf("Your HP: %d//%d  ||  Enemy HP: %d//%d\n", character.HP, maxHP, enemy.HP, enemyMaxHP);
			printf("Passive Skill Charge: %d / 3\n", hitCount);
			Sleep(1000);
			printf("================================\n");
			printf("a. One Bullet\n");
			printf("b. Piercing Shot\n");
			printf("c. Lock Target\n");
			printf("Choose your action: ");

			// Input Handling
			scanf(" %c", &actionChoice); getchar();

			while (actionChoice != 'a' && actionChoice != 'b' && actionChoice != 'c') {
				printf("Invalid choice, Captain! Please choose a, b, or c.\n");
				scanf(" %c", &actionChoice);
			}
			if(hitCount >= 3){
				if(HP > maxHP / 2){
					heal = maxHP - character.HP;
					character.HP = maxHP;
				} else {
					character.HP += maxHP / 2;
				}
				printf("Crescent decided she deserved a treat, and ate a can of sardine, replenishing %d HP. She has %d HP left.",heal , character.HP);
				hitCount = 0;
				Sleep(1000);
			}
			// Clear console (platform-specific)
			system("cls");

			// Handle action choices

			switch (actionChoice) {
			case 'a': // Basic Attack
					damage = character.ATK / (1 + enemy.DEF / 100);
					enemy.HP -= damage;
					hitCount += 1;
					if (enemy.HP < 0){
					enemy.HP = 0;
				}
					printf("Crescent shot the enemy once, dealing %d damage. Enemy has %d HP left.\n", damage, enemy.HP);
					break;

				case 'b': // Active Skill
					damage = (character.ATK * 3);
					stun = 2;
					hitCount += 1;
					enemy.HP -= damage;
					if (enemy.HP < 0){
						printf("MORE THAN 0 ALERT");
						enemy.HP = 0;
					}
					// if (HP > maxHP) HP = maxHP;
					printf("Crescent took a focused shot, dealing a whopping %d damage to the enemy, Enemy has %d HP left. Crescent needs to reload next turn.\n", damage, enemy.HP);
					break;

				case 'c': // Block
					if(ATKBuff > 0){
						printf("Crescent keeps her focus, ATK buff resets back to 1 turn..\n");
					} else {
					character.ATK += maxATK; 
					printf("Crescent increases her focus, increasing her ATK by 100 %% for 1 turn.\n");
				}
					ATKBuff = 2;
					break;
				}
				break;
		}
	 else {
		printf("Crescent is reloading this turn...\n");
	}}
		stun -= 1;

        // Enemy attack phase
        if (enemy.HP > 0) {
            damage = (enemy.ATK / (1 + character.DEF / 100)) / damageReduction;
            character.HP -= damage;
            if (HP < 0) HP = 0;
            printf("Enemy attacked you for %d damage. Your HP: %d\n", damage, character.HP);

            // Counterattack (if blocking)
            if (counter == 1) {
                damage = (character.ATK * 3 / 10) / (1 + enemy.DEF / 100);
                enemy.HP -= damage;
                if (enemy.HP < 0){
					enemy.HP = 0;
				}
                printf("Consecute counterattacks, dealing %d damage. Enemy HP: %d\n", damage, enemy.HP);
                counter = 0; // Reset counter
            }
            ATKBuff -= 1;
            if(ATKBuff == 0){
            	character.ATK = maxATK;
            	printf("ATK Buff is reset.\n");
			}
            
        }

        // Reset damage reduction after block
        damageReduction = 1;

        Sleep(1500); // Pause for readability
    }

    // Battle outcome
    if (enemy.HP <= 0) {
        printf("\nVictory! You defeated the enemy.\n");
        point += pointYield;
        printf("Obtained %d points.\n", pointYield);
        printf("Current point: %d\n", point);
        printf("Continue? (y/n): ");
				scanf("%c", &playAgain); getchar();
				while(1){
					if(playAgain == 'y'|| playAgain == 'n'){
						system("cls");
						break;	
					} else {
						printf("Invalid input, please input only 'y' or 'n' (case insensitive): ");
					}
				}
    } else if (HP == 0) {
        printf("\nDefeat! The enemy has overpowered you.\n");
        printf("Final Point: %d\n", point);
        printf("Returning to Menu in 5 seconds...\n");
        Sleep(5000);
        system("cls");
        playAgain = 'n';
        
    }
}
return point;
}


//Ini buat character database, isinya lore, stats, skill explanation, etc.
void displayCharacters(struct Character characters[], int n) {
    printf("========================================\n");
    printf("           CHARACTER DATABASE           \n");
    printf("========================================\n\n");

    for (int i = 0; i < n; i++) {
        printf("%d. %s\n", i + 1, characters[i].name);
        printf("HP: %d (%s)\n", characters[i].HP, characters[i].HP_grade);
        printf("ATK: %d (%s)\n", characters[i].ATK, characters[i].ATK_grade);
        printf("DEF: %d (%s)\n\n", characters[i].DEF, characters[i].DEF_grade);
        printf("Background: %s\n\n", characters[i].background);
        printf("Passive Skill: %s\n", characters[i].passiveSkill);
        printf("Skill 1: %s\n", characters[i].skill1);
        printf("Skill 2: %s\n", characters[i].skill2);
        printf("Skill 3: %s\n", characters[i].skill3);
        printf("========================================\n\n");
        Sleep(1000);
    }
}

//module untuk search character berdasarkan namanya
void searchCharacter(struct Character characters[], int n) {
    char searchName[20];
    int found;
    char choice;

    do {
        found = 0;
        printf("Enter the name of the character you want to search for: ");
        scanf("%19s", searchName);

        for (int i = 0; i < n; i++) {
            if (strcmp(characters[i].name, searchName) == 0) {
                found = 1;
                printf("\nCharacter Found:\n");
                printf("Name: %s\n", characters[i].name);
                printf("HP: %d (%s)\n", characters[i].HP, characters[i].HP_grade);
                printf("ATK: %d (%s)\n", characters[i].ATK, characters[i].ATK_grade);
                printf("DEF: %d (%s)\n\n", characters[i].DEF, characters[i].DEF_grade);
                printf("Background: %s\n\n", characters[i].background);
                printf("Passive Skill: %s\n", characters[i].passiveSkill);
                printf("Skill 1: %s\n", characters[i].skill1);
                printf("Skill 2: %s\n", characters[i].skill2);
                printf("Skill 3: %s\n", characters[i].skill3);
                break;
            }
        }

        if (!found) {
            printf("\nCharacter '%s' not found in the database.\n", searchName);
        }

        do {
            printf("\nDo you want to search for another character? (y/n): ");
            scanf(" %c", &choice);
            if (choice != 'y' && choice != 'Y' && choice != 'n' && choice != 'N') {
                printf("Invalid input. Please enter 'y' or 'n'.\n");
            }
        } while (choice != 'y' && choice != 'Y' && choice != 'n' && choice != 'N');

    } while (choice == 'y' || choice == 'Y');
}

void characterDatabase() {
	system("cls");
    struct Character characters[] = {
        {
            "Consecute", 150, "A+", 50, "B-", 70, "A",
            "A boy raised by the organization, known for his happy-go-lucky attitude and passion for martial arts.",
            "Consecute throws a follow-up punch, dealing damage equal to 200% of his ATK. Hit Count Required: 4.",
            "Punches an enemy once, dealing damage equal to 100% of Consecute's ATK. Hit count: 2.",
            "Consecute patches himself up with bandages, healing for 20% of max HP.",
            "Blocks and counter-attacks, reducing damage by 50% and attacking for 30% of ATK. Hit count: 1."
        },
        
        {
            "Vindictor", 75, "B", 100, "A", 60, "B-", 
            "A human experimented on, possessing Horror DNA, with a stoic and caring demeanor.",
            "Reaps the enemy's life-force, dealing 200% of her ATK and healing for 50% of the damage dealt. Hit Count Required: 10.",
            "Slashes the enemy three times, dealing 100% of her ATK in total. Hit count: 3.",
            "Steals a bit of life force, dealing 50% of ATK and healing for 50% of damage dealt. Hit count: 1.",
            "Sharpens her scythe, increasing ATK by 50% for 2 turns."
        },

        {
            "Crescent", 80, "B", 100, "A", 50, "C", 
            "A girl fascinated by military arsenals, a talented marksman working as a sniper since age 15.",
            "Replenishes 50% of her HP by eating a can of sardines. Hit Count Required: 3.",
            "Shoots an enemy, dealing damage equal to 100% of her ATK. Hit count: 1.",
            "Shoots with an armor-piercing bullet, dealing 300% ATK and ignoring DEF. Reloads for 1 turn after use. Hit count: 1.",
            "Focuses on her target, increasing ATK by 100% for the next attack."
        }
    };

    int n = sizeof(characters) / sizeof(characters[0]);

    displayCharacters(characters, n);
    searchCharacter(characters, n);
}

//Ini buat enemy database, isinya stats, lore, sama skill enemy. Sama kyk character database, lore sama gerlad aja
void enemyDatabase() {
    system("cls"); // Clear the console for a fresh display
    printf(" =========================================\n");
    printf("            ENEMY DATABASE               \n");
    printf(" =========================================\n");

    printf("  ________________________________________\n");
    printf("  | Termiten |     Nibbler   |    Feller |\n");
	printf("  |__________|_______________|___________|\n");
    printf("  | HP: 150  |    HP: 275    |   HP: 400 |   \n");
    printf("  | ATK: 25  |    ATK: 15    |   ATK: 10 |  \n");
    printf("  | DEF: 20  |    DEF: 50    |   DEF: 70 | \n");
	printf("  |__________|_______________|___________|\n");

    printf("Descriptions:\n");
    printf("-------------------------------------------------\n");
    printf("Termiten: Quick and aggressive, it bites with deadly force.\n");
    printf("Nibbler: Slow but resilient, with an impenetrable defense.\n");
    printf("Feller: Towering and sluggish, but difficult to take down.\n\n");
    
    printf(" =========================================\n");
    printf("Return to menu? (y/n): ");
}

//Ini main, nyambung-nyambungin module dan sebagai menu utama.
int main(){
	int menuChoice, choiceTries, validRetry = 0, point = 0, i = 0;
	char gameOn = 'y';
	char replayChoice;
	
	FILE* leaderboardFile;
	leaderboardFile = fopen("leaderboard.txt", "r+");
	
	struct leaderboardStruct leaderboardData[5];
	
	for(i = 0; i < 5; i++){
		if (fscanf(leaderboardFile, "%[^-]-%d\n", leaderboardData[i].name, &leaderboardData[i].score) != 2) {
	        printf("Error reading leaderboard data\n");
	        break;
	    }
	}
	
	bubbleSort(leaderboardData, 5);
	
	printf("Loading...\n");
	Sleep(1000);
	printf("Captain's Interface Data loaded, initiating system...\n");
	Sleep(1000);
	printf("System initiated, waking up Lightdust...\n");
	Sleep(1000);
	printf("\n");
	printf("Welcome back, Captain. What would you like to do?\n");
	Sleep(300);
	while(gameOn == 'y'){
		system("cls");
		validRetry = 0;
		menuChoice = 0;
		choiceTries = 0;
		while (1) {
        // Display menu
            printf("\n1. Start a mission \n");
            printf("2. Access Your Team's Units Database \n");
            printf("3. Access Monster Data\n");
            printf("4. Access Captains' Achievements (Leaderboard)\n");
            printf("5. Exit System\n");
            printf("Your choice, Captain: ");

            if (scanf("%d", &menuChoice) != 1) {
                // Handle non-integer input
                printf("Invalid input! Please enter a number (1-5): ");
                while (getchar() != '\n'); // Clear the buffer
                continue;
            }

            getchar(); // Consume the newline character

            if (menuChoice < 1 || menuChoice > 5) {
                printf("Invalid choice, please choose again (1, 2, 3, 4, or 5): ");
                continue;
            }

            // Handle menu options
            switch (menuChoice) {
                case 1: {
                    point += missionModule();
                    char name[20];
                    printf("Please input your name (no more than 20 characters including spaces): ");
                    scanf(" %[^\n]", name); // Read full name
                    getchar(); // Consume newline
                    printf("\nYour report: \nName: %s \nScore: %d \n", name, point);

                    if(point > leaderboardData[4].score){
                        leaderboardData[4].score = point;
                        strcpy(leaderboardData[4].name, name);
                        bubbleSort(leaderboardData, 5);
				    }
                    point = 0; // Reset point after the mission
                    break;
                }

                case 2:
                    characterDatabase();
                    break;

                case 3:
                    enemyDatabase();
                    break;

                case 4:
                    leaderboard(leaderboardData);
                    break;

                case 5:
                    printf("Ending system...\n");
                    Sleep(1000);
                    printf("System ended. See you next time, Captain. Lightdust, signing out.");
                    return 0;
            }

            // Ask if the user wants to return to the menu
            printf("\nDo you want to return to the menu? (y/n): ");
            while (1) {
                scanf(" %c", &gameOn);
                gameOn = tolower(gameOn);

                if (gameOn == 'y' || gameOn == 'n') {
                    break; // Valid input
                }

                printf("Invalid input, please input only 'y' or 'n' (case insensitive): ");
            }

            if (gameOn == 'n') {
                break;
            }
        }
    }
	FILE* leaderboardFileToWriteOn;
	leaderboardFile = fopen("leaderboard.txt", "w+");

	for(i = 0; i < 5; i++){
	        fprintf(leaderboardFile, "%s-%d\n", leaderboardData[i].name, leaderboardData[i].score);

	}
	printf("Ending system...\n");
	Sleep(1000);
	printf("System ended. See you next time, Captain. Lightdust, signing out.");
	
	return 0;
	
}

