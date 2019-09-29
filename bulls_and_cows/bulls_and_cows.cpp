// A littel guessing game called
//   (for some obscure reason)

#include <std_lib_facilities.h>

int random_int(int a ,int b)
{
	return (rand() / double(RAND_MAX)) * (b - a) + a;
}

constexpr int digit_range = 10;

int random_digit()
{
	return random_int(0, digit_range);
}

vector<char> create()
{ 
	const int wordSize = 4; // length vector
	int random = random_digit();

	vector<int> number{ random };
	vector<int> check(digit_range, 1); // vector for check uniquie
	check[random] = 0;

	for (int i = 1; i < wordSize; ++i)
	{
		int random = random_digit();

		while (check[random] == 0)
		{
			cout << random << endl;
			random = random_digit();
		}

		number.push_back(random);
		check[random] = 0;
	}

	vector<char> result;

	for (int i = 0; i < wordSize; ++i) // translate from int to char
	{
		result.push_back('0' + number[i]);
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

	return guess;
}


vector<vector<char>> permitations()
{
	vector<vector<char>> allNumbers;
	const int countDigits = 10;

	for (int i1 = 0; i1 < countDigits; ++i1) // full vector
		for (int i2 = 0; i2 < countDigits; ++i2)
			for (int i3 = 0; i3 < countDigits; ++i3)
				for (int i4 = 0; i4 < countDigits; ++i4)
				{
					if ((i1 != i2) && (i1 != i3) && (i1 != i4) && (i2 != i3) && (i2 != i4) && (i3 != i4))
					{
						vector<char> arguments;
						arguments.push_back(i1 + '0');
						arguments.push_back(i2 + '0');
						arguments.push_back(i3 + '0');
						arguments.push_back(i4 + '0');
						allNumbers.push_back(arguments);
					}
				}
	return allNumbers;
}


void good_alghoritm()
{
	vector<vector<char>> allNumbers = permitations();
	char bulls = 0;
	char cows;
	const char wins = '4';
	const int wordSize = 4;

	while (bulls != wins)
	{
		int r = random_int(0,allNumbers.size());
		for (int i = 0; i < wordSize; ++i) cout << allNumbers[r][i];
		cout << endl;

		cout << "Bulls :";
		cin >> bulls;

		if (bulls == 'e')
			break;

		cout << "Cows :";
		cin >> cows;

		if (cows == 'e')
			break;

		int bulls1 = bulls - '0';
		int cows1 = cows - '0';

		vector<vector<char>> newNumbers;

		for (int i = 0; i < allNumbers.size(); ++i)
		{
			int newBulls = 0;
			int newCows = 0;
			for (int j = 0; j < wordSize; ++j)
				if (allNumbers[r][j] == allNumbers[i][j]) ++newBulls;
				else if (count(allNumbers[r], allNumbers[i][j]) == 1) ++newCows;
			if ((newBulls == bulls1) && (newCows == cows1))
				newNumbers.push_back(allNumbers[i]);
		}

		allNumbers = newNumbers;
	}
}

void test()
{
	vector<vector<char>> allNumbers = permitations();
	vector<vector<char>> newNumbers;
	int randomNumber;
	int bulls = 0;
	int cows;
	const int countDigits = 10;
	const int wins = 4;
	const int wordSize = 4;

	vector<char> uguess = user_guess();

	while (bulls != wins)
	{
		randomNumber = rand() % allNumbers.size();
		for (int i = 0; i < wordSize; ++i) cout << allNumbers[randomNumber][i];
		cout << endl;

		bulls = 0;
		cows = 0;

		for(int i = 0; i < uguess.size(); ++i)
			if (allNumbers[randomNumber][i] == uguess[i]) ++bulls;
			else if (count(uguess, allNumbers[randomNumber][i]) == 1) ++cows;

		cout << " Bulls : " << bulls;
		cout << " Cows : " << cows << endl;

		for (int i = 0; i < allNumbers.size(); ++i)
		{
			int newBulls = 0;
			int newCows = 0;
			for (int j = 0; j < wordSize; ++j)
				if (allNumbers[randomNumber][j] == allNumbers[i][j]) ++newBulls;
				else if (count(allNumbers[randomNumber], allNumbers[i][j]) == 1) ++newCows;
			if ((newBulls == bulls) && (newCows == cows))
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
	int wins = 4;

	while (bulls != wins)
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
	int wins = 4;

	for (int i = 0; i < number.size(); ++i) cout << number[i];
	while (bulls != wins)
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
		<< " If you want exit write e "
		<< "\n"
		<< " Game is on" << endl;
}

void mode_selection()
{
	char gamemode ;
	const char PlayerVSplayer = '1';
	const char PlayerVScomp = '2';
	const char SkyNet = '3';
	const char Test = '4';

	cout << "Choose your game mode : " << "\n"
		<< "1) Player VS Player." << "\n"
		<< "2) Player VS Comp." << "\n"
		<< "3) SkyNet. " << "\n"
		<< "4) Test. " << endl;
	cin >> gamemode;

	while ((gamemode != PlayerVSplayer) && (gamemode != PlayerVScomp) && (gamemode != SkyNet) && (gamemode != Test) )
	{
		cout << "Unknown gamemode." << "\n"
			<< "Choose your game mode : " << "\n"
			<< "1) Player VS Player." << "\n"
			<< "2) Player VS Comp." << "\n"
			<< "3) SkyNet. " << "\n"
			<< "4) Test. " << endl;
			cin >> gamemode;
	}

	if (gamemode == PlayerVSplayer) player_vs_player();
	else if (gamemode == PlayerVScomp) player_vs_comp();
	else if (gamemode == SkyNet) good_alghoritm();
	else test();
}

void game_process()
{
	greeting();

	char GameOver = 'Y';
	char continueGame = 'Y';

	cout << " Do you want play ? [Y/N] : ";
	cin >> GameOver;

	while (GameOver == continueGame)
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