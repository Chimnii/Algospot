using System;

public class Solution
{
    public int[] solution(int[] sequence, int k)
    {
        int[] answer = {0, sequence.Length - 1};
        
        int sum = sequence[0], start = 0, final = 0;
        while(start < sequence.Length && final < sequence.Length)
        {
            if (sum > k)
            {
                sum -= sequence[start];
                ++start;
                continue;
            }
            
            if (sum == k && final - start < answer[1] - answer[0])
            {
                answer[0] = start;
                answer[1] = final;
            }
            
            if (++final < sequence.Length)
                sum += sequence[final];
        }

        return answer;
    }
}