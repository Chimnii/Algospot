using System;
using System.Collections.Generic;

public class Solution
{
    public class homework
    {
        public string name;
        public int start;
        public int playtime;
        public homework(string _name, string _start, string _playtime)
        {
            name = _name;
            start = Convert.ToInt32(_start.Substring(0,2))*60 + Convert.ToInt32(_start.Substring(3,2));
            playtime = Convert.ToInt32(_playtime);
        }
    }
    
    public string[] solution(string[,] plans)
    {
        int length = plans.GetLength(0);
        string[] answer = new string[length];
        homework[] homeworks = new homework[length];
        for (int i = 0; i < length; ++i)
        {
            homeworks[i] = new homework(plans[i,0], plans[i,1], plans[i,2]);
        }
        Array.Sort(homeworks, (h1, h2) => h1.start < h2.start ? -1 : 1);
        
        
        int current_time = 0;
        int answer_index = 0;
        Stack<homework> delayed = new Stack<homework>();
        foreach (homework h in homeworks)
        {
            int remain_start = h.start - current_time;
            while (delayed.Count > 0 && remain_start > 0)
            {
                if (delayed.Peek().playtime <= remain_start)
                {
                    remain_start -= delayed.Peek().playtime;
                    answer[answer_index++] = (delayed.Pop().name);
                }
                else
                {
                    delayed.Peek().playtime -= remain_start;
                    remain_start = 0;
                }
            }
            current_time = h.start;
            delayed.Push(h);
        }
        
        while (delayed.Count > 0)
        {
            answer[answer_index++] = (delayed.Pop().name);
        }
        
        return answer;
    }
}