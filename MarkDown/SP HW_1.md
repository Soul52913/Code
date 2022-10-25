# SP HW_1 
>By 范秉逸 B10902117
## 1.
### (a)
./a.out < infile 2>&1 > outfile means that we<br>
- set “infile” to “standard output”
- redirect “standard error” to “standard output”
- set “standard output” to “infile.”
### (b)
Code
```
dup2(fd1, 1);
dup2(2, 1);
close(2);
dup2(1, fd2);
```
## 2.
### (a)
*write_to_fn()* function should be an atomic operation because<br>
if another funtion writes **A_txt** before *write_to_fd()* writes **B_txt** to the file, * it will append the **B_txt** written by *write_to_fd()* to the **A_txt** written by *write_to_fd() because they use the same offset in the same open file.<br>
### (a)
*write_to_fn()* function should be an atomic operation because<br>
if another funtion writes **A_txt** before *write_to_fd()* writes **B_txt** to the file, the **A_txt** written by another funtion may be displaced by the **B_txt** written by *write_to_fd()*.<br>
Although *write_to_fd()* create a new open file and a new open file fescriptor, the offset in the new open file may be same as the offset in another open file. Thus, the **A_txt** written by another funtion will be displaced by the **B_txt** written by *write_to_fd()*.