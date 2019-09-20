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
		cout << "Write the mount of players : ";

		int mount;
		cin >> mount;

		srand(time(NULL));

		vector<vector<char>> uguess;
		vector<char> number = create();

		for (int info = 1; info <= mount; ++info)
		{
			for (int i = 0; 1; i)
			{
				vector<int> bulls(10, 0);
				vector<int> cows(10, 0);

				for (int j = 0; j < mount; ++j)
				{
					cout << j << " Players";
					uguess[j] = user_guess();
				}
				for (int j = 0; j < mount; ++j)
				{
					for (int i = 0; i < uguess.size(); ++i)
					{
						if (i != uguess.size())
							if (uguess[j][i] == uguess[j + 1][i]) ++bulls[j];
							else if (count(uguess[+1], uguess[info][i]) == 1) ++cows[j];
							else
								if (uguess[info][i] == uguess[0][i]) ++bulls[j];
								else if (count(uguess[0], uguess[info][i]) == 1) ++cows[j];
					}
					cout << j + 1 << " Players " << "Bulls : " << bulls[j] << "\n"
						<< j + 1 << " Players " << "Cows : " << cows[j] << endl;
				}
			}
			cout << "Do you want play again?[Y/N]";
		}
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