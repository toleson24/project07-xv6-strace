[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-24ddc0f5d75046c5622901739e7c5dd533143b0c8e959d652212380cedb1ea36.svg)](https://classroom.github.com/a/M039ZnOv)
# Project07 xv6 strace

## About

## Requirements

### Overview

In this project you will get experience using the xv6 systems calls for working with processes in Unix and with making modifcations to the kernel to support a command called `strace`.

The `strace` program is standard on many versions of Unix, including Linux that allows you to see all the system calls that a program invokes during execution. This can be helpful for debugging certain types of problems. It also helps you understand how system calls are used. You can learn more about it here:

https://opensource.com/article/19/10/strace

We are going to modify xv6 to support a simple version of the `strace` command. You will make modifications to the kernel, add an `strace` system call, and write a new user level program called `strace` that will run a program with tracing on.

### Reading

You should read Chapters 1, 2, and 4 from the xv6 book:

### Adding the strace() system call

To support strace you will need to add a new field to the struct proc in proc.c. You can call this field int strace. A value of 0 means tracing is off and a value of 1 means tracing is on. You will add a system call, strace(int value), that will set the strace field appropriately. Only values of 0 and 1 should be accepted.

### Modifying the system calls

To support strace you will need to modify each of the system calls to print the tracing info if the strace value for the currently running process is 1. Note that in the kernel, you can get access to the currently running process struct using the myproc() function, you can combine this with field access, e.g., myproc()->strace. For buffers we will just print addr to make the autograder work. In some cases adding the trace printing is easy, in other cases you have to rework the code a bit in order to get access to the arguments before checking for errors, here is an example:

```c
uint64
sys_close(void)
{
  int fd;
  struct file *f;
  int rv;
  rv = argfd(0, &fd, &f);
  if (myproc()->trace)
    printf("[%d] sys_close(%d)\n", myproc()->pid, fd);
  if(rv < 0)
    return -1;
  myproc()->ofile[fd] = 0;
  fileclose(f);
  return 0;
} 
```

Compare this to the original code and notice the added rv variable and order of access, printing, and then error condition checking.

### User Programs

See `xv6-riscv/user/sctrace.c` for the `strace` user program. An example output for `strace echo` with a string follows:

```bash
$ strace echo a b c
[13] sys_write(1, addr, 1)
a[13] sys_write(1, addr, 1)
 [13] sys_write(1, addr, 1)
b[13] sys_write(1, addr, 1)
 [13] sys_write(1, addr, 1)
c[13] sys_write(1, addr, 1)

[13] sys_exit(0)
$
```

See `xv6-riscv/user/sctest.c` for the comprehensive system call-testing user program. See `project07-sample-output.txt` for the expected output. See `project07-output.txt` for the output produced by this project.

### Deliverables

## Links

## Testing

### Manual



> Note: There are no Autograder tests for this project.
