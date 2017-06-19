Production cpp code is a must for self-driving car engineers. Every second, we save on latency in 
algorithm reaction is worth it and often hardware do not support running higher level programming 
languages. This guide is to help python developer get onboard with cpp programming 
* Analysis of annoylib.h 
    * (include_guards) Purpose of the below construct is to avoid double import/circular dependency

        ```cpp
        #ifndef HEADERFILE_H
        #define HEADERFILE_H
        ..
        #endif
        ```
    *  `__MINGW32__` compiler Macros.
    * `using namespace std;` is equivalent to `from std import *` in python 
    * What is a template ? are the different from functions ?
    * what does the keyword inline mean ? for short function, compiler can insert the function during 
    execution time. 
    * What is Struct ? Same as class except members are public by default. 
* [CPP for python 1](http://users.aims.ac.za/~nneoma/cpp4py/cpptut.html)
* [Managing Large Prjects in Cpp: chapter 12](http://cs.slu.edu/~goldwamh/publications/python2cpp.pdf)
    * importing with "" is used for local files, while angle_bracket is used for system libraries.
    * Each module has a header file and corresponding .cpp file for implementation.
    * `g++` command by default does both : compiling and as well as dependency linking. but with option 
    `-c` for compiling `-o` for linking, we could separate them for re-usability.
    * Managing Templated class 
* Good Code to read 
    * REDIS 
    

    