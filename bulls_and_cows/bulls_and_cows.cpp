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

	while ((setting != "[A-Z]") && (setting != "[0-9]"))
	{
		cout << "Unkown language" << "\n";
		cout << "Choose your language [A-Z]/[0-9] : ";
		cin >> setting;
	}

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

		vector<char> uguess;
		vector<char> uguessInputFirstPlayer;
		vector<char> uguessInputSecondPlayer;
		vector<char> uguess1;
		vector<char> uguess2;

		uguess = user_guess();

		for (int i = 0; i < uguess.size(); ++i)
		{
			if (uguess[i] == number[i]) ++bulls;
			else if (count(number, uguess[i]) == 1) ++cows;
		}

		cout << "Bulls : " << bulls << "\n"
			<< "Cows : " << cows << endl;
		
	}
}

int main()
try
{
	srand(time(NULL));

	cout << " << Bulls and Cows" << "\n"
		<< " Computer sets a number or capital letters of 4 unique digits" << "\n"
		<< " Try to guess it." << "\n"
		<< " <Bull> means right digit or letters in the right position." << "\n"
		<< " <Cow> means right digit or letters in the wrong position" << "\n"
		<< "\n"
		<< " Game is on" << endl;

	char GameOver = 'Y';

	cout << " Do you want play ? [Y/N] : ";
	cin >> GameOver;

	while (GameOver == 'Y')
	{
		string gamemode = "0";

		while ((gamemode != "1") && (gamemode != "2") && (gamemode != "3"))
		{
			cout << "Choose your game mode : " << "\n"
				<< "1) Player VS Player." << "\n"
				<< "2) Player VS Comp." << "\n"
				<< "3) ??? " << endl;
			cin >> gamemode;
		}

		if (gamemode == "1") player_vs_player();
		else if (gamemode == "2") player_vs_comp();

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