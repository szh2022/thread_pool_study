#include "tr_pool.h"
using namespace std;
int main() {
    ThreadPool pool(4);
    for (int i = 0; i < 10; i++) {
        pool.enqueue([i]() {
            cout << "task: " << i << " is running" << endl;
            std::this_thread::sleep_for(std::chrono::seconds(1));
            cout << "task: " << i << " is done" << endl;
        });
    }
    return 0;
}