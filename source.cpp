#include <stdio.h>
#include <iostream>
#include <sys/select.h>
#include <termios.h>
#include <unistd.h>
#include <future>
#include <cstdlib>
#include <unistd.h>
#include <string.h>
#include <chrono>
#include <thread>

#define STDIN_FILENO 0
using namespace std;

int count = 0;
string currentCharacter = "";
int i = 0;
int speed = 10;
int gameCounter = 0;


bool gameLoop () {
  while(true) {
    struct termios t;
    tcgetattr(STDIN_FILENO, &t);
    t.c_lflag &= ~ICANON;
    tcsetattr(STDIN_FILENO, TCSANOW, &t);

    char c,d,e;
    cin >> c;
    cin >> d;
    cin >> e;
    if ((c==27)&&(d==91)) {
        if (e==65) { currentCharacter = "UP"; }
        if (e==66) { currentCharacter = "DOWN"; }
        if (e==67) { currentCharacter = "RIGHT"; }
        if (e==68) { currentCharacter = "LEFT"; }
    }
  }
}

void convertGameStateToString() {
  vector< vector<char> > gameState;
  for (int x = 0; x < 20; x++) {
    vector<char> row;
    for (int j = 0; j < 10; j++) {
      row.push_back('O');
    }
    gameState.push_back(row);
  }

  gameState[0][gameCounter % 10] = '#';

  string output = "\n\n\n\n\n";
  for (int x = 0; x < 20; x++) {
    for (int j = 0; j < 10; j++) {
      output += (gameState[x][j]);
      output += " ";
    }
    output += "\n";
  }

  printf("%s", output.c_str());
}

int main(int argc, char** argv) {
  future<bool> fut = async(gameLoop);
  while(true) {
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    i++;
    if (i % speed == 0) {
      convertGameStateToString();
      i = 0;
      gameCounter++;
    }
  }
    
  return 0;
}