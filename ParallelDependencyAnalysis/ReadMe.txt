ReadMe.txt

0x00 Descriptions:

This Project is ParallelDependencyAnalysis package, and it contains the following packages:

1. DependencyAnalysis (not parallel)
2. FileMgr
3. ParallelDependencyAnalysis (paralele)
4. ParallelDependencyExecutive   (Parallel)
5. Parser
6. ScopeStack(fawcett's original code)
7. SemiExp(fawcett's original code)
8. Task
9. ThreadPool
10. BlockingQueue (fawcett's original code)
11. Tokenizer (fawcett's original code)
12. TypeAnalysis
13. Utilities (fawcett's original code)

So, here, each package contains one testsub, and the ParallelDependencyExecutive package offer
the running exe file for this project. And it been wraped into Debug file in root path.



0x01 Build and Running
1. Run the build.bat file located in the root directory and then you can build the whole project
2. Run the execute.bat file located in the root directory and then you can run the project.

Note that, if you can't run the program or the cmd window exit, pleas check the file directory doesn't
contain special characters[space, '/' '@''$']. You can reset the root file directory locatio and rerun
the bat file, then you will get the results.


0x02 Test Files

The test files been located in the TestFile folder, and in this file contains three test files, in the
nihaohuai.h file, it contains some classes and functiosn, in the nimei.h file contains some class definitions
which inherit from nihaohuai.h, and have some self defined funstions. In nimei.cpp file, it will call the functions
defined both in nimei.h and nihaohuai.h 

0x03 Check for Multithreads

In order to check that our program indeed running in the threadpool, you can open the build project in Visual Stdio
and then you set function breakpoint from Debug tab, and run the code in the Degub mmodel. Once the code been intercepted 
by the main function's breakpoint, you can click Debug->Windows->Parallel Stacks. And you will see all the running threads.

