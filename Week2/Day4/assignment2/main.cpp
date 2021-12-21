#include <iostream>
#include <cassert>
#include <vector>

struct Student {
    std::string studentId; // studentId is unique
    int score; // between [1..100]

    Student(std::string id, int s): 
        studentId(id), score(s){};

    Student(){};
};

class MergeSort {
    public:
        void sort(std::vector<Student> &students){  // don't use recursion directly here!
            mergeSort(students, 0, students.size()-1);
        }

    protected:
        bool comparator(Student x, Student y){ // returns true if score of x is less than score of y
            return x.score < y.score;
        }

        void merge(std::vector<Student> &students, int left, int middle, int right){
            // gets size of l and r subarrays
            int l_size = middle - left + 1;
            int r_size = right - middle;

            // merge left and right subarrays
            Student *l_arr = new Student[l_size];
            for(int i = 0; i < l_size; i++){
                l_arr[i] = students.at(i + left);
            }
            Student *r_arr = new Student[r_size];
            for(int j = 0; j < r_size; j++){
                r_arr[j] = students.at(j + middle + 1);
            }

            int l = 0, r = 0;
            int k = left; 

            // merge the subarrays to real array
            while(l < l_size && r < r_size){
                if(comparator(l_arr[l], r_arr[r])){
                    students.at(k) = l_arr[l];
                    l++;
                }
                else{
                    students.at(k) = r_arr[r];
                    r++;
                }
                k++;
            }

            while(l < l_size){
                students.at(k) = l_arr[l];
                l++;
                k++;
            }

            while(r < r_size){
                students.at(k) = r_arr[r];
                r++;
                k++;
            }
        }

        void mergeSort(std::vector<Student> &students, int left, int right){
            int middle = left + (right - left) / 2;

            if(left < right){
                mergeSort(students, left, middle); // sort left side of array
                mergeSort(students, middle + 1, right); // sort right side of array
                merge(students, left, middle, right); // merge the array
            }
        }
};

int main(){
    std::string names[10] = {"Gary", "Barry", "Jerry", "Larry", "Mary", "Harry", "Terry", "Carrie", "Cherry", "Perry"};
    int score[10] = {100, 10, 90, 20, 80, 30, 70, 40, 60, 50};

    // create student vector
    std::vector<Student> students;
    for(int i = 0; i < 10; i++){
        students.push_back(Student(names[i], score[i]));
    }

    // print out unsorted vector
    std::cout << std::endl << "Unsorted names and grades" << std::endl;
    for(auto &student : students){
        std::cout << "Name: " << student.studentId << " Score: " << student.score << std::endl;
    }

    MergeSort mergesort;
    mergesort.sort(students);

    // print sorted vector
    std::cout << std::endl << "Sorted names and grades" << std::endl;
    for(auto &student : students){
        std::cout << "Name: " << student.studentId << " Score: " << student.score << std::endl;
    }

    // tests
    Student *s1, *s2;
    s1 = &students.at(0);

    for(int j = 1; j < students.size(); j++){
        s2 = &students.at(j);
        assert(s1->score < s2->score);
        s1 = s2;
    }
}