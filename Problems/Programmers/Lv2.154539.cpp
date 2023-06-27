#include <vector>
#include <stack>
using namespace std;

vector<int> solution(vector<int> numbers)
{
    vector<int> answers(numbers.size());
    
    stack<int> highest;
    highest.emplace(-1);
    
    for(int i = numbers.size() - 1; i >= 0; --i)
    {
        int curr = numbers[i];
        
        while(highest.top() != -1 && curr >= highest.top())
        {
            highest.pop();
        }
        
        answers[i] = highest.top();
        highest.emplace(curr);
    }
    
    return answers;
}
