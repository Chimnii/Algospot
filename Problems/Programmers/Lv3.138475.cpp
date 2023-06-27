#include <string>
#include <vector>

using namespace std;

constexpr int max_num = 5000000;
int saved_divs[max_num+1] = {0, };

int saved_maxs[max_num+1] = {0, };

int get_div_count(int n, int e)
{
    if (saved_divs[n] != 0) return saved_divs[n];
    
    for (int i = 2; i <= e; ++i)
    {
        int m = i;
        while (m <= e)
        {
            ++saved_divs[m];
            m += i;
        }
    }
    
    return saved_divs[n];
}

int get_max(int s, int e)
{
    if (saved_maxs[s] != 0) return saved_maxs[s];
    
    int max_div = 0, max_n = max_num;
    for (int i = e; i >= 1; --i)
    {
        int div = get_div_count(i, e);
        if (div >= max_div)
        {
            max_div = div;
            max_n = i;
        }
        saved_maxs[i] = max_n;
    }
    return saved_maxs[s];
}

vector<int> solution(int e, vector<int> starts)
{
    vector<int> answers;
    for (int s : starts)
    {
        answers.emplace_back(get_max(s, e));
    }
    
    return answers;
}