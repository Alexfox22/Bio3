#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;
struct maxim
{
	int count;
	int position;
	char mean;
};
struct minim
{
	int count;
	int position;
	string mean;
};
int PatternCount(string text, string pattern)
{
	int count = 0;
	int position = 0;

	while (text.find(pattern, position) != string::npos)
	{
		position = text.find(pattern, position) + 1;
		count++;
	}
	return count;
}
string FreqentWords(string text, int count)
{
	string result;
	string pattern;
	int n = text.size();
	int *mas = new int[n];
	int max = -10000;
	for (int i = 0;i < n - count + 1;i++)
	{
		pattern = text.substr(i, count);
		mas[i] = PatternCount(text, pattern);
		if (mas[i] > max)
			max = mas[i];
	}
	for (int i = 0;i < n - count + 1;i++)
	{
		if (mas[i] == max)
		{

			if (PatternCount(result, text.substr(i, count)) == 0)
			{
				result = result + text.substr(i, count) + ' ';
			}

			else
			{
				int r = text.find(text.substr(i, count));
				result.erase(r, count + 1);
				result = result + text.substr(i, count) + ' ';

			}
		}
	}
	return result;
}
void copy(int *fir, int *sec, int len)
{
	for (int i = 0;i < len;i++)
		sec[i] = fir[i];
}
void make_null(int *mas, int len)
{
	for (int j = 0;j < (len);j++)
	{
		mas[j] = 0;

	}
}
void make_matrix(int **mas, int strlen, int cofstr, string *str, int *change,int kokoko)
{
	for (int i = 0;i < (cofstr);i++)
	{
		int k = 0;
		for (int j = 0 + change[i]+kokoko;j < strlen + change[i]+kokoko;j++)
		{
			if ((str[i].substr(j, 1) == "A")) { mas[0][k]++; }
			if ((str[i].substr(j, 1) == "C")) { mas[1][k]++; }
			if ((str[i].substr(j, 1) == "G")) { mas[2][k]++; }
			if ((str[i].substr(j, 1) == "T")) { mas[3][k]++; }
			k++;
		}

	}
}
void show_matrix(int **mas, int strlen)
{
	for (int i = 0;i < 4;i++)
	{
		for (int j = 0;j < (strlen);j++)
		{
			cout << mas[i][j] << ' ';
		}
		cout << endl;
	}

}
int consensusfirst(int **mas, int *popopo, int strlen, int max, int maxscore)
{
	//	cout << "////" << strlen << " " << max << " " << maxscore << endl;
	//int mx = 0;
	//	cout << "consensus: " << endl;

	int mx = 0;
	//show_matrix(mas, strlen);

	for (int i = 0;i < strlen;i++)
	{
		int maximus = 0;
		//cout << maximus << endl;
		
			for (int j = 0;j < (4);j++)
			{
				if (mas[j][i] > maximus)
				{
					maximus = mas[j][i];

				}
			}

			popopo[i] = maximus;
			mx = mx + popopo[i];
		//	cout << maximus << ' ';
	}

	return mx;
}
int consensus(int **mas, int *popopo, int strlen, int max, int maxscore,string cofstr,string* strs,int* ch)
{
//	cout << "////" << strlen << " " << max << " " << maxscore << endl;
	//int mx = 0;
//	cout << "consensus: " << endl;
	//cout << "maxscore ---> " << maxscore << endl;
	int maximus = 0;
	int mx = 0;
	for (int p = 0;p < 4;p++) mas[p][0] = 0;
	make_matrix(mas, 1, stoi(cofstr), strs, ch,0);
	show_matrix(mas, 1);
	for (int j = 0;j < (4);j++)
	{
		if (mas[j][0] > maximus)
		{
			maximus = mas[j][0];

		}
	}
	mx = mx + maximus;
	//maxscore = maxscore - maximus;
	cout << maximus << " | ";
	cout << "maxsc " << maxscore << endl;
	for (int i = 1;i < strlen;i++)
	{
		int maximus = 0;
		
		if (mx + (strlen - i)*max > maxscore)
		{
		cout << mx << " + " << (strlen - i)*max << " > " <<maxscore<< endl;
			cout << "maxscore ---> " << maxscore << endl;
			make_matrix(mas, 1, stoi(cofstr), strs, ch, i);
			show_matrix(mas, 1);
			for (int j = 0;j < (4);j++)
			{
				if (mas[j][0] > maximus)
				{
					maximus = mas[j][0];

				}
			}

			popopo[i] = maximus;
		//	maxscore = maxscore - mx;
			mx = mx + popopo[i];
			cout << maximus << " | ";
			
			
		}
		else
		{
			cout <<endl<< "hey, i'll out" << endl;
			mx = 0;
			break;
		}
	}
	
	return mx;
}
bool combination(int *mas, int tap, int m)
{
	int j = m - 1;
	while (j >= 0 && mas[j] == tap) j--;
	if (j < 0) return false;
	if (mas[j] >= tap)
		j--;
	mas[j]++;
	if (j == m - 1) return true;
	for (int k = j + 1; k < m; k++)
		mas[k] = 1;
	return true;
}
int Hamming(string text, string pat)
{
	int count = 0;
	for (int i = 0;i < pat.length();i++)
	{
		if (text.substr(i, 1) != pat.substr(i, 1)) count++;
	}
	return count;
}
minim TotalDistance(string str, string pat, int *mas)
{
	minim min;
	min.count = INT_MAX;
	int k = INT_MAX;
	for (int i = 0;i < str.length() - pat.length() + 1;i++)
	{
		mas[i] = Hamming(str.substr(i, pat.length()), pat);
		if (Hamming(str.substr(i, pat.length()), pat) < min.count)
		{
			min.count = Hamming(str.substr(i, pat.length()), pat);

			min.position = i;
		}

	}
	return min;
}
void main()
{
	int menu = -2;
	bool tried = false;
	ifstream imfile;
	imfile.open("input.txt");
	string text;
	string result;
	cout << "Press '0' to find with max " << endl;
	cout << "Press '1' to find with min " << endl;
	while ((menu != 0) && (menu != 1))
	{
		if (tried == true)
		{
			cout << "Wrong value. Please, press '0' or '1' " << endl;
		}
		cin >> menu;
		tried = true;
	}
	if (menu == 0)
	{

		string sze;
		string cofstr;
		string allbuf;

		cout << "Please, wait" << endl << endl;
		getline(imfile, allbuf);
		//cout << allbuf << endl;
		int loop = 0;
		for (int i = 0;i<allbuf.find(" ", 0) + 1;i++)
		{
			sze = sze + allbuf.substr(i, 1);
		}
		for (int i = allbuf.find(" ", 0) + 1;i<allbuf.length();i++)
		{
			cofstr = cofstr + allbuf.substr(i, 1);
		}
		string *strs = new string[stoi(cofstr)];
		for (int i = 0;i < stoi(cofstr);i++)
		{
			getline(imfile, strs[i]);
			//cout << strs[i] << endl;
		}
		int size = stoi(sze);  //длина мотива

		int strlen = strs[0].size();
		int timer = strlen - stoi(sze);
		int **mas = new int*[4];

		for (int i = 0;i < 4;i++)
		{
			mas[i] = new int[size];
			make_null(mas[i], size);
		}

		int *ch = new int[stoi(cofstr)];//массив смещений
		int *chbuf = new int[stoi(cofstr)];//массив смещений buffer
		int *ch2 = new int[stoi(cofstr)];//массив смещений buffer
		make_null(ch, stoi(cofstr));
		make_null(chbuf, stoi(cofstr));
		int maximum = 6;
		int *d = new int[size];
		bool twentyfive = false;
		bool fifty = false;
		bool seventyfive = false;
		bool hundred = false;
		bool g = true;
		int *foundmaxcycle = new int[size];
		int *foundmax = new int[size];
		for (int e = 0;e < stoi(cofstr);e++)
			ch2[e] = 1;
		bool isfirst = true;
		while (g)
		{
			

			
			int sumum = 0;
			//show_matrix(mas, size);
			if (isfirst==false) sumum = consensus(mas, d, size, stoi(cofstr), maximum, cofstr,strs,ch);
			else
			{
				sumum = consensusfirst(mas, d, size, stoi(cofstr), maximum);
				isfirst = false;
			}
			if (sumum > 0)
			{
			//	cout << "sumum " << sumum << endl;
			//	cout << "chbuf: " << endl;
			//	for (int e = 0;e < stoi(cofstr);e++)
			//		cout << ch[e] << ' ';
			//	cout << endl;
				//	cout << "___________________________________" << endl;
			}
			for (int l = 0;l < 4;l++)
				make_null(mas[l], size);

			if ((sumum > maximum))
			{
				//	cout << "passed comparison 2" << endl;

				maximum = sumum;
				copy(ch, chbuf, stoi(cofstr));
			}
			/*ch[stoi(cofstr)-i-1]++;*/
			g = combination(ch2, strlen - size + 1, stoi(cofstr));
			for (int e = 0;e < stoi(cofstr);e++)
				ch[e] = ch2[e] - 1;
			//	cout << "passed comparison 1" << endl;


			if ((ch[0] == timer / 4) && (twentyfive == false))
			{
				cout << "<---- 25% done ---->" << endl;
				twentyfive = true;
			}
			if ((ch[0] == timer / 2) && (fifty == false))
			{
				cout << "<---- 50% done ---->" << endl;
				fifty = true;
			}
			if ((ch[0] == 3 * timer / 4) && (seventyfive == false))
			{
				cout << "<---- 75% done ---->" << endl;
				seventyfive = true;
			}
			if ((ch[0] == timer) && (hundred == false))
			{
				cout << "<---- 90% done ---->" << endl;
				hundred = true;
			}

		}

		cout << "maximum: " << maximum << endl;

		for (int i = 0;i < stoi(cofstr);i++)
		{
			//cout << "___"<<chbuf[i] << " ";
			result = result + strs[i].substr(chbuf[i], size) + '\n';
		}
		cout << result;

	}
	if (menu == 1)
	{
		ifstream imfile2;
		imfile2.open("input.txt");
		string buf;
		int kit = 0;
		while (imfile2)
		{
			getline(imfile2, buf);
			kit++;
		}
		imfile2.close();
		ifstream imfile;
		imfile.open("input.txt");
		string count;
		string DNK;
		string sze;
		int coun;
		minim resic;
		resic.count = INT_MAX;
		getline(imfile, sze);
		cout << sze << endl;
		int sizeofpattern = stoi(sze);

		/*	getline(imfile, count);
		cout << count << endl;*/
		coun = kit - 2;
		string *strs = new string[coun];
		for (int i = 0;i < coun;i++)
		{
			getline(imfile, strs[i]);
			cout << strs[i] << endl;
		}

		int k = 0;
		int len = strs[0].length();
		int **mas = new int*[coun];
		cout << coun << "  <----coun    ";
		cout << len << "  <----len" << endl;
		for (int i = 0;i<coun;i++)
		{
			mas[i] = new int[len];
		}
		for (int i = 0;i < coun;i++)
		{
			for (int j = 0;j < len;j++)
			{
				mas[i][j] = 0;
			}

		}
		string pat;
		char *symb = new char[4];
		symb[0] = 'A';
		symb[1] = 'C';
		symb[2] = 'G';
		symb[3] = 'T';
		bool rere = true;
		string nul;
		int *comb = new int[sizeofpattern];
		for (int i = 0;i < sizeofpattern - 1;i++)
			comb[i] = 1;
		comb[sizeofpattern - 1] = 0;
		minim *minimus = new minim[coun];
		while (rere)
		{

			rere = combination(comb, 4, sizeofpattern);
			//for (int i = 0;i < sizeofpattern;i++)
			//cout << comb[i] << "  -- ";
			//cout << endl;
			for (int k = 0;k < sizeofpattern;k++)
				pat = pat + symb[comb[k] - 1];
			//cout << "<--" << pat << "-->" << endl;
			for (int i = 0;i < coun;i++)
			{
				minimus[i] = TotalDistance(strs[i], pat, mas[i]);
			}
			int sum = 0;
			for (int i = 0;i < coun;i++)
			{
				sum = sum + minimus[i].count;
			}
			for (int i = 0;i < coun;i++)
			{

				for (int j = 0;j < len - sizeofpattern + 1;j++)
				{

					//cout << mas[i][j] << "  ";
				}
				if (sum < resic.count)
				{
					resic.count = sum;
					resic.mean = pat;
				}
				//cout << "| " << minimus[i].count << endl;

			}
			pat = nul;

		}
		cout << resic.count << "____" << resic.mean << endl;
		result = resic.mean;

	}

	ofstream exfile;
	exfile.open("output.txt");
	exfile << result;
	exfile.close();
	imfile.close();

}