public class Solution {
    public int LengthOfLongestSubstring(string s) {
        int maxLength = 0;
        for(int i = 0; i < s.Length; i++){
            List<char> list = new List<char>();
            for(int j = i; j < s.Length; j++){
                if(list.Contains(s[j]) == false){
                    list.Add(s[j]);
                }
                else{
                    break;
                }
            }
            if(list.Count > maxLength)
                maxLength = list.Count;
        }
        return maxLength;
    }
}