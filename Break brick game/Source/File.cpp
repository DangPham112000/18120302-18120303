#include "File.h"

int File::Docfile()
{
	f.open("HighScore.txt");
	string a;
	getline(f, a);
	int score = atoi(a.c_str());
	f.close();
	return score;
}

void File::Ghifile(int score)
{
	f.open("HighScore.txt", ios::out);
	f << score;
	f.close();
}
