# LAB 1 and 2 Computer science

**Question 1:**
  * STDOUT_FILENO: standard output
  * STDIN_FILENO: standard input
  * The use of write(fd,buffer,nb_of_bytes);
**Question 2:**
  * read(fd,buffer,nb_of_bytes_read);
  * execlp(command_file,command_file,NULL) for simple command and not complex. System call that execute the file. Terminate the current process so it was mandatory to use a fork() to create a child process
  * fork(): return 0 for the child process, and the child PID for the parent process
**Question 3:**
  * strcmp(string1,string2): Compare two strings. **Return 0** if both strings are equals
  * For **<ctrl+d>** signal the length of the input we read is equal to zero
**Question 4:**
  * for the return code we used these functions to get some information about the current state of the child process.
  * *WIFEXITED(status)* *WEXITSTATUS(status)* *WIFSIGNALED(status)*
**Question 5:**
  * For the time we used **clock_gettime(CLOCK_MONOTONIC,struct timespec pointer)**. Apparently the CLOCK_MONOTONIC is better than CLOCK_REALTIME to get the execution time of the process.
  * struct timespec has two attributes:
   * tv_spec (the time in second) and tv_nsec (the time in nanosecond)
**Question 6:**
  * For this question we used execv(path,[arguments]) because we didn't know about the existence of execvp.
  * To get the path of the file, we used the **which file** command. To get the return value of this system call we used a pipe **pipe(int[2] fd)**
  * Next time we'll look more deeply in the documentation. But we learned alot by using **execv** !
**Question 7**
