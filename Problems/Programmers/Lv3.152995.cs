using System;

public class Solution
{
    public class score
    {
        public int l, r;
        public score(int _l, int _r) { l = _l; r = _r; }
        public int sum() { return l + r; }
    }
    
    public bool check_pass(score[] scores, score wanho)
    {
        Array.Sort(scores, (s1, s2) => s1.l > s2.l ? -1 : (s1.l == s2.l && s1.r > s2.r) ? -1 : 1);
        
        int last_max_r = -1;
        int max_r = -1;
        int last_l = -1;
        
        for (int i = 0; i < scores.Length; ++i)
        {
            score curr = scores[i];
            if (curr.l != last_l)
            {
                last_max_r = max_r;
                last_l = curr.l;
            }
            
            if (curr.r < last_max_r)
            {
                if (curr.l == wanho.l && curr.r == wanho.r)
                    return false;
                curr.l = -1;
                curr.r = -1;
            }
            max_r = Math.Max(max_r, curr.r);
            
            // Console.WriteLine("{0},{1} // lmax={2}, max={3}", curr.l, curr.r, last_max_r, max_r);
        }
        
        // foreach (score s in scores) Console.WriteLine("{0},{1} {2}", s.l, s.r, s.pass);
        return true;
    }
    public int get_wanho_grade(score[] scores, score wanho)
    {
        Array.Sort(scores, (s1, s2) => s1.sum() > s2.sum() ? -1 : 1);
        
        int grade = 1;
        for (int i = 0; i < scores.Length; ++i)
        {
            //Console.WriteLine("{0},{1}", scores[i].l, scores[i].r);
            if (scores[i].sum() == wanho.sum())
                return grade;
            ++grade;
        }
        return -1;
    }
    public int solution(int[,] scoreArray)
    {
        int len = scoreArray.GetLength(0);
        score[] scores = new score[len];
        for (int i = 0; i < len; ++i)
            scores[i] = new score(scoreArray[i,0], scoreArray[i,1]);
        score wanho = new score(scores[0].l, scores[0].r);

        bool wanho_pass = check_pass(scores, wanho);
        return wanho_pass ? get_wanho_grade(scores, wanho) : -1;
    }
}