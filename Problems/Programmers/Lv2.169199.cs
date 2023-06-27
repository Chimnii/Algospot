using System;
using System.Linq;

public class Solution
{
    int length_i, length_j;
    int[] dists;
    string[] cells;
    int dist(int i, int j) { return dists[i*length_j + j]; }
    void set_dist(int i, int j, int n) { dists[i*length_j + j] = n; }
    char cell(int i, int j) { return cells[i][j]; }
    
    void print()
    {
        for (int i = 0; i < length_i; ++i)
        {
            for (int j = 0; j < length_j; ++j)
            {
                if (dist(i, j) == 0) Console.Write(cell(i, j));
                else Console.Write(dist(i, j));
            }
            Console.WriteLine();
        }
    }
    
    void find_start_point(out int start_i, out int start_j)
    {
        start_i = 0; start_j = 0;
        for (start_i = 0; start_i < length_i; ++start_i)
            for (start_j = 0; start_j < length_j; ++start_j)
                if (cell(start_i, start_j) == 'R')
                    return;
    }
    
    int go_toward(int di, int dj, int i, int j, int turn)
    {
        //Console.WriteLine("go_toward {0}/{1}, {2}/{3}, {2}", i, di, j, dj, turn);
        int n = 1;
        while (true)
        {
            int ci = i + di * n;
            int cj = j + dj * n;
            if (ci < 0 || cj < 0 || ci >= length_i || cj >= length_j)
                break;
            if (cell(ci, cj) == 'D')
                break;
            ++n;
        }
        --n;
        return find_to_goal_dist(i + di * n, j + dj * n, turn + 1);
    }
    
    int find_to_goal_dist(int i, int j, int turn)
    {
        //Console.WriteLine("find_to_goal_dist {0}, {1}, {2}", i, j, turn);
        if (cell(i, j) == 'G') return turn;
        if (cell(i, j) == 'R' && turn > 0) return -1;
        if (dist(i, j) != 0 && dist(i, j) <= turn) return -1;
        //Console.WriteLine("set_dist {0}, {1}, {2}", i, j, turn);
        set_dist(i, j, turn);
        //print();
        
        int[] toward_dist = new int[4];
        toward_dist[0] = go_toward(-1, 0, i, j, turn);
        toward_dist[1] = go_toward(1, 0, i, j, turn);
        toward_dist[2] = go_toward(0, -1, i, j, turn);
        toward_dist[3] = go_toward(0, 1, i, j, turn);
        
        int answer = -1;
        foreach (int d in toward_dist)
        {
            if (d != -1 && (answer == -1 || d < answer))
                answer = d;
        }
        
        return answer;
    }
    public int solution(string[] board)
    {
        length_i = board.Length;
        length_j = board[0].Length;
        dists = Enumerable.Repeat(0, length_i * length_j).ToArray();
        cells = board;
        //Console.WriteLine("length_i={0}, length_j={1}", length_i, length_j);
        
        int start_i, start_j;
        find_start_point(out start_i, out start_j);

        int min_dist = find_to_goal_dist(start_i, start_j, 0);
        return min_dist;
    }
}