#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;
struct max
{
	int count;
	int position;
	char mean;
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
void bubblesortc(max *x, int len)
{
	max temp;
	for (int i = 0; i < len - 1; i++)
	{
		for (int j = i + 1; j < len; j++)
		{
			if (x[i].count < x[j].count)
			{
				temp = x[i];
				x[i] = x[j];
				x[j] = temp;
			}

		}
	}
}
void bubblesortp(max *x, int len)
{
	max temp;
	for (int i = 0; i < len - 1; i++)
	{
		for (int j = i + 1; j < len; j++)
		{
			if (x[i].position < x[j].position)
			{
				temp = x[i];
				x[i] = x[j];
				x[j] = temp;
			}

		}
	}
}
void insertSort(max* a, int size)
{
	max tmp;
	int j;
	for (int i = 1; i < size; ++i)
	{
		tmp = a[i];
		for (j = i - 1; j >= 0 && a[j].position > tmp.position; --j)
			a[j + 1] = a[j];
		a[j + 1] = tmp;
	}
}
max min(max *buffer,int size)
{
	max m;
	m.count = 0;
	m.mean = ' ';
	m.position = 0;
	int r=0;
	m.position = 999999;
	for (int k = 0;k < size;k++)
	{
		
		if (buffer[k].position < m.position)
		{
			m = buffer[k];
			r = k;
		}
	}
	buffer[r].position = 1000000000;
	return m;
}
void make_matrix(int **mas,int strlen,int cofstr,string text)
{
	for (int i = 0;i < (strlen);i++)
	{
		for (int j = 0;j <cofstr;j++)
		{
			if ((text.substr(j*(strlen + 1) + i, 1) == "A"))   mas[0][i]++;
			if ((text.substr(j*(strlen + 1) + i, 1) == "C"))   mas[1][i]++;
			if ((text.substr(j*(strlen + 1) + i, 1) == "G"))   mas[2][i]++;
			if ((text.substr(j*(strlen + 1) + i, 1) == "T"))   mas[3][i]++;
		}

	}
}
void show_matrix(int **mas,int strlen)
{
	for (int i = 0;i < 4;i++)
	{
		for (int j = 0;j < (strlen);j++)
		{
			cout << mas[i][j] << ' ';
		}
		cout << endl;
	}
	cout << endl;
}
void consensus(int **mas, max *popopo,int strlen)
{
	cout << "maximum: ";
	for (int i = 0;i < strlen;i++)
	{
		int maximus = -10000000;
		for (int j = 0;j < (4);j++)
		{
			if (mas[j][i] > maximus)
			{
				maximus = mas[j][i];
				if (j == 0) popopo[i].mean = 'A';
				if (j == 1) popopo[i].mean = 'C';
				if (j == 2) popopo[i].mean = 'G';
				if (j == 3) popopo[i].mean = 'T';

			}
		}
		popopo[i].count = maximus;
		popopo[i].position = i;
		cout << popopo[i].count << ' ';
	}
	cout << endl;
	for (int i = 0; i< strlen;i++)
		cout << popopo[i].position << ' ';
	cout << endl;
	cout << " consen: ";
	for (int i = 0;i < strlen;i++)
	{
		cout << popopo[i].mean << ' ';
	}
	cout << endl;
}
void main()
{
	int menu = -2;
	bool tried = false;
	ifstream imfile;
	imfile.open("input.txt");
	string text;
	string res;
	cout << "Press '0' to find pattern count " << endl;
	cout << "Press '1' to find freqen words " << endl;
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

		string size;
		string cofstr;
		if (!imfile.is_open())
			cout << "Cannot open'input.txt'";
		else
		{
			getline(imfile, size);
			getline(imfile, cofstr);
			string buf;
			for (int i = 0;i < stoi(cofstr);i++)
			{
				getline(imfile, buf);
				text = text + buf + '\n';
			}
		}
		cout << size << endl;
		cout << cofstr << endl;
		cout << text << endl;
		int strlen = text.size() / stoi(cofstr) - 1;
		int **mas = new int*[4];

		string out = " ";

		for (int i = 0;i < 4;i++)
		{
			mas[i] = new int[strlen];
		}
		for (int i = 0;i < 4;i++)
		{
			for (int j = 0;j < (strlen);j++)
			{
				mas[i][j] = 0;
			}
		}
	
		make_matrix(mas, strlen, stoi(cofstr), text);
		show_matrix(mas, strlen);
		
		max *popopo = new max[strlen];
		consensus(mas, popopo, strlen);

		bubblesortc(popopo, strlen);
		max *buffer = new max[stoi(size)];
		max *bufferino = new max[stoi(size)];
		for (int i = 0;i < strlen;i++)
			cout << popopo[i].count << ' ';
		cout << endl;
		for (int i = 0;i < strlen;i++)
			cout << popopo[i].mean << ' ';
		cout << endl;
		for (int i = 0;i < strlen;i++)
			cout << popopo[i].position << ' ';
		cout << endl;
		bool e = false;
		for (int s = 0;s < stoi(cofstr);s++)
		{

			for (int i = 0;i < strlen - 3;i++)
			{
				
				buffer[0]=popopo[i];
				for (int j = i + 1;j < strlen - 2;j++)
				{
					buffer[1] = popopo[j];
					for (int k = j + 1;k < strlen - 1;k++)
					{
						string sbuf;
						buffer[2] = popopo[k];
						for (int t = 0;t < 3;t++)
						{
						//	sbuf = sbuf + buffer[t].mean;
							cout << buffer[t].position << ' ';
						}
						cout << endl;
						//cout << sbuf << endl;
						for (int r = 0;r < stoi(size);r++)
							bufferino[r] = min(buffer, stoi(size));
					//	bubblesortp(bufferino, stoi(size));
						for (int t = 0;t<3;t++)
							sbuf = sbuf + bufferino[t].mean;
						cout << sbuf << endl;
						if (PatternCount((text.substr(s*(strlen + 1), strlen)), sbuf) != 0)
						{
							out = out + sbuf + ' ';
							e = true;
							break;
						}
						
						if (e == true) break;
						
					}
					
					if (e == true) break;
				}
				if (e == true) continue;
			}

		}
		cout << out;

		//ofstream exfile;
		//exfile.open("file2.txt");
		//exfile << out;
	}
	if (menu == 1)
	{
		string count;

		if (!imfile.is_open())
			cout << "Cannot open'input.txt'";
		else
		{
			getline(imfile, text);
			getline(imfile, count);
		}
		res = FreqentWords(text, stoi(count));
	}
	ofstream exfile;
	exfile.open("output.txt");
	exfile << res;

	imfile.close();
	exfile.close();
}