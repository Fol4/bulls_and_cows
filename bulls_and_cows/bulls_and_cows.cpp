// A littel guessing game called
//   (for some obscure reason)

#include <std_lib_facilities.h>
vector<char> create()
{
	string setting;
	int type;
	int range;

	cout << "Choose your language [A-Z]/[0-9] : ";
	cin >> setting;

	while(setting != "[A-Z]" || setting != "[0-9]")

	if (setting == "[A-Z]")
	{
		type = 65;
		range = 26;
	}
	else
	{
		type = 48;
		range = 10;
	}

	vector<int> number{ rand() % range };
	vector<int> check(range, 1);

	for (int i = 1; i < 4; ++i)
	{
		int random = rand() % range;
		while (check[random] == 0)
			random = rand() % range;

		number.push_back(random);
		check[random] = 0;
	}

	vector<char> result;

	for (int i = 0; i < 4; ++i)
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
		if ((n < '0' || '9' < n) and (n < 'A' || 'Z' < n)) error("the number contains not digit or letters");
		if (count(number, n) != 1) error("didgits of number are not unique");
	}
}

vector<char> user_guess()
{
	vector<char> guess(4);

	cout << "Guess the number:  ";
	for (int i = 0; i < guess.size(); ++i) cin >> guess[i];

	if (!cin)
		error("invalid input");
	validate(guess);

	return (guess);
}

int main()
try
{
	cout << " << Bulls and Cows" << "\n"
		<< " Computer sets a number or capital letters of 4 unique digits" << "\n"
		<< " Try to guess it." << "\n"
		<< " <Bull> means right digit or letters in the right position." << "\n"
		<< " <Cow> means right digit or letters in the wrong position" << "\n"
		<< "\n"
		<< " game is on" << endl;

	char GameOver = 'Y';

	cout << " Do you want play ? [Y/N] : ";
	cin >> GameOver;

	while (GameOver == 'Y')
	{
		srand(time(NULL));
		string gamemode;

		cout << "Choose your game mode. PVP or PVE : ";
		cin >> gamemode;

		int bulls{0};
		int firstInput = 1;
		int pvp = 0;
		int hardmode = 0;

		vector<char> number = create();

		while ((gamemode != "PVP") || (gamemode != "PVE") || (gamemode !="hardmode"))
		{
			cout << "Unknown gamemode" << "\n";
			cout << "Choose your game mode. PVP or PVE : ";
			cin >> gamemode;
		}

		if (gamemode == "PVP")
			pvp = 1;

		while (bulls != 4)
		{
			bulls = 0;
			int cows{};

			vector<char> uguess;
			vector<char> uguessInputFirstPlayer;
			vector<char> uguessInputSecondPlayer;
			vector<char> uguess1;
			vector<char> uguess2;

			if (pvp == 1)
			{
				if (firstInput == 1)
				{
					cout << "First Player " << "\n";
					uguessInputFirstPlayer = user_guess();

					cout << "Second Player " << "\n";
					uguessInputSecondPlayer = user_guess();

					firstInput = 0;
				}

				cout << "First Player " << "\n";
				uguess1 = user_guess();

				cout << "Second Player " << "\n";
				uguess2 = user_guess();
			}
			else
				uguess = user_guess();

			if (pvp == 0)
			{
				for (int i = 0; i < uguess.size(); ++i)
				{
					if (uguess[i] == number[i]) ++bulls;
					else if ((number, uguess[i]) == 1) ++cows;
				}

				cout << "Bulls : " << bulls << "\n"
					<< "Cows : " << cows << endl;
			}
			else if(pvp == 1)
			{
				for (int i = 0; i < uguess1.size(); ++i)
				{
					if (uguess1[i] == uguessInputSecondPlayer[i]) ++bulls;
					else if (count(uguessInputSecondPlayer, uguess1[i]) == 1) ++cows;
				}

				cout <<"First player :" << "\n"
					<<  "Bulls : " << bulls << "\n"
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
			else
			{
				vector<char>  bullsCount;
				vector<char>  cowsCount;
				vector<char>  compOutput(4, 0);

				if (number[0] < 65)
				{
					for (int i = 0; i < 10; ++i) bullsCount.push_back(i + 48);
				}
				else
				{
					for (int i = 0; i < 26; ++i) bullsCount.push_back(i + 65);
				}
				int i = 0;
				while (cowsCount.size() != 4)
				{
					if (count(uguess, bullsCount[i]) == 1) cowsCount.push_back(bullsCount[i]);
					++i;
				}
				int j = 0;
				while (cowsCount.size() != 0)
				{
					while (compOutput[j] == 0)
					{
						if (compOutput[j] == cowsCount[i])
						{
							compOutput[j] = cowsCount[i];
							cowsCount.pop_back();
							--i;
						}
					}
					++j;
				}
				for (int i = 0; i < 4; ++i) cout << compOutput[i];

				bulls = 4;
			}
		}
		cout << "Do you want play again?[Y/N]";
		cin >> GameOver;
	}
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