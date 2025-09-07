// “Given a string made of lowercase letters each followed by a (possibly multi-digit) positive integer, merge counts for the same letters and print each letter with its total count in alphabetical order.”

// Explanation of what the provided code does

// It parses a string like a12b3a4.

// For each pattern <letter><number> it adds the number to a bucket for that letter.

// Finally it prints each letter with a non-zero total, e.g. for a12b3a4 it prints:

// a 16 b 3


#include<iostream>
using namespace std;

int findLen(char arr[]){
    int len =0;
    int i =0;
    while(arr[i] != '\0'){
        i++;
        len;
    }
    return len;
}
void merge(char arr[]){
    int len = findLen(arr);
    int mp[26] = {0};
    for(int i =0 ; i<len ; i++){
        char letter = arr[i];
        i++;
        int temp =0;
        while(i<len && arr[i] >='0' && arr[i] <='9'){
            temp = temp*10 + (arr[i] -'0');
            i++;
        }
        i--;
        mp[letter -'a']+= temp;
    }
    for(int i =0 ; i<26;i++){
        if(mp[i] != 0){
            char tmp = i + 'a';
            cout<<tmp <<" " <<mp[i]<<" ";
        }
    }
}
int main(){
    char s[100];
    cin>>s;
    merge(s);
    return 0;
}