#include <iostream>
#include <iomanip>
#include <string>
#include <ctime>
#include <unistd.h>
using namespace std;

class Warrior {        
  
  public:

    int hardiness;
    int skill;
    int health;
    int wins_count;
    bool is_dead;

    Warrior() {
      hardiness = 0;
      skill = 0;
      health = 0;
      wins_count = 0;
      is_dead = false;
    }

    void GenerateSkill() {
      hardiness = rand() % 100 + 1;
      skill = rand() % 100 + 1;
      health = rand() % 100 + 1;
    }

    int GetHardiness() {
      return hardiness;
    }

    int GetSkill() {
      return skill;
    }

    int GetHealth() {
      return health;
    }

    void Win() {
      wins_count += 1;
    }

    void ResetWin() {
      wins_count = 0;
    }

    int GetWinsCount() {
      return wins_count;
    }

    void Die() {
      is_dead = true;
    }

    bool IsDead() {
      return is_dead;
    }

};


class Drawer {

  public:

    string spaceRight(string source, size_t total_width, char padding_char = ' ') {
      if (total_width > source.size()) {
          source.insert(source.size(), total_width - source.size(), padding_char);
      }
      return source;
    }

    string spaceLeft(string source, size_t total_width, char padding_char = ' ') {
      if (total_width > source.size()) {
        source.insert(0, total_width - source.size(), padding_char);
      }
      return source;
    }

    string spaceBoth(string source, size_t total_width, char padding_char = ' ') {
      if (total_width > source.size()) {
        size_t total_pad_width = total_width - source.size();
        size_t left_pad_width = (total_pad_width / 2) + source.size();
        source = spaceRight(spaceLeft(source, left_pad_width, padding_char), total_width, padding_char);
      }
      return source;
    }

    void NewLine() {
      cout << endl;
    }

    void TournamentHeader(int number, int red_warrior, int green_warrior) {
      NewLine();
      cout << "========= Fight #" << number << " \033[1;31mRed warrior\033[0m " << red_warrior;
      cout << " vs \033[1;32mGreen warrior\033[0m " << green_warrior  << " =========";
      NewLine();
    }

    void Fight() {
      NewLine();
      cout << setw(15) << " " << "\033[1;31m (*_*)    \033[0m            \033[1;32m    (*_*)  \033[0m"  << endl;
      cout << setw(15) << " " << "\033[1;31m╔(   )=|=>\033[0m            \033[1;32m<=|=(   )╗ \033[0m"  << endl;
      cout << setw(15) << " " << "\033[1;31m /```\\   \033[0m            \033[1;32m     /```\\ \033[0m"  << endl;
      NewLine();
    }

    void StatHeader() {
      cout << setw(9) << " ";
      cout << "\033[1;31m" << spaceRight("Red platoon", 30) << "\033[0m";
      cout << "\033[1;32m" << spaceRight("Green platoon", 8) << "\033[0m";
      NewLine();
    }

    void Stat(string name, int value) {
      cout << setw(9) << " " << spaceRight(name + ": ", 15) << spaceRight(to_string(value), 5) << ' ';
    }

    void Result(string text, int color) {
      cout << "\033[1;" << color << "m" << spaceBoth(text, 63) << "\033[0m";
    }

    void GameOver(int red_warriors_count, int  green_warriors_count) {
      string title = spaceBoth(
        "Left Red warriors: " + to_string(red_warriors_count) +
        " and Green warriors: " + to_string(green_warriors_count),
        63
      );

      cout << endl;
      cout << endl;
      cout << endl;
      cout << "\033[1;36m         _____                         ____                     \033[0m" << endl;
      cout << "\033[1;36m        / ____/___ _____ ___  ___     / __ \\_   _____  _____   \033[0m" << endl;
      cout << "\033[1;36m       / / __/ __ `/ __ `__ \\/ _ \\   / / / / | / / _ \\/ ___/ \033[0m" << endl;
      cout << "\033[1;36m      / /_/ / /_/ / / / / / /  __/  / /_/ /| |/ /  __/ /        \033[0m" << endl;
      cout << "\033[1;36m      \\____/\\__,_/_/ /_/ /_/\\___/   \\____/ |___/\\___/_/    \033[0m" << endl;
      cout << endl;
      cout << title << endl;
      cout << endl;
      cout << endl;
      cout << endl;
    }

};

int main() {
  srand(time(NULL));
  system("cls");

  int warriors_count = 5;
  int green_warriors_count = warriors_count;
  int red_warriors_count = warriors_count;

  Warrior green_warriors[warriors_count];
  Warrior red_warriors[warriors_count];
  Drawer drawer;

  for (int i = 0; i < warriors_count; i++) {
    green_warriors[i].GenerateSkill();  
    red_warriors[i].GenerateSkill();
  }

  int i = 0;

  while (true) {
    i += 1;

    int red_i = rand() % warriors_count;
    int green_i = rand() % warriors_count;
    Warrior red_warrior = red_warriors[red_i];
    Warrior green_warrior = green_warriors[green_i];

    if (red_warrior.IsDead()) {
      while (true) {
        red_i = rand() % warriors_count;
        red_warrior = red_warriors[red_i];

        if (!red_warrior.IsDead()) {
          break;
        }
      }
    }

    if (green_warrior.IsDead()) {
      while (true) {
        green_i = rand() % warriors_count;
        green_warrior = green_warriors[green_i];

        if (!green_warrior.IsDead()) {
          break;
        }
      }
    }

    drawer.TournamentHeader(i, red_i + 1, green_i + 1);
    drawer.Fight();
    drawer.StatHeader();
    drawer.Stat("hardiness", red_warrior.GetHardiness());
    drawer.Stat("hardiness", green_warrior.GetHardiness());
    drawer.NewLine();
    drawer.Stat("skill", red_warrior.GetSkill());
    drawer.Stat("skill", green_warrior.GetSkill());
    drawer.NewLine();
    drawer.Stat("health", red_warrior.GetHealth());
    drawer.Stat("health", green_warrior.GetHealth());
    drawer.NewLine();

    red_warrior.ResetWin();
    green_warrior.ResetWin();

    if (red_warrior.GetHardiness() > green_warrior.GetHardiness()) {
      red_warrior.Win();
    } else if (red_warrior.GetHardiness() < green_warrior.GetHardiness()) {
      green_warrior.Win();
    }

    if (red_warrior.GetSkill() > green_warrior.GetSkill()) {
      red_warrior.Win();
    } else if (red_warrior.GetSkill() < green_warrior.GetSkill()) {
      green_warrior.Win();
    }

    if (red_warrior.GetHealth() > green_warrior.GetHealth()) {
      red_warrior.Win();
    } else if (red_warrior.GetHealth() < green_warrior.GetHealth()) {
      green_warrior.Win();
    }

    drawer.Stat("Red points", red_warrior.GetWinsCount());
    drawer.Stat("Green points", green_warrior.GetWinsCount());
    drawer.NewLine();
    drawer.NewLine();

    if (red_warrior.GetWinsCount() > green_warrior.GetWinsCount()) {
      green_warriors_count -= 1;
      green_warrior.Die();

      drawer.Result("Winner is Red platoon warrior!", 31);
    } else if (red_warrior.GetWinsCount() < green_warrior.GetWinsCount()) {
      red_warriors_count -= 1;
      red_warrior.Die();

      drawer.Result("Winner is Green platoon warrior!", 32);
    } else {
      drawer.Result("Nobody Win!", 36);
    }

    red_warriors[red_i] = red_warrior;
    green_warriors[green_i] = green_warrior;

    cout << endl << endl;

    sleep(1);
    system("cls");

    if (green_warriors_count == 0 || red_warriors_count == 0) {
      break;
    }
  }

  drawer.GameOver(red_warriors_count, green_warriors_count);

  return 0;
}