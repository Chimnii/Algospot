#include <string>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

vector<int> nodes;
vector<bool> lighton;
vector<set<int>> vertices;

void print()
{
    printf("nodes - ");
    for (int n : nodes) printf("%d ", n);
    printf("\nvertices");
    for (int i = 1; i < vertices.size(); ++i)
    {
        printf("\n%d: {", i);
        for (int n : vertices[i]) printf("%d ", n);
        printf("}");
    }
    printf("\nlighton: ");
    for (bool b : lighton) printf("%d ", b ? 1 : 0);
    printf("\n");
}
void fill_vertices(int n, const vector<vector<int>>& lighthouse)
{
    vertices.resize(n+1);
    for (const vector<int>& v : lighthouse)
    {
        vertices[v[0]].emplace(v[1]);
        vertices[v[1]].emplace(v[0]);
    }
}

void on_light(int n)
{
    if (lighton[n])
        return;
    
    lighton[n] = true;
    for (int v : vertices[n])
    {
        vertices[v].erase(n);
    }
    vertices[n].clear();
}
               
bool lighton_leaves()
{
    set<int> leaves_conn;
    while (nodes.size() > 0)
    {
        int node = nodes.back();
        if (lighton[node]) { nodes.pop_back(); continue; }
        if (vertices[node].size() == 0) { nodes.pop_back(); continue; }
        if (leaves_conn.find(node) != leaves_conn.end()) { nodes.pop_back(); continue; }
        if (vertices[node].size() == 1)
        {
            leaves_conn.emplace(*vertices[node].begin());
            nodes.pop_back();
            continue;
        }
        break;
    }
    
    for (int n : leaves_conn)
    {
        on_light(n);
    }
    
    return leaves_conn.size() > 0;
}

bool lighton_somethings()
{
    while (nodes.size() > 0)
    {
        int node = nodes.back();
        if (lighton[node]) { nodes.pop_back(); continue; }
        if (vertices[node].size() == 0) { nodes.pop_back(); continue; }
        
        int first = nodes[0];
        nodes[0] = node;
        nodes.pop_back();
        if (lighton[first]) { continue; }
        on_light(first);
        return true;
    }
    return false;
}
int solution(int n, vector<vector<int>> lighthouse)
{
    fill_vertices(n, lighthouse);
    nodes.resize(n);
    lighton.resize(n+1);
    for (int i = 1; i <= n; ++i)
    {
        nodes[i-1] = i;
        lighton[i] = false;
    }
    
    while (nodes.size() > 0)
    {
        sort(nodes.begin(), nodes.end(), [](int n1, int n2) -> bool { return vertices[n1].size() > vertices[n2].size(); });
        
        if (lighton_leaves()) continue;
        //if (lighton_somethings()) continue;
        break;
    }
    
    return count(lighton.begin(), lighton.end(), 1);
}