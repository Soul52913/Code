# SP HW_1 
>By 范秉逸 B10902117
## 1.
### Directory
#### We need :<br>
- 1 i-node and 1 disk block to store directory "/"
- 1 i-node and 1 disk block to store directory "home/"
- 1 i-node and 1 disk block to store directory "user/"
- 1 i-node to store file "alice.txt"<br>
### "alice.txt"
#### In an i-node :
12 direct pointers can point to 12 disk blocks which can store
$$ 12 * 4096 = 49152 bytes $$
1 singly-indirect pointer can point to a disk block and a block pointer is 4 bytes long. In this disk block, we can store :
$$ 4096 / 4 = 1024 pointers $$
And 1024 pointers can store :
$$ 1024 * 4096 = 4194304 bytes $$
1 doubly-indirect pointer can point to a disk block a block pointer is 4 bytes long. In this disk block, we can store total singly-indirect pointer:
$$ 4096 / 4 = 1024 $$
And 1024 singly-indirect pointer can store :
$$ 1024 * 4194304 = 4294967296 bytes $$
Because $4294967296 + 4194304 + 49152 = 4299210752 > 5242880$ so we can use only a i-node to point to "alice.txt"<br>
$$5242880- 49152 = 5193728$$
#### 12 direct pointers need :
- 12 disk blocks to store data
$$5193728 - 4194304 = 999424$$
#### 1 singly-indirect pointer need :
- 1 disk blocks for pointers
- 1024 disk blocks to store data
#### Because $999424 < 4194304$, we only need :
- 1 disk blocks for first layer pointers
- 1 disk blocks for second layer pointers
$$999424 / 4096 = 244$$
- 244 disk blocks to store data
### Total :
We need:<br>
$$ 1 + 1 + 1 + 1 = 4 $$
i-nodes, and<br>
$$ 1 + 1 + 1 + 12 + 1 + 1024 + 1 + 1 + 244 = 1286 $$
disk blocks
### Answer: 4 i-nodes, and 1286 disk blocks
## 2.
### (a)
The advantage of creating a link in InBox over copying a file to InBox is Alice can easily change the permission of the file and manage the file. If copy a file to InBox, Alice need to "cd" to Bob's directory to change permission which is troublesome.
### (b)
A hard link is better than a symbolic link.<br>
- If we use hard link, we will directly link to the i-node of the target file. If another file, which also use a hard link to link to the same target file, is deleted, it won't affect our hard link since we directly link to the i-node of the target file. Also, it won't use any additional i-node and disk block.<br>
- If we use symbolic link, it will use additional i-nodes and disk blocks. Futhermore, if anything in the route go wrong, like being deleted, we can't access the target data. 
### (c)
- Directory InBox: <br>"-wx"
- Directory OutBox (if hard links are adopted):<br>"--x"
- Directory OutBox (if symbolic links are adopted):<br>"---"
### (d)
#### Bob can remove the file from his InBox directory.<br>
Although Bob doesn't have the write permission to the file, Bob have the write permission of the directory which contains the file. Thus, Bob can easily remove the file from his InBox directory.