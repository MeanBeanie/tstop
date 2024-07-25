#include <chrono>
#include <ctime>
#include <iostream>
#include <map>
#include <ncurses.h>
#include <string>
#include <thread>
#include <vector>

int main(){
	setlocale(LC_ALL, "");
	std::map<char, std::vector<std::string>> numberMap = {
		{'0', {"██████","██  ██","██  ██","██  ██","██████"}},
		{'1', {"  ██  ","████  ","  ██  ","  ██  ","██████"}},
		{'2', {"██████","    ██","██████","██    ","██████"}},
		{'3', {"██████","    ██","  ████","    ██","██████"}},
		{'4', {"██  ██","██  ██","██████","    ██","    ██"}},
		{'5', {"██████","██    ","██████","    ██","██████"}},
		{'6', {"██████","██    ","██████","██  ██","██████"}},
		{'7', {"██████","    ██","    ██","    ██","    ██"}},
		{'8', {"██████","██  ██","██████","██  ██","██████"}},
		{'9', {"██████","██  ██","██████","    ██","██████"}},
		{':', {"      ","  ██  ","      ","  ██  ","      "}}
	};

	initscr();
	noecho();
	nodelay(stdscr, TRUE);
	curs_set(0);

	int start = time(NULL);
	std::string formatted;

	int hours = 0;
	int minutes = 0;
	int seconds = 0;

	int verticalOffset = (LINES / 2) - 2;
	int horizOffset = (COLS / 2 ) - 28;
	
	int prevElapsed = 0;

	bool running = true;
	while(running){
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		seconds++;
		if(seconds % 15 == 0){
			int now = time(NULL);
			seconds = now - start;
			minutes = seconds / 60;
			seconds -= ((seconds / 60) * 60);
			hours = minutes / 60;
			minutes -= ((minutes / 60) * 60);
		}
		
		formatted = (hours < 10 ? "0" : "") + std::to_string(hours) + ":" + (minutes < 10 ? "0" : "") + std::to_string(minutes) + ":" + (seconds < 10 ? "0" : "") + std::to_string(seconds);

		for(int i = 0; i < formatted.size(); i++){
			for(int j = 0; j < numberMap.at(formatted[i]).size(); j++){
				mvprintw(j+verticalOffset, (i*7)+horizOffset, "%s", numberMap.at(formatted[i]).at(j).c_str());
			}
		}

		int input = getch();
		if(input == 'q'){
			running = false;
		}
	}

	endwin();
	curs_set(1);
}
