#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <string>
#include <queue>
#include <iostream>

template <typename T>
class queue
{
	struct que
	{
		T data;
		int priority;
		que* next = nullptr;
		que* prev = nullptr;

		que() {}

		que(T data, que* next = nullptr, que* prev = nullptr)
		{
			this->data = data;
			this->next = next;
			this->prev = prev;
		}
	};

	size_t size = 0;

	que* root = nullptr;
	que* head = nullptr;


public:
	void enqueue(T _data)
	{
		if (root != nullptr)
		{
			root = new que(_data, root);
			root->next->prev = root;
			++size;
		}
		else
		{
			head = root = new que(_data);
			++size;
		}
	}

	T dequeue()
	{
		if (size > 0)
		{
			que* temp = head;
			T t = temp->data;
			if (size == 1)
			{
				root = nullptr;
				head = nullptr;
			}
			else
			{
				head = head->prev;
				head->next = nullptr;
			}
			--size;
			delete temp;
			return t;
		}

		throw;
	}

	bool check_queue()
	{
		if (size > 0)
		{
			return 1;
		}
		return 1;
	}

	int get_size()
	{
		return size;
	}



	bool find(T _data)
	{
		que* temp = root;
		if (size > 0)
		{
			while (temp != nullptr)
			{
				if (temp->data == _data)
				{
					return true;
				}
				temp = temp->next;
			}
		}

		return false;
	}
};

struct coor
{
	int x;
	int y;
};

void main()
{
	int const n = 20, m = 20;
	char map[n][m];
	coor check[n][m] = {};

	queue<std::pair<int, int>> islands;
	int count = 0;
	std::pair<int, int>s_p;
	std::pair<int, int>f_p;

	FILE* f = fopen("map.txt", "r");
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < m; ++j)
		{
			map[i][j] = fgetc(f);
			fgetc(f);
			if (map[i][j] == 's')
			{
				s_p.first = i;
				s_p.second = j;
				//				map[i][j] = '1';
			}
			if (map[i][j] == 'f')
			{
				f_p.first = i;
				f_p.second = j;
				map[i][j] = 'M';
			}
		}
	}

	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < m; ++j)
		{
			printf("%c ", map[i][j]);
		}
		printf("\n");
	}
	printf("\n");

	std::pair<int, int> part;

	int k = s_p.first;
	int l = s_p.second;

	check[k][l].x = -1;
	check[k][l].y = -1;

	if (map[k][l] == 's')
	{
		count = 0;
		islands.enqueue({ k, l });
		// k -> x
		// l -> y

		map[k][l] = '2';
		int i, j;

		while (islands.get_size())
		{
			part = islands.dequeue();
			if (part.first == f_p.first && part.second == f_p.second)
			{
				printf("The way was found\n");
				coor temp = check[f_p.first][f_p.second];
				int b = f_p.second;

				//while (a != s_p.first && b!= s_p.second)//WHILE
				while (temp.x != -1)
				{
					map[temp.y][temp.x] = '#';
					temp = check[temp.y][temp.x];
					//printf("%d\n", i++);
				}
				break;
			}
			++count;
			i = part.first;
			j = part.second;

			if (i > 0 && map[i - 1][j] == 'M')
			{
				check[i - 1][j].x = j;
				check[i - 1][j].y = i;
				islands.enqueue({ i - 1, j });
				map[i - 1][j] = '2';
			}

			if (i < n - 1)
			{
				if (map[i + 1][j] == 'M')
				{
					check[i + 1][j].x = j;
					check[i + 1][j].y = i;
					islands.enqueue({ i + 1, j });
					map[i + 1][j] = '2';
				}
			}
			if (j > 0)
			{
				if (map[i][j - 1] == 'M') //Error
				{
					check[i][j - 1].x = j;
					check[i][j - 1].y = i;
					islands.enqueue({ i, j - 1 });
					map[i][j - 1] = '2';
				}
			}
			if (j < m - 1)
			{
				if (map[i][j + 1] == 'M')//Error
				{
					check[i][j + 1].x = j;
					check[i][j + 1].y = i;
					islands.enqueue({ i, j + 1 });
					map[i][j + 1] = '2';

				}
			}


		}
	}
	// int count1 = 0;
	// for (int i = 0; i < n; ++i)
	// {
	// 	for (int j = 0; j < m; ++j)
	// 	{
	// 		if (map[i][j] == '#')
	// 		{
	// 			++count1;
	// 		}
	// 	}
	//
	// }
	//printf("\n%d - count\n", count1);

	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < m; ++j)
		{
			printf("%c ", map[i][j]);
		}
		printf("\n");
	}
	system("pause");
}