#include <iostream>
using namespace std;

int main()
{

    // intput the k
    int k;
    cin >> k;
    string s;
    // take two get line becuase 1st is consemed by enter
    getline(cin, s);
    getline(cin, s);
    int sum = 0;
    int level = -1;
    int n = s.size();
    for (int i = 0; i < n; i++)
    {
        // if we get '(' increase the level
        if (s[i] == '(')
        { ///
            level++;
            // take second pointer from i+1
            int j = i + 1;
            // remove empty space if it havae
            while (j < n && isspace((char)s[j]))
                j++;
            // j is closing bracket
            if (s[j] == ')')
                continue;
            // check if first element is. sign or not
            if (j < n && ((s[j] == '-') || isdigit((char)s[j])))
            {
                int sign = 1;
                if (s[j] == '-')
                {
                    sign = -1;
                    j++;
                }
                int val = 0;
                bool hasDigit = false;
                // get the number
                while (j < n && isdigit((char)s[j]))
                {
                    hasDigit = true;
                    val = val * 10 + (s[j] - '0');
                    j++;
                }
                // if we got an digit
                if (hasDigit)
                {
                    val *= sign;
                    // check wheter this element. belong to kth level
                    if (level == k)
                    {
                        sum += val;
                    }
                }
            }
        }
        else if (s[i] == ')')
        {
            level--;
        }
    }

    cout << sum << endl;
    return 0;
}