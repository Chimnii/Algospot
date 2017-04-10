#include <cstdio>
#include <cstring>

void to_nine(char* c, int begin, int end)
{
	for (int i = begin; i < end; ++i)
		c[i] = '9';
}

void get_tidy(char* c, int len)
{
	int desc = len;
	for (int i = 1; i < len; ++i)
	{
		if (c[i] < c[i-1])
		{
			desc = i;
			break;
		}
	}

	if (desc == len)
		return;

	while (desc--)
	{
		if (desc == 0)
		{
			if (c[desc] > '1')
			{
				c[desc]--;
				to_nine(c, desc+1, len);
			}
			else
			{
				to_nine(c, desc, len);
				c[len-1] = 0;
			}

			break;
		}
		else if(c[desc] - c[desc-1] >= 1)
		{
			c[desc]--;
			to_nine(c, desc+1, len);
			break;
		}
	}
}

int main()
{
	FILE *fin, *fout;
	freopen_s(&fin, "CodeJam\\TidyNumbers_in.txt", "r", stdin);
	freopen_s(&fout, "CodeJam\\TidyNumbers_out.txt", "w", stdout);

	int t;
	scanf_s("%d", &t);

	for (int i = 1; i <= t; ++i)
	{
		char c[25];
		scanf_s("%s", c, sizeof(c));

		get_tidy(c, strlen(c));

		printf("Case #%d: %s\n", i, c);
	}

	return 0;
}
