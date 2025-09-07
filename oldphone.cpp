// // /*

// // You are given an old touch smartphone numbers having dial pad and calculator app.
// // Aim: The goal is to type a number on dialpad.

// // But as phone is old, some of the numbers and some operations can't be touched.
// // For eg. 2,3,5,9 keys are not responding , i.e you cannot use them
// // But you can always make a number using other numbers and operations in Calculator. There could be multiple ways of making a number

// // Calculator have 1-9 and +,-,*,/,= as operations. Once you have made the number in Calculator you can copy the number and use it.

// // You have to find minimum number to touches required to obtain a number.

// // #Input:#
// // There will be multiple Test cases .Each test case will consist of 4 lines
// // 1) First line will consist of N,M,O
// //     N: no of keys working in Dialpad (out of 0,1,2,3,4,5,6,7,8,9)
// //     M:types of operations supported (+,-,*,/)
// //     O: Max no of touches allowed
// // 2) second line of input contains the digits that are working e.g 0,2,3,4,6.
// // 3) Third line contains the valued describing operations, 1(+),2(-),3(*),4(/)
// // 4) fourth line contains the number that we want to make .

// // #Output:#
// // Output contains 1 line printing the number of touches required to make the number

// // #Sample Test Case:#
// // 5
// // 5 3 5
// // 1 2 4 6 0
// // 1 2 3
// // 5
// // 6 4 5
// // 1 2 4 6 9 8
// // 1 2 3 4
// // 91
// // 6 2 4
// // 0 1 3 5 7 9
// // 1 2 4
// // 28
// // 5 2 10
// // 1 2 6 7 8
// // 2 3
// // 981
// // 6 3 5
// // 1 4 6 7 8 9
// // 1 2 3
// // 18

// // #Output:#
// // 4
// // 2
// // 5
// // 9
// // 2

// // If you have to type 18-> 2 operations. (Each touch is considered an operation),br> If you have to type 5 -> '1+4=' that requires 4 operations. There could be other ways to make '5'.
// // */
// #include <iostream>
// using namespace std;
// const unsigned long long maxi =100000000000;
// struct node
// {
//     int data;
//     int touch;
//     bool prev;
// };

// node q[maxi];
// int vis[10000];
// int digit[10];
// int op[4];

// int front, back, n, o, lim, num, len;

// void init()
// {
//     front = 0;
//     back=-1;
//     len = 0;
//     return;
// }

// void push(int data, int touch, bool x)
// {
   
    
//     back = (1+back)%maxi;
//     q[back].data = data;
//     q[back].touch = touch;
//     q[back].prev = x;
//     len++;
//     return;
// }

// node pop()
// {
//     node temp = q[front];
//       front = (front + 1) % maxi;
//     len--;
//     return temp;
// }

// bool isempty()
// {
//     return len == 0;
// }

// int solve()
// {
//     int ans=-1;
//     while (!isempty())
//     {
//         node temp = pop();
//         int data = temp.data;
//         int tt = temp.touch;

//         if (tt > lim)
//         {
//             continue;
//         }

//         if (data == num)
//         {
//             ans=tt  + temp.prev;
//             break;
//         }

//         if (vis[data]==0)
//         {
//             for (int i = 0; i < n; i++)
//             {
//                 // if(10 * data + digit[i] <)
//                 push(10 * data + digit[i], tt + 1,0);
//             }

//             for (int i = 0; i < o; i++)
//             {
//                 for (int j = 0; j < 10000; j++)
//                 {
//                     if (vis[j])
//                     {

//                         if (op[i] == 1)
//                         {
//                             //   cout << data + j << endl;
//                             push(data + j, tt + 2,1);
//                         }
//                         else if (op[i] == 2 && data - j >= 0)
//                         {
//                             //   cout << data - j << endl;
//                             push(data - j, tt + 2,1);
//                         }
//                         else if (op[i] == 3 && data*j < 1000)
//                         {
//                             //   cout << data * j << endl;
//                             push(data * j, tt + 2,1);
//                         }
//                         else if (op[i] == 4 && j != 0)
//                         {
//                             //   cout << data / j << endl;
//                             push(data / j, tt + 2,1);
//                         }
//                     }
//                 }
//             }
//             vis[data] = 1;
//         }
//     }
//     return ans;
// }

// int main()
// {
//     int t;
//     cin >> t;
//     while (t--)
//     {
//         cin >> n >> o >> lim;
//         int x;
//         init();
//         for(int i =0 ; i<10000;i++){
//             vis[i] =0;
//         }
//         for (int i = 0; i < n; i++)
//         {
//             cin >> x;
//             digit[i] = x;
//             push(x, 1,0);
//         }
//         for (int i = 0; i < o; i++)
//         {
//             cin >> op[i];
            
//         }
//         cin >> num;
//         cout << solve() << endl;
        
//     }

//     return 0;
// }


