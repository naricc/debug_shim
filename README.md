# debug_shim


## Description

The purpose of this debug_shim is to make it easier to debug programs at the begining of their execution. 

Sometimes you run into a situation where program A starts program B, and you would like to attach a debugger to program B right at the begining of execution, but it is difficult to reproduce the exact execution environment program A produced.

In this case, you can replace the binary of program B with debug_shim. debug_shim with wait in a busy loop, allowing you to attach a debugger. Then it will proceed to when you send it a SIGUSR1 signal, and execv whatever is at /debug_shim_link (which you should point at the program you actually want to debug)


## Usage

Copy the <target_program> you want to debug to a new location, `<program_debug>`

Overwrite <target_program> with `debug_shim`

Create a symlink in the root directory to the `<program_debug>`

```
ln -s <full path to program_deubg> /debug_shim_link
```

Now do whatever is needed to run the program you wish to debug (ie, spawn some other process that eventually runs it) and wait.

Once the the target program is running, find its process id:

```
ps -aux <target_program>
```

And attach gdb:

```
gdb <pid>
```

Set whatever break points you wish.

Now send to the <target_program> (which is really debug_shim in disguise):

```
killall -SIGUSR1 <target_program>
```

In gdb, run the program:

```
(gdb) run
```

`debug_shim` will proceed and excute `<program-debug>`