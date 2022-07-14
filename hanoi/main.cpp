#include <iostream>
#include <vector>


using namespace std;


class Hanoi {
    private:
        vector<int> first;
        vector<int> second;
        vector<int> third;

        int step;

        void printCondition() {
            cout << "---------------------------------------------------------\n\n";

            cout << "\t\t\tStep #" << step << "\n\n";

            cout << "1: ";
            for (auto &it : first) {
                cout << it;
            }
            cout << '\n';

            cout << "2: ";
            for (auto &it : second) {
                cout << it;
            }
            cout << '\n';

            cout << "3: ";
            for (auto &it : third) {
                cout << it;
            }
            cout << '\n';

            cout << "\n---------------------------------------------------------\n\n\n";
        }
    
        vector<int>& parseRod(const int number) {
            switch (number) {
                case 1:
                    return first;
                
                case 2:
                    return second;
                
                case 3:
                    return third;

                default:
                    throw "Invalid rod number";
            }
        }

        void moveRing(const int from, const int to) {
            ++step;
            parseRod(to).push_back(parseRod(from).back());
            parseRod(from).pop_back();
            printCondition();
        }

        void hanoi(const int n, const int i, const int k) {
            if (n == 1) {
                moveRing(i, k);
                return;
            }

            int tmp = 6 - i - k;
            hanoi(n - 1, i, tmp);
            moveRing(i, k);
            hanoi(n - 1, tmp, k);
        }

    public:
        explicit Hanoi(const int rings, const int from, const int to) {
            step = 0;

            for (int i = rings; i > 0; --i) {
                parseRod(from).push_back(i);
            }

            printCondition();

            hanoi(rings, from, to);
        }
};

int main() {
    Hanoi(8, 1, 2);
}
