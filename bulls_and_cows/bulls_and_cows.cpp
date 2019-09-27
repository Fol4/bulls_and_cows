// A littel guessing game called
//   (for some obscure reason)

#include <std_lib_facilities.h>
vector<char> create()
{
	string gamemode; 
	int type  = 48; // first element in alphabet in ASCII
	int range = 10; // amount elements in alphabet


	vector<int> number{ rand() % range };
	vector<int> check(range, 1); // vector for check uniquie

	for (int i = 1; i < 4; ++i)
	{
		int random = rand() % range;
		while (check[random] == 0)
			random = rand() % range;

		number.push_back(random);
		check[random] = 0;
	}

	vector<char> result;

	for (int i = 0; i < 4; ++i) // translate from int to char
	{
		result.push_back(number[i] + type);
	}

	return result;

}

int count(const vector<char>& digits, char c)
{
	int k = 0;

	for (int i = 0; i < digits.size(); ++i)
	{
		if (digits[i] == c) ++k;
	}

	return k;
}

void validate(const vector<char>& number)
{
	for (char n : number)
	{
		if (n == 'e' || n == 'x' || n == 'i' || n == 't') break;
		if (n < '0' || '9' < n) error("the number contains not digit");
		if (count(number, n) != 1) error("didgits of number are not unique");
	}
}

vector<char> user_guess()
{
	vector<char> guess(4);

	cout << "Guess the number:  ";
	for (int i = 0; i < guess.size(); ++i) 
	{
		 cin >> guess[i];
		 if (guess[i] == 'e')
			 break;
	}


	if (!cin)
		error("invalid input");
	validate(guess);

	return (guess);
}

void good_alghoritm()
{
	vector<vector<char>> allNumbers;
	vector<vector<char>> newNumbers;
	int randomNumber;
	char bulls = 0;
	char cows;

	for (int i1 = 0; i1 < 10; ++i1) // full vector
		for (int i2 = 0; i2 < 10 ; ++i2)
			for (int i3 = 0; i3 < 10; ++i3)
				for (int i4 = 0; i4 < 10 ; ++i4)
				{
					if ((i1 != i2) && (i1 != i3) && (i1 != i4) && (i2 != i3) && (i2 != i4) && (i3 != i4))
					{
						vector<char> arguments;
						arguments.push_back(i1 + 48);
						arguments.push_back(i2 + 48);
						arguments.push_back(i3 + 48);
						arguments.push_back(i4 + 48);
						allNumbers.push_back(arguments);
					}
				}

		while (bulls != 4)
		{
			randomNumber = rand() % allNumbers.size();
			for (int i = 0; i < 4; ++i) cout << allNumbers[randomNumber][i];
			cout << endl;

			cout << "Bulls :";
			cin >> bulls;

			if (bulls == 'e')
				break;

			cout << "Cows :";
			cin >> cows;

			if (cows == 'e')
				break;

			int bulls1 = bulls - 48;
			int cows1 = cows - 48;

			for (int i = 0; i < allNumbers.size(); ++i)
			{
				int newBulls = 0;
				int newCows = 0;
				for (int j = 0; j < 4; ++j)
					if (allNumbers[randomNumber][j] == allNumbers[i][j]) ++newBulls;
					else if (count(allNumbers[randomNumber], allNumbers[i][j]) == 1) ++newCows;
				if ((newBulls == bulls1) && (newCows == cows1))
					newNumbers.push_back(allNumbers[i]);
			}

			allNumbers = newNumbers;
			newNumbers.clear();
		}
}

void player_vs_player()
{
	int bulls = 0;
	int firstInput = 1;
	while (bulls != 4)
	{
		bulls = 0;
		int cows{};

		vector<char> uguessInputFirstPlayer;
		vector<char> uguessInputSecondPlayer;
		vector<char> uguess1;
		vector<char> uguess2;

		if (firstInput == 1)
		{
			cout << "Makes a number " << endl;

			cout << "First player  " << "\n";
			uguessInputFirstPlayer = user_guess();

			if (uguessInputFirstPlayer[0] == 'e')
				break;

			cout << "Second player" << "\n";
			uguessInputSecondPlayer = user_guess();

			if (uguessInputSecondPlayer[0] == 'e')
				break;

			firstInput = 0;
		}

		cout << "First player " << "\n";
		uguess1 = user_guess();

		if (uguess1[0] == 'e')
			break;

		cout << "Second player " << "\n";
		uguess2 = user_guess();

		if (uguess2[0] == 'e')
			break;

		for (int i = 0; i < uguess1.size(); ++i)
		{
			if (uguess1[i] == uguessInputSecondPlayer[i]) ++bulls;
			else if (count(uguessInputSecondPlayer, uguess1[i]) == 1) ++cows;
		}

		cout << "First player :" << "\n"
			<< "Bulls : " << bulls << "\n"
			<< "Cows : " << cows << endl;

		bulls = 0;
		cows = 0;

		for (int i = 0; i < uguess2.size(); ++i)
		{
			if (uguess2[i] == uguessInputFirstPlayer[i]) ++bulls;
			else if (count(uguessInputFirstPlayer, uguess2[i]) == 1) ++cows;
		}

		cout << "Second player :" << "\n"
			<< "Bulls : " << bulls << "\n"
			<< "Cows : " << cows << endl;

	}
}

void player_vs_comp()
{	
	vector<char> number = create();
	int bulls = 0;

	for (int i = 0; i < number.size(); ++i) cout << number[i];
	while (bulls != 4)
	{
		bulls = 0;
		int cows{};

		vector<char> uguess = user_guess();
		
		if (uguess[0] == 'e')
			break;

		for (int i = 0; i < uguess.size(); ++i)
		{
			if (uguess[i] == number[i]) ++bulls;
			else if (count(number, uguess[i]) == 1) ++cows;
		}

		cout << "Bulls : " << bulls << "\n"
			<< "Cows : " << cows << endl;
		
	}
}

void greeting()
{
	cout << " << Bulls and Cows" << "\n"
		<< " Computer sets a number4 unique digits" << "\n"
		<< " Try to guess it." << "\n"
		<< " <Bull> means right digit in the right position." << "\n"
		<< " <Cow> means right digit in the wrong position" << "\n"
		<< " If you want exit write exit or e "
		<< "\n"
		<< " Game is on" << endl;
}

void mode_selection()
{
	string gamemode ;

	cout << "Choose your game mode : " << "\n"
		<< "1) Player VS Player." << "\n"
		<< "2) Player VS Comp." << "\n"
		<< "3) SkyNet " << endl;
	cin >> gamemode;

	while ((gamemode != "1") && (gamemode != "2") && (gamemode != "3"))
	{
		cout << "Unknown gamemode." << "\n"
			<< "Choose your game mode : " << "\n"
			<< "1) Player VS Player." << "\n"
			<< "2) Player VS Comp." << "\n"
			<< "3) SkyNet. " << endl;
			cin >> gamemode;
	}

	if (gamemode == "1") player_vs_player();
	else if (gamemode == "2") player_vs_comp();
	else good_alghoritm();
}

void game_process()
{
	greeting();

	char GameOver = 'Y';

	cout << " Do you want play ? [Y/N] : ";
	cin >> GameOver;

	while (GameOver == 'Y')
	{
		mode_selection();
		cout << "Do you want play again? [Y/N] : ";
		cin >> GameOver;
	}
}

int main()
try
{
	srand(time(NULL));
	game_process();
}
catch (exception& e)
{
	cerr << e.what() << endl;
	return 1;
}
catch (...)
{
	cerr << "Oops, something went wrong" << endl;
	return 2;
}