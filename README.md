# lkm-examples
Set of Linux loadable kernel modules as simple examples, this was used to support for a Kernel security article published in an old spanish magazine which no longer exists (yeah... no celebrities there).

The code is meant to be simple and explain the basics on creating Linux Loadable Kernel Modules and how a backdoor could be implanted, but could be used for different purposes.

The LKMs in this repo should work in old Linux kernel versions: 2.2/2.4 and some 2.6.


## description

|  listing |   notes|
|---|---|
|  1 | C basics: pointer to a function   |
|  2 | LKM structure, hello world |
|  3 | LKM chmod hook  |
|  4 | LKM mv hook  |
|  5 | LKM suid hook |
|  5b| Version 2 of listing 5   |
|  7 | LKM for 2.6.9  |
|  8 | Search for syscall table  |
|  9 | Search for syscall table, better example  |
| bd | Backdoor that hides as another LKM |

