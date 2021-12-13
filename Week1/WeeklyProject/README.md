# Week 1 Project: Admin Bank CLI

## How to build the project
```
git clone https://github.com/calvindo95/smoothstack_cpp

cd smoothstack_cpp/Week1/WeeklyProject

mkdir build && cd build

cmake ..

make
```

## Usage
You can now run the program binary in the build/src folder.
```
cd ../src

./main
```
You can also run the test suite in build/test:
```
cd ../test

./tests
```

## TODO:
1. Input validation

2. Make search by account name case insensitive (it is currently cases sensitive, making searching for names such as McDonald difficult)

3. Input validation in newAccount() function (such as minimum character length, etc)

4. password encryption / not plain text