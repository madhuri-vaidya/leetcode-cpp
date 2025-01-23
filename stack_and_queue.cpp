/* Stack and Queue Problems */

#include <vector>
#include <stack>
#include <queue>
#include <string>

using namespace std;

/* Implement a Queue Using a Stack
Implement a first in first out (FIFO) queue using only two stacks. The implemented queue should support all the functions of a normal queue (push, peek, pop, and empty).
*/
class MyQueue {
private:
    stack<int> stk_main, stk_rev;
    
    void swap_stacks(stack<int>& stk1, stack<int>& stk2) {
        while(!stk1.empty()) {
            stk2.push(stk1.top());
            stk1.pop();
        }
    }
    
public:
    MyQueue() {
    }
    
    void push(int x) {
        stk_main.push(x);
    }
    
    int pop() {
        int ans;
        
        swap_stacks(stk_main, stk_rev);
        
        ans = stk_rev.top();
        stk_rev.pop();
        
        swap_stacks(stk_rev, stk_main);
               
        return ans;
    }
    
    int peek() {
        int ans;
        
        swap_stacks(stk_main, stk_rev);
        
        ans = stk_rev.top();
        
        swap_stacks(stk_rev, stk_main);
        
        return ans;
    }
    
    bool empty() {
        return stk_main.empty();
    }
};


/* Implement Stack Using Queues
Implement a last-in-first-out (LIFO) stack using only two queues. The implemented stack should support all the functions of a normal stack (push, top, pop, and empty).
*/
class MyStack {
private:
    queue<int> q_main, q_rev;
    
    void swap_queues(queue<int>& q1, queue<int>& q2) {
        while(q1.size() != 1) {
            q2.push(q1.front());
            q1.pop();
        }
        q1.pop();
        
    }
    
public:
    MyStack() {
        
    }
    
    void push(int x) {
        q_main.push(x);
    }
    
    int pop() {
        int ans = q_main.back();
        
        while(q_main.size() != 1) {
            q_rev.push(q_main.front());
            q_main.pop();
        }
        q_main.pop();
        
        while(!q_rev.empty()) {
            q_main.push(q_rev.front());
            q_rev.pop();
        }
        
        return ans;
    }
    
    int top() {
        return q_main.back();
    }
    
    bool empty() {
        return q_main.empty();
    }
};


class Solution {
public:
    /* Valid Parentheses
    Given a string s containing just the characters '(', ')', '{', '}', '[' and ']', determine if the input string is valid.

    An input string is valid if:

    Open brackets must be closed by the same type of brackets.
    Open brackets must be closed in the correct order.
    Every close bracket has a corresponding open bracket of the same type.
    */
   bool isValid(string s) {
        vector<char> brackets;
        
        for(char c : s) {
            if((c == '(') || (c == '[') || (c == '{')) { brackets.push_back(c); }
            
            else {
                if(brackets.empty()) { return false; }
                
                else if(c == ')') {
                    if(brackets.back() == '(') { brackets.pop_back(); }
                    else { return false; }
                }
                
                else if(c == ']') {
                    if(brackets.back() == '[') { brackets.pop_back(); }
                    else { return false; }
                }
            
                else if(c == '}') {
                    if(brackets.back() == '{') { brackets.pop_back(); }
                    else { return false; }
                }
            }
        }
        
        if(brackets.empty()) { return true; }
        else { return false; }
    }


    /* Daily Temperatures
    Given an array of integers temperatures represents the daily temperatures, return an array answer such that answer[i] is the number of days you have to wait after the ith day to get a warmer temperature. If there is no future day for which this is possible, keep answer[i] == 0 instead.
    */
   vector<int> dailyTemperatures(vector<int>& temperatures) {
        vector<int> answer(temperatures.size(), 0);
        stack<int> tmp_stk;
        
        for(int i = 0; i < temperatures.size(); i++) {
            while(!tmp_stk.empty() && temperatures[i] > temperatures[tmp_stk.top()]) {
                answer[tmp_stk.top()] = i - tmp_stk.top();
                tmp_stk.pop();
            }
            tmp_stk.push(i);
        }
        
        return answer;
    }


    /* Evaluate Reverse Polish Notation
    You are given an array of strings tokens that represents an arithmetic expression in a Reverse Polish Notation.

    Evaluate the expression. Return an integer that represents the value of the expression.
    */
   int evalRPN(vector<string>& tokens) {
        stack<int> stk;
        int op1 = 0, op2 = 0;
        
        for(int i = 0; i < tokens.size(); i++) {
            if((tokens[i].size() > 1) || (tokens[i][0] - '0' >= 0)) {
                stk.push(stoi(tokens[i]));
            }
            else {
                op2 = stk.top(); stk.pop();
                op1 = stk.top(); stk.pop();
                
                switch(tokens[i][0]) {
                    case '+': stk.push(op1 + op2); break;
                    case '-': stk.push(op1 - op2); break;
                    case '*': stk.push(op1 * op2); break;
                    case '/': stk.push(op1 / op2); break;
                }
            }
        }
        
        return stk.top();
    }


    /* Decode String
    Given an encoded string, return its decoded string.

    The encoding rule is: k[encoded_string], where the encoded_string inside the square brackets is being repeated exactly k times. Note that k is guaranteed to be a positive integer.

    You may assume that the input string is always valid; there are no extra white spaces, square brackets are well-formed, etc. Furthermore, you may assume that the original data does not contain any digits and that digits are only for those repeat numbers, k. For example, there will not be input like 3a or 2[4].
    */
   string decodeString(string s) {
        stack<string> stk;
        string current_str = "";  // To accumulate the characters
        int repeat_count = 0;     // To store the repeat count (k)
        
        for (char c : s) {
            if (isdigit(c)) {
                // Build the repeat count number (could be more than one digit)
                repeat_count = repeat_count * 10 + (c - '0');
            } else if (c == '[') {
                // Push the current accumulated string and the repeat count onto the stack
                stk.push(current_str);
                stk.push(to_string(repeat_count));
                current_str = "";  // Reset current_str to start building the substring inside the brackets
                repeat_count = 0;  // Reset repeat_count for the next potential k
            } else if (c == ']') {
                // Pop the repeat count and the previous accumulated string
                int k = stoi(stk.top());  // Get repeat count
                stk.pop();
                
                string prev_str = stk.top();  // Get the previous accumulated string before the '['
                stk.pop();
                
                // Repeat the current string k times
                string decoded_str = "";
                for (int i = 0; i < k; i++) {
                    decoded_str += current_str;
                }
                
                // Combine the previous string with the repeated substring
                current_str = prev_str + decoded_str;
            } else {
                // If it's a character, accumulate it in the current string
                current_str += c;
            }
        }
        
        return current_str;
    }
};