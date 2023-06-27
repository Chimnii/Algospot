#include <string>
#include <vector>

using namespace std;

int min(int a1, int a2) { return a1 < a2 ? a1 : a2; }
struct metal
{
    int d, i, s;
    metal() : d(0), i(0), s(0) {}
    metal(int _d, int _i, int _s) : d(_d), i(_i), s(_s) {}
    void emplace(const vector<int>& picks)
    {
        d += (picks.size() > 0 ? picks[0] : 0);
        i += (picks.size() > 1 ? picks[1] : 0);
        s += (picks.size() > 2 ? picks[2] : 0);
    }
    void emplace(const string& mineral)
    {
        d += (mineral == "diamond"s ? 1 : 0);
        i += (mineral == "iron"s ? 1 : 0);
        s += (mineral == "stone"s ? 1 : 0);
    }
    void print() const { printf("d=%d, i=%d, s=%d\n", d, i, s); }
    bool is_empty() const { return d == 0 && i == 0 && s == 0; }
    int calc_energy_by_dia() const { return (d + i + s); }
    int calc_energy_by_iron() const { return (d*5 + i + s); }
    int calc_energy_by_stone() const { return (d*25 + i*5 + s); }
};

int calc_minimum_energy(metal& pick, const vector<metal>& mines, int index)
{
    if (pick.is_empty())
        return 0;
    if (index >= mines.size())
        return 0;

    int d = 1250, i = 1250, s = 1250;
    if (pick.d > 0)
    {
        --pick.d;
        d = mines[index].calc_energy_by_dia() + calc_minimum_energy(pick, mines, index+1);
        ++pick.d;
    }
    if (pick.i > 0)
    {
        --pick.i;
        i = mines[index].calc_energy_by_iron() + calc_minimum_energy(pick, mines, index+1);
        ++pick.i;
    }
    if (pick.s > 0)
    {
        --pick.s;
        s = mines[index].calc_energy_by_stone() + calc_minimum_energy(pick, mines, index+1);
        ++pick.s;
    }

    return min(min(d, s), i);
}

int solution(vector<int> picks, vector<string> minerals)
{
    metal pick;
    pick.emplace(picks);

    vector<metal> mines;
    for (int i = 0; i < minerals.size(); i += 5)
    {
        metal mine;
        for (int j = 0; j < 5 && i + j < minerals.size(); ++j)
        {
            mine.emplace(minerals[i+j]);
        }
        mines.emplace_back(mine);
    }

    return calc_minimum_energy(pick, mines, 0);
}