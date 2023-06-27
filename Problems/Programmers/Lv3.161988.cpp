#include <string>
#include <vector>

using namespace std;
long long max(long long m1, long long m2) { return m1 > m2 ? m1 : m2; }
long long find_lpss(const vector<int>& seq)
{
    long long current_lpss = (seq.size() > 0 ? seq[seq.size() - 1] : 0);
    long long max_lpss = current_lpss;
    
    for (int i = seq.size() - 2; i >= 0; --i)
    {
        int current = seq[i];
        max_lpss = max(max_lpss, current);
        
        current_lpss = max(max(current_lpss + current, current), 0ll);
        max_lpss = max(max_lpss, current_lpss);
    }
    
    return max_lpss;
}

void pulse(vector<int>& seq, int sign)
{
    for (int& s : seq)
    {
        s *= sign;
        sign *= -1;
    }
}

long long solution(vector<int> sequence)
{
    long long answer = 0;
    
    pulse(sequence, 1);
    answer = max(answer, find_lpss(sequence));
    
    pulse(sequence, 1);
    pulse(sequence, -1);
    answer = max(answer, find_lpss(sequence));

    return answer;
}