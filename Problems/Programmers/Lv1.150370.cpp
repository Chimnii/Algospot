#include <string>
#include <vector>
#include <map>
#include <cstdlib>
#include <cstdio>

using namespace std;

int string_to_day(const string& date)
{
    int y = atoi(date.substr(0, 4).c_str());
    int m = atoi(date.substr(5, 2).c_str());
    int d = atoi(date.substr(8, 2).c_str());
    return y * 28 * 12 + m * 28 + d;
}
map<int, int> terms_to_day(const vector<string>& terms)
{
    map<int, int> termsday;
    for (const string& term : terms)
    {
        termsday.emplace(term[0], 28*atoi(term.substr(2,term.length()-2).c_str()));
    }
    return termsday;
}
void privacy_to_day_term(const string& privacy, int& out_start, int& out_term)
{
    string date = privacy.substr(0, 10);
    out_start = string_to_day(date);
    out_term = privacy[11];
}

vector<int> solution(string today, vector<string> terms, vector<string> privacies)
{
    map<int, int> termsday = terms_to_day(terms);
    
    int curr = string_to_day(today);
    
    vector<int> answers;
    for (int i = 0; i < privacies.size(); ++i)
    {
        const string& privacy = privacies[i];
        
        int start, term;
        privacy_to_day_term(privacy, start, term);
        
        if (start + termsday[term] <= curr)
            answers.emplace_back(i+1);
    }
    
    return answers;
}