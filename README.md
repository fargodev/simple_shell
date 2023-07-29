# Simple_shell Project
<img src="https://www.tecmint.com/wp-content/uploads/2020/11/if-else-statement.png"></img><br>
## MABERT SHELL
MABERT SHELL - as the name implies meaning MAbo and herBERT shell the two collaborators who worked together to create this amazing project.
## Introduction
Simple Shell is a simple project version or form of Linux shell command line. This project
tasked us to using all the knowledge if gathered so far in the past three month of ALX program studying C-Language. This is a partnered project to build our own version of Unix simple shell or command line which works exactly the same as an OS command line in it simple form.
<br>
The advantage of this project is that it helps to test our collaborative spirit and standard work ethics. It also exposes us to real application of skills gathered with the focus of honing our skillset the more.

## Helpful Resources
[Writing Unix Shell - Part I](https://indradhanush.github.io/blog/writing-a-unix-shell-part-1/)<br>
[Writing Unix Shell - Part II](https://indradhanush.github.io/blog/writing-a-unix-shell-part-2/)<br>
[Writing Unix Shell - Part III](https://indradhanush.github.io/blog/writing-a-unix-shell-part-3/)<br>
[Dev Genius - Build a Linux Shell](https://blog.devgenius.io/lets-build-a-linux-shell-part-i-954c95911501)

## Testing
Compile your shell this way:
```
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh
````
Your shell should work like this in interactive mode:
```
$ ./hsh
($) /bin/ls
hsh main.c shell.c
($)
($) exit
$
```
But also in non-interactive mode:
```
$ echo "/bin/ls" | ./hsh
hsh main.c shell.c test_ls_2
$
$ cat test_ls_2
/bin/ls
/bin/ls
$
$ cat test_ls_2 | ./hsh
hsh main.c shell.c test_ls_2
hsh main.c shell.c test_ls_2
$
```

## Collaborators
[Wale Herbert](https://github.com/trucedev) <br>
[Mabo Gwala](https://github.com/Pontsho04)
