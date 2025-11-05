#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <condition_variable>

using namespace std;


// void print(int& x) {
//     x = x + 10;   // modify value
//     cout << "Modified: " << x << endl;
// }

// int main() {
//     const int a = 5;

//     // Remove const using const_cast
//     print(const_cast<int&>(a));

//     return 0;
// }
// int main() {
//     const int a = 5;
//     int* p = const_cast<int*>(&a);
//     *p = 10;   // ❌ Undefined behavior
//     cout << a << " " << *p;
// }


mutex mtx;
condition_variable cv;
bool oddTurn = true;   // Start with odd thread

void printOdd(const vector<int>& odds) {
    for (int num : odds) {
        unique_lock<mutex> lock(mtx);
        cv.wait(lock, [] { return oddTurn; }); // wait for odd's turn
        cout << num << " ";
        oddTurn = false;    // now even's turn
        cv.notify_all();
    }
}

void printEven(const vector<int>& evens) {
    for (int num : evens) {
        unique_lock<mutex> lock(mtx);
        cv.wait(lock, [] { return !oddTurn; }); // wait for even's turn
        cout << num << " ";
        oddTurn = true;     // now odd's turn
        cv.notify_all();
    }
}

int main() {
    vector<int> odds  = {1, 3, 5, 7, 9};
    vector<int> evens = {2, 4, 6, 8, 10};

    thread t1(printOdd, odds);
    thread t2(printEven, evens);

    t1.join();
    t2.join();

    cout << endl;
    return 0;
}





// mutex mtx;
// condition_variable cv;
// bool oddTurn = true;   // Start with odd thread
// mutex mtx; — a mutual-exclusion lock. It protects shared state (here oddTurn and coordinated use of cout) so only one thread manipulates/reads them at a time.

// condition_variable cv; — a synchronization primitive that lets threads wait until some condition becomes true. Threads wait on the cv, and other threads notify it to wake them.

// bool oddTurn = true; — shared state that determines whose turn it is. true means it’s the odd thread’s turn; both threads read/write this while holding mtx.

// cpp
// Copy code
// void printOdd(const vector<int>& odds) {
//     for (int num : odds) {
//         unique_lock<mutex> lock(mtx);
//         cv.wait(lock, [] { return oddTurn; }); // wait for odd's turn
//         cout << num << " ";
//         oddTurn = false;    // now even's turn
//         cv.notify_all();
//     }
// }
// void printOdd(const vector<int>& odds) — function run by the odd thread; it receives a read-only reference to the list of odd numbers to print.

// for (int num : odds) { — iterate through each number the odd thread should print.

// unique_lock<mutex> lock(mtx); — acquire the mutex mtx. unique_lock is a RAII lock object: it locks here and will automatically unlock when it goes out of scope. unique_lock (unlike lock_guard) can be unlocked and re-locked and is required by condition_variable::wait.

// cv.wait(lock, [] { return oddTurn; }); — wait until it’s the odd thread’s turn:

// Conceptually this does two things atomically: it releases the mutex and blocks the thread. When woken (by notify_*), it re-acquires the mutex and re-checks the predicate.

// The lambda [] { return oddTurn; } is the predicate. wait will only return when the predicate is true. This handles spurious wakeups and races safely.

// Using wait(lock, predicate) means the thread won’t proceed until oddTurn is true and the mutex is held again.

// cout << num << " "; — print the number while still holding the lock. Holding the lock prevents interleaving of cout from other threads and keeps the output consistent and ordered.

// oddTurn = false; — flip the shared flag to indicate it’s now the even thread’s turn.

// cv.notify_all(); — wake up all threads waiting on cv (here the even thread). notify_all causes the waiting thread(s) to re-check the predicate; the one whose predicate is true will proceed. notify_one could be used too; notify_all is simple and safe when only a small number of waiters exist.

// cpp
// Copy code
// void printEven(const vector<int>& evens) {
//     for (int num : evens) {
//         unique_lock<mutex> lock(mtx);
//         cv.wait(lock, [] { return !oddTurn; }); // wait for even's turn
//         cout << num << " ";
//         oddTurn = true;     // now odd's turn
//         cv.notify_all();
//     }
// }
// printEven is the mirror of printOdd: it waits until !oddTurn (even's turn), prints, flips oddTurn back to true, and notifies.

// Same notes apply: using unique_lock, using a predicate with wait prevents race conditions and spurious-wakeup bugs, printing while holding the mutex keeps output atomic.

// cpp
// Copy code
// int main() {
//     vector<int> odds  = {1, 3, 5, 7, 9};
//     vector<int> evens = {2, 4, 6, 8, 10};

//     thread t1(printOdd, odds);
//     thread t2(printEven, evens);

//     t1.join();
//     t2.join();

//     cout << endl;
//     return 0;
// }
// vector<int> odds … evens … — prepare the data to be printed.

// thread t1(printOdd, odds); — create a new thread t1 that runs printOdd(odds). Note: the odds vector is copied into the new thread’s context because the thread function takes a const vector<int>& parameter but std::thread will decay and copy arguments by default unless you use std::ref. In this case copying is fine.

// thread t2(printEven, evens); — create the even thread similarly.

// t1.join(); t2.join(); — wait (block) until the threads finish. join() ensures the threads complete before main continues and the program exits.

// cout << endl; — print newline after the paired output.

// return 0; — exit program successfully.

// Additional conceptual notes / pitfalls
// Predicate in wait is essential. Always use the predicate form (wait(lock, predicate)) or check the predicate in a loop; otherwise spurious wakeups or race conditions can let a thread continue prematurely.

// Why hold the mutex while printing? It prevents the other thread from printing at the same time and avoids interleaved cout output. It also synchronizes changes to oddTurn.

// notify_all vs notify_one: here either would work because there are only two threads. notify_one could be slightly more efficient (wake one waiter) but notify_all is safe and clear.

// Copying vectors into threads: std::thread constructor copies the arguments by default. If you intended to pass by reference, use std::ref(odds). Copying is fine when you want independent copies.

// Race conditions if initial state mismatched: If oddTurn had been initialized incorrectly relative to which thread starts waiting first, the first thread would immediately block until the other flips it. Using the predicate avoids deadlocks so long as the logic and sequences are consistent.

// Different sizes: If odds and evens have different lengths, one thread will finish earlier and stop notifying; the other thread must handle the remaining prints properly — with this code the shorter thread will exit and the other waits on the predicate; since the shorter thread no longer flips oddTurn, the remaining elements may never print. To handle uneven sizes you need slight adjustments (for example, ensure the longer side’s loop doesn’t wait forever once the other thread is done).

