#include <string>
#include <vector>
#include <algorithm>

using namespace std;

string to_binary(long long num)
{
    string binary = ""s;
    while (num > 0)
    {
        binary += (num % 2) + '0';
        num /= 2;
    }
    reverse(binary.begin(), binary.end());
    return binary;
}

bool is_all_zero(const string& binary)
{
    for (auto c : binary)
        if (c == '1')
            return false;
    return true;
}

bool is_cbt(const string& binary)
{
    int len = binary.length();
    if (len == 0 || len == 1)
        return true;
    if (len % 2 == 0)
        return false;
    
    int mid = len/2;
    if (binary[mid] == '0')
        return is_all_zero(binary.substr(0, mid)) && is_all_zero(binary.substr(mid+1,  mid));
    else
        return is_cbt(binary.substr(0, mid)) && is_cbt(binary.substr(mid+1, mid));
}
vector<int> solution(vector<long long> numbers)
{
    vector<int> answer;
    
    for (long long n : numbers)
    {
        string binary = to_binary(n);
        int len = binary.length();
        
        bool cbt = false;
        while (len-- > 0)
        {
            if (is_cbt(binary))
            {
                cbt = true;
                break;
            }
            binary.insert(0, 1, '0');
        }
        answer.emplace_back(cbt ? 1 : 0);
    }
    
    return answer;
}