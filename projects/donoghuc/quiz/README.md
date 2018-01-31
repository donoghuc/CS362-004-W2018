# Random Testing Quiz
#### Cas Donoghue

__This is my random quiz submission__

## MAN
I wrote a makefile that allows user to see how the testing is working. I describe the workflow below. 
1.	After cloning repo, run ```make run_testme``` This will compile testme and run the simulation
2.	To see gcov results run ```make test_cov``` This will show the gcov stats for the last run of testme
3.	You can also run ```make clean``` to remove everything but the testme.c source and Makefile or you can run ```make build_testme``` to only build the source and not run the test. 
```
flip1 ~/CS362-004-W2018/projects/donoghuc/quiz 170% make run_testme
flip1 ~/CS362-004-W2018/projects/donoghuc/quiz 171% make test_cov
flip1 ~/CS362-004-W2018/projects/donoghuc/quiz 172% make clean
```
