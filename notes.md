# p0
- [X] authors Prints the names and logins of the program authors. authors -l prints
only the logins and authors -n prints only the names
- [X] pid Prints the pid of the process executing the shell.
- [X] ppid Prints the pid of the shell’s parent process.
- [X] cd [dir] Changes the current working directory of the shell to dir (using the
chdir system call). When invoked without auguments it prints the

current working directory (using the getcwd system call.
- [X] date [-t|-d] Prints the current date in the format DD/MM/YYYY and the current
time in the format hh:mm:ss.
- [X] date -d Prints the current date in the format DD/MM/YYYY
- [X] date -t Prints and the current time in the format hh:mm:ss.
- [ ] historic [N|-N] Shows the historic of commands executed by this shell. In order to
do this, a list to store all the commands input to the shell must be
implemented.
– historic Prints all the comands that have been input with their
order number
– historic N Repeats command number N (from historic list)
– historic -N Prints only the lastN comands
Students are free to decide whether historic stars numbering commands
at 0 or at 1. Hypothetically, there’s a scenario where trying to repeat
a historic command could yield an infinite loop or a stack overflow
(depending on how it is coded), so students may choose to not store
calls to historic N itself in the historic list if they want so (See the
NOTES ON LIST IMPLEMENTATIONS at the end of this document)
- [ ] open [file] mode Opens a file and adds it (together with the file descriptor and the
opening mode to the list of shell open files. For the mode we’ll use:
- cr for O CREAT, 
- ap for O APPEND, 
- ex for O EXCL, 
- ro for O RDONLY,
rw for O RDWR, wo for O WRONLY and tr for O TRUNC.
Open without arguments lists the shell open files. For each file it lists its
descriptor, the file name and the opening mode. The shell will inherit
from its parent process open descriptors 0, 1 and 2 (stdin, stout, and
stderr). To get the opening mode from a descriptor (df) we can use
fcntl(fd,F GETFL).
- [ ] close [df ] Closes the df file descriptor and eliminates the corresponding item from
the list
- [ ] dup [df ] Duplicates the df file descriptor (using the dup system call, creating the
corresponding new entry on the file list
infosys Prints information on the machine running the shell (as obtained via
the uname system call/library function)
help [cmd] help displays a list of available commands. help cmd gives a brief help
on the usage of comand cmd
- [X] quit Ends the shell
- [X] exit Ends the shell
- [X] bye Ends the shell

# p1

- [X] makefile
    - makefile
    - makefile [name]
- [X] makedir
    - makedir
    - makedir [name]
- [ ] listfile
    - [X] listfile
    - [X] listfile -long
    - [ ] listfile -link
    - [ ] listfile -acc
- [X] cwd
listdir
reclist
revlist
erase
delrec