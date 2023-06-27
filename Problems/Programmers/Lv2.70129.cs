using System;
using System.Linq;

public class Solution
{
    public string int_to_binary(int one)
    {
        string s = "";
        while(one > 0)
        {
            s += (one % 2 == 0 ? 0 : 1);
            one /= 2;
        }
        return new string(s.Reverse().ToArray());
    }
    public int[] solution(string s)
    {
        int converted = 0, removed = 0;
        while (s.Length > 1)
        {
            int zero = s.Count(c => c == '0');
            int one = s.Length - zero;
            
            removed += zero;
            converted += 1;
            s = int_to_binary(one);
        }
        
        return new int[] {converted, removed};
    }
}