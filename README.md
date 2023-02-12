
# What is this?
```
+++++++++++++[>+++++<-]>
+.
++++++++++++++++.  
-----------------.
++++++++.
+++++.       
--------.
+++++++++++++++.
------------------.
++++++++.

```

**An interpreter of Brainf*ck with C lang**


# A short description of Brainf*ck

[Wikipedia](https://en.wikipedia.org/wiki/Brainfuck)

Brainf*ck is one of the esoteric programming languages.

The processor of the Brainf*ck consists of the following elements: 
* a Brainf*ck program  (in this application this is called "source")
* a pointer pointing to a certain character in the program, which is generally called "instruction pointer" 
* an array of bytes  (in this application this array is called "field array")
* a pointer pointing to any element of the aforementioned array (an array of bytes) , which is generally called "data pointer" (in this application this is simply called "index")
* input/output


And the Brainf*ck has following eight commands:

| command | meaning |
| :-: | :-- |
| > | Increment the data pointer. |
| < | Decrement the data pointer. |
| + | Increment the byte which the the data pointer points to. |
| - | Decrement the byte which the the data pointer points to. |
| . | Output the byte which the the data pointer points to. |
| , | Input the byte into element of array which the the data pointer points to. |
| [ | If the byte which the data pointer points to is zero, the instruction pointer jumps to just after the matching `]` command. |
| ] | The data pointer jumps to the matching `[` command. |

## The system matching `]` to `[` in this application

Describing how the processor jumps from the `]` to the matching `[` in this application.
```
+++ [ >+++++<- ] >+

    ↑          |
    +-----?----+
```

1. This application's processor has a stack named "bracket stack".
1. When the instruction pointer finds `[`, push the value of the instruction pointer (the position of the `[` on the source) to the stack.  
1. When the instruction pointer finds `]`, the instruction pointer jumps to the position of the top value of the stack, and pop the value.





# Compile

Please compile `brainfuck.c` simply. 


# How To Use

1. Create the source code for Brainf*ck.

1. Run this application.

1. Enter the path to the Brainf*ck source code.
  ```
   file name > brainfuck_sumple_bf.txt
  ```

# What is "debug mode"?

```
debug mode ? (Y/n) > Y

...

source   20th: <
input/output :
index:    0 / value:   11
---
bracket stack:  13
top 10 of field array:  11 15 0 0 0 0 0 0 0 0 0
action count: 41
---

```

The "debug mode" has following function:

* Show the position now on the source code.
  * e.g.  `source    7th: +`

* Show the position and the value where the data pointer points.
  * e.g.  `index:    0 / value:    8`

* Show the status of the "bracket stack".
  * e.g.  `bracket stack:  27 42`
  
* Show the top 10 elements of the "field array".
  * e.g.  `top 10 of field array:  6 0 2 1 0 0 0 0 0 0 0`
 
* Shows how many the instruction pointer has moved.
  * e.g.  `action count: 41`
  

# Tips!

* Only the eight commands are interpreted.
  * The other charactors are ignored.
* And Comment Out is available.
  * Characters from `#` to `\n` are not readed in the first place.
  
# Author

**EaGitro (Twitter: [@EaGitro](https://twitter.com/EaGitro))** 





