#include <string>
#include <vector>

using namespace std;

vector<int> calc_price(vector<int>& sales, const vector<vector<int>>& users, const vector<int>& emoticons)
{
    int plus = 0, total_price = 0;
    for (const vector<int>& user : users)
    {
        int buyable = user[0];
        int plusable = user[1];
        
        int buyable_price = 0;
        for (int i = 0; i < emoticons.size(); ++i)
        {
            buyable_price += (sales[i] >= buyable ? emoticons[i] * (100-sales[i]) / 100 : 0);
        }
        if (buyable_price >= plusable) ++plus;
        else total_price += buyable_price;
    }
    
    return {plus, total_price};
}
vector<int> find_best_sales(vector<int>& sales, int index, const vector<vector<int>>& users, const vector<int>& emoticons)
{
    if (index >= emoticons.size())
    {
        return calc_price(sales, users, emoticons);
    }
    
    vector<int> best = {0, 0};
    for (int sale : {10, 20, 30, 40})
    {
        sales[index] = sale;
        vector<int> price = find_best_sales(sales, index+1, users, emoticons);
        if (best[0] < price[0]) best = price;
        if (best[0] == price[0] && best[1] < price[1]) best = price;
    }
    return best;
}

vector<int> solution(vector<vector<int>> users, vector<int> emoticons)
{
    vector<int> sales(emoticons.size());
    vector<int> best_price = find_best_sales(sales, 0, users, emoticons);
    return best_price;
}