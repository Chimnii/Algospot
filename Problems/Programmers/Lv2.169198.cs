using System;

public class Solution
{
    public int dist(int sx, int sy, int bx, int by)
    {
        return (sx - bx) * (sx - bx) + (sy - by) * (sy - by);
    }
    public int moved_dist(int m, int n, int sx, int sy, int bx, int by)
    {
        int max = Int32.MaxValue;
        int dist1 = (sy != by || sx < bx) ? dist(-sx, sy, bx, by) : max;
        int dist2 = (sx != bx || sy < by) ? dist(sx, -sy, bx, by) : max;
        int dist3 = (sy != by || sx > bx) ? dist(m+m-sx, sy, bx, by) : max;
        int dist4 = (sx != bx || sy > by) ? dist(sx, n+n-sy, bx, by) : max;
        return Math.Min(dist1, Math.Min(dist2, Math.Min(dist3, dist4)));
    }
    
    public int[] solution(int m, int n, int startX, int startY, int[,] balls)
    {
        int[] answer = new int[balls.GetLength(0)];
        for (int i = 0; i < balls.GetLength(0); ++i)
        {
            int bx = balls[i, 0], by = balls[i, 1];
            answer[i] = moved_dist(m, n, startX, startY, bx, by);
        }
        
        return answer;
    }
}