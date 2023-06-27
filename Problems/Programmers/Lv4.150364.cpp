#include <string>
#include <vector>
#include <algorithm>

using namespace std;

struct node
{
    int id = 0;
    int path_index = 0;
    vector<int> paths;
    vector<int> points;
    
    bool add_point(int& need_point)
    {
        for (int i = 0; i < points.size(); ++i)
        {
            if (need_point >= 3)
                break;
            
            int extra = min(3 - need_point, points[i] - 1);
            points[i] -= extra;
            need_point += extra;
        }
        
        if (need_point <= 0)
            return false;
        
        int point = min(3, need_point);
        need_point -= point;
        points.emplace_back(point);
        return true;
    }
};

void make_nodes(vector<node>& out_nodes, const vector<vector<int>>& edges)
{
    out_nodes.clear();
    out_nodes.resize(edges.size() + 2);
    for(const vector<int>& edge : edges)
    {
        out_nodes[edge[0]].paths.emplace_back(edge[1]);
    }
    
    for (int i = 0; i < out_nodes.size(); ++i)
    {
        out_nodes[i].id = i;
        sort(out_nodes[i].paths.begin(), out_nodes[i].paths.end());
    }
}

int next_node(vector<node>& nodes)
{
    int id = 1;
    
    while(nodes[id].paths.size() > 0)
    {
        node& n = nodes[id];
        id = n.paths[n.path_index];
        n.path_index = (n.path_index + 1) % n.paths.size();
    }
    
    return id;
}

bool make_points(vector<node>& nodes, vector<int>& targets)
{
    int total_remain = 0;
    for (int n : targets) total_remain += n;
    
    while (total_remain > 0)
    {
        int id = next_node(nodes);
        int target = targets[id];
        if (!nodes[id].add_point(target))
            return false;
        
        total_remain -= (targets[id] - target);
        targets[id] = target;
    }
    
    return true;
}

vector<int> make_answers(vector<node>& nodes)
{
    vector<int> answer;
    
    while(true)
    {
        int id = next_node(nodes);
        node& n = nodes[id];
        if (n.points.size() == 0)
            break;
        answer.emplace_back(n.points[0]);
        n.points.erase(n.points.begin());
    }
    
    return answer;
}

vector<int> solution(vector<vector<int>> edges, vector<int> target)
{
    vector<node> nodes;
    make_nodes(nodes, edges);
    
    target.insert(target.begin(), 0);
    
    if (make_points(nodes, target))
    {
        for(node& n : nodes) n.path_index = 0;
        return make_answers(nodes);
    }
    else
    {
        return {-1};
    }
}