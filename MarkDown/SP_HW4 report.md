# SP_HW4 report
>By 范秉逸 B10902117

![Pic](pic.png)
I process them on linux11.csie.mtu.edu.tw <br>
By the picture, we find out that with more layer, the time it consumed will take shorter. From layer 1 to layer 2, the time they consumed decline significantly from 17 to 3 (t) and 16 to 4 (p). But it won't decline more significantly if the layer is bigger. Instead, it will gradually approach to a certain value. For tserver, it will decline to about 0.6 sec, and for pserver, it will decline to about 2 sec. At smaller layer, pserver run almost same as tserver. But when layer is bigger, tserver is faster tha pserver. <br>
The reason for bigger layer take shorter time is multithreads and multiprocesses will run the progress at the same time, which cause the time it takes get shorter.