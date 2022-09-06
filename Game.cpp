#include<iostream>
#include<ctime>
#include<iostream>
#include<Windows.h>
#include <conio.h>   
#include<vector>
using namespace std;

//----------------------------------------
struct Snake {
	int X;
	int Y;
	int Tails;
};
struct Size {
	int Height;
	int Width;
};
struct FruitLocation {
	int X;
	int Y;
};
enum Direction{None,Left,Right,Up,Down};
//----------------------------------------

class SnakeGame {
	Snake snake;
	FruitLocation fruit;
	Size size;
	vector<pair<int,int>>tailes;
	Direction direction;
	bool GameOver;
	void Input() {
		if (_kbhit()) {
			switch (_getch())
			{
			case 'a':
				if(direction!=Right)
				direction = Left;
				break;
			case 'd':
				if (direction != Left)
				direction = Right;
				break;
			case 's':
				if (direction != Up)
				direction = Down;
				break;
			case 'w':
				if(direction!=Down)
				direction = Up;
				break;
			case 'x':
				GameOver = 1;
				break;
			case 'p':
				system("pause");
				break;
			default:break;
			}
		}
	}
	void addTail() {
		tailes.push_back({ 0,0 });
		snake.Tails++;
	}
	void Logic() {
		if (snake.X == fruit.X && snake.Y == fruit.Y) {
			addTail();
			cout << "\a";
			while (snake.X == fruit.X && snake.Y == fruit.Y) {
				fruit.X = rand() % (size.Width - 2) + 1;
				fruit.Y = rand() % (size.Height - 2) + 1;
			}
		}

		//----------------------------------------
		
		for (int i = tailes.size() -1; i > 0; i--) {
			tailes[i].first = tailes[i - 1].first;
			tailes[i].second = tailes[i - 1].second ;
		}
		tailes[0].first = snake.X; tailes[0].second = snake.Y;
		//----------------------------------------

		isGameOver();

	}
	void isGameOver() {
		for (int i = 1; i < tailes.size(); i++)
			if (tailes[0].first == tailes[i].first  && tailes[0].second == tailes[i].second  && snake.Tails > 1)
				cout << "\tGame Over!\n", GameOver = 1;
	}
	void MoveSnake() {

		//----------------------------------------
		switch (direction)
		{
		case None:
			break;
		case Left:
			snake.X--;
			break;
		case Right:
			snake.X++;
			break;
		case Up:
			snake.Y--;
			break;
		case Down:
			snake.Y++;
			break;

		}


		//----------------------------------------
		if (snake.X == 0)snake.X = size.Width - 2;
		else if (snake.X == size.Width-1)snake.X = 1;
		else if (snake.Y == size.Height-1)snake.Y = 1;
		else if (snake.Y == 0)snake.Y = size.Height - 2;
	}
	bool snakeTail(int x,int y) {
		for (int i = 1; i < tailes.size(); i++) {
			if (tailes[i].first ==x && tailes[i].second == y)return 1;
		}
		return 0;
	}
	void printInfo() {
		cout << "Direction : ";
		switch (direction)
		{
		case None:
			cout << "None\n";
			break;
		case Left:
			cout << "Left\n";
			break;
		case Right:
			cout << "Right\n";
			break;
		case Up:
			cout << "Up\n";
			break;
		case Down:
			cout << "Down\n";
			break;
		default:
			break;
		}
		cout << "Score : " << (snake.Tails-1) * 10 << endl;
		cout << "(" << snake.X << "," << snake.Y << ")\n";
		cout << "(" << fruit.X << "," << fruit.Y << ")\n" ;

	}
	void Draw() {
		system("cls");
		for (int i = 0; i < size.Height; i++) {
			for (int j = 0; j < size.Width; j++) {
				if (i == 0 || i == size.Height - 1 || j == 0 || j == size.Width - 1)
					cout << "#";
				else if (snakeTail(j,i))
					cout << "o";
				else if (i == snake.Y && j == snake.X)
					cout << "O";
				else if (i == fruit.Y && j == fruit.X)
					cout << "*";
				else cout << " ";
			}
			cout << endl;
		}
	}
	void setTails() {
		tailes.push_back({0,0});

		for (int i = 0; i < snake.Tails; i++)
			tailes.push_back({-1,-1});
	}
	void Reset() {
		fruit.X = rand() % (size.Width - 1) + 1;
		fruit.Y = rand() % (size.Height - 1) + 1;
		direction = None;
		GameOver = 0;
		size.Height = 20;
		size.Width = 30;
		snake.X = size.Width / 2;
		snake.Y = size.Height / 2;
		snake.Tails = 1;
		tailes.clear();
	}
public:
	SnakeGame() {
		fruit.X = rand() % (size.Width - 2) + 1;
		fruit.Y = rand() % (size.Height - 2) + 1;
		direction = None;
		GameOver = 0;
		size.Height = 20;
		size.Width = 30;
		snake.X = size.Width / 2;
		snake.Y = size.Height / 2;
		snake.Tails = 1;
	}
	void Play() {
		setTails();
		while (!GameOver) {
			Draw();
			printInfo();
			Input();
			MoveSnake();
			Logic();
			Sleep(75);
		}
		cout << "Press R to restart: ";
		if (_kbhit && _getch() == 'r') Reset(), Play();
	}		
};

//----------------------------------------
int main() {
	//Move only with " a , s , d , w"
	//Press P to pause 
	//Press X to end game
	srand(time(0));
	SnakeGame game;
	game.Play();
}
