#include <iostream>
using namespace std;
#include <cmath>
#include <string>
#include <cstdlib>
enum enGameChoice{Stone=1 ,paper=2 ,Scissors=3 };
enum enWinner{player=1 , computer=2 ,Draw=3};
struct stGameInfo {
	int GameRound;
	int playerWinTimes;
	int computerWinTimes;
	int DrawTimes;
	enWinner FinalWinner;
	string FinalWinnerName;

};
struct stRoundInfo{
	int NumberOfRounds;
	enGameChoice playerChoice;
	enGameChoice ComputerChoice;
	enWinner Winner;
	string WinnerName;
};
int RandomNumber(int from, int to) {
	return rand() % (to - from + 1) + from;
}
enGameChoice PlayerChoice() {
	short choice;
	cout << "Your choice : [1]:stone , [2]Paper ,[3]:Scissors ?";
	cin >> choice;
	return (enGameChoice)choice;
}
enGameChoice computerChoice() {
	short choice = RandomNumber(1, 3);
	return (enGameChoice)choice;
}
enWinner WhoWinTheRound(stRoundInfo& RoundInfo) {
	switch (RoundInfo.playerChoice) {
		case enGameChoice::Stone:
			if (RoundInfo.ComputerChoice == enGameChoice::paper) { 
				return enWinner::computer;
			} break;
		case enGameChoice::paper: 
	        if (RoundInfo.ComputerChoice == enGameChoice::Scissors) { 
				return enWinner::computer;
			} break; 
		case enGameChoice::Scissors: 
			if (RoundInfo.ComputerChoice == enGameChoice::Stone) {
			   return enWinner::computer;
				} break;
	} 	if (RoundInfo.playerChoice == RoundInfo.ComputerChoice) {
		return enWinner::Draw;
	}
	//if you reach here then player1 is the winner.
	return enWinner::player; 
}
enWinner WhoWinTheGame(int playerWinTimes, int ComputerWinTimes) {
	if (playerWinTimes > ComputerWinTimes) return enWinner::player;
	else if (playerWinTimes < ComputerWinTimes) return enWinner::computer;
	else if (playerWinTimes == ComputerWinTimes) enWinner::Draw;
}
string WinnerName(enWinner winner){
	string arr[] = { "player" ,"computer" ,"No Winner" };
	return arr[winner - 1];
}
string ChoiceName(enGameChoice choice) {
	string arr[] = { "Stone" ,"paper" ,"Scissors" };
	return arr[choice - 1];
}
short NumberOfRounds() {
	cout << "How Many Rounds 1 to 10 ? \n";
	short number;
	cin >> number;
	return number;
}
void SetWinnerSecreemColor(enWinner Winner) {
	switch (Winner) {
	case enWinner::computer:
		system("color 4f");
		break;
	case enWinner::player:
		system("color 2F");
		cout << "\a";
		break;
	case enWinner::Draw:
		system("color 6f");
		break;
	}
}
stGameInfo fillGameInfo(int playerWinTimes, int ComputerWinTimes, int DrawTimes ,int GameRound) {
	stGameInfo GameInfo;
	GameInfo.GameRound = GameRound;
	GameInfo.computerWinTimes = ComputerWinTimes;
	GameInfo.playerWinTimes = playerWinTimes;
	GameInfo.DrawTimes = DrawTimes;
	GameInfo.FinalWinner = WhoWinTheGame(playerWinTimes, ComputerWinTimes);
	GameInfo.FinalWinnerName = WinnerName(GameInfo.FinalWinner);
	return GameInfo;
}
stGameInfo RoundResult(int HowManyRound) {
	stRoundInfo info;
	int playerWinTimes = 0, ComputerWinTimes = 0, DrawTimes = 0;
	   for(int i=1 ;i<= HowManyRound ;i++){
		cout << "Round [" << (i) << "] begins : \n\n";
		info.playerChoice = PlayerChoice();
		info.ComputerChoice = computerChoice();
		cout << "_________________Round [" << (i) << "]________________\n";
		cout << "Player Choice   : " << ChoiceName(info.playerChoice) << endl;
		cout << "computer Choice : " << ChoiceName(info.ComputerChoice) << endl;
		info.Winner = WhoWinTheRound(info);
		cout << "Round Winner    : " << WinnerName(info.Winner) << endl;
		cout << "-----------------------------------------------------\n\n";
		SetWinnerSecreemColor(info.Winner);
		if (info.Winner == enWinner::player) playerWinTimes++;
		else if (info.Winner == enWinner::computer) ComputerWinTimes++;
		else if (info.Winner == enWinner::Draw) DrawTimes++;
	}
	return fillGameInfo(playerWinTimes, ComputerWinTimes, DrawTimes , HowManyRound);
}
void finalGame() {
	short NumofRound = NumberOfRounds();
	stGameInfo GameInfo = RoundResult(NumofRound);
	GameInfo.GameRound = NumofRound;
	stRoundInfo info;
	cout << "\t\t\t-------------------------------------------------------\n";
	cout << "\n\t\t\t\t\t+++ G a m e  O v e r +++ \n";
	cout << "\t\t\t-------------------------------------------------------\n";
	cout << "\n\t\t\t------------------[ Game Results ]---------------------\n";
	cout << "\t\t\t Game Rounds          : " << GameInfo.GameRound<<endl;
	cout << "\t\t\t player Win Times     : " << GameInfo.playerWinTimes << endl;
	cout << "\t\t\tcomputer Win Times    : " << GameInfo.computerWinTimes << endl;
	cout << "\t\t\t Draw Times           : " << GameInfo.DrawTimes << endl;
	cout << "\t\t\t Final Winner         : " << GameInfo.FinalWinnerName << endl;
	cout << "\t\t\t-------------------------------------------------------\n";
}
void ResetScreen() {
	system("cls");
	system("color 0F");
}
void startGame() {
	finalGame();
	while (true) {
		char Answar;
		cout << "Do you want to play again ? Y/N ?";
		cin >> Answar;
		if (Answar == tolower('n')) {
			break;
		}
		ResetScreen();
		finalGame();
	}
}
int main(){
	srand((unsigned)time(NULL));
	startGame();
}

