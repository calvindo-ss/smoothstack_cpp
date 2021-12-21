#include <iostream>
#include <cassert>

class Grade {
    static char grades[4];
    public:
        static char grade(const int&& score){

            int grade_rounded = (score / 10) * 10; // round down to multiple of 10

            int grade_index = (grade_rounded / 10) - 1; // convert multiple of 10 to index

            return grades[grade_index];
        }
};

char Grade::grades[4] = {'D', 'C', 'B', 'A'};

int main(void) {
    int n[] = {10, 20, 30, 40};

    for(int i = 0; i < sizeof(n)/4; i++){
        std::cout << "Score = " << n[i] << " Grade " << Grade::grade((const int) n[i]) << std::endl;
    }

    assert(Grade::grade((const int) 10) == 'D');
    assert(Grade::grade((const int) 20) == 'C');
    assert(Grade::grade((const int) 30) == 'B');
    assert(Grade::grade((const int) 40) == 'A');

    return 0;
}