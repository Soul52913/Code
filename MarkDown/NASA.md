# Homework #0
>By 范秉逸 B10902117
## Network Administration
### 1. True/False
1. True <br>
4G LTE的LTE是指Long Term Evolution。4G LTE是3.5G邁向4G的過度版本，但4G LTE在速度方面未符合4G所規定的速度，4G LTE速度比4G的速度還要慢。
2. True <br>
IP address是用來定位一個網域或一個主機在網際網路上的位置，而Mac address是用來定位一個網路裝置的位置，一個網路裝置(如網卡)只有一個獨一無二的Mac address。因此MAC address 和 IP address可以定位網際網路裡唯一一個網域裡的唯一一個裝置。
3. False <br>
儘管IPv4 address已逐漸枯竭，但目前的網域是IPv4和IPv6共同使用。如果所連接的網域屬於IPv4，則我們仍可以使用IPv4，並非一定要使用IPv6。
4. True <br>
當我們使用VPN時，我們會將封包傳到VPN廠商的伺服器，並經由VPN伺服器將封包傳至要抵達的IP位置。此過程中會使封包的sourse IP更換為VPN伺服器的IP位置。
5. True <br>
當我們沒有public IP時，外面的裝置是無法找到我所架設的伺服器，他們只能通過路由器間接的連到我逤架設的伺服器。
6. False <br>
DHCP server僅在分配IP位置時使用，傳送封包或資料時不需要經過DHCP server才能傳輸。
7. True <br>
因為台大課程網的網址開頭是http，所以任何用戶與伺服器之間的封包傳送都是以明文的方式進行傳輸，所以任何擷取到這個封包的人都可以很輕易地知道我們輸入的關鍵字是什麼。
8. False <br>
當沒有Router的時候，每個VLAN就是一個獨立的虛擬網域，在同一個VLAN的設備能互相傳輸資訊，但沒有Router便不能在不同的VLAN之間傳輸資料。
9. True <br>
當我們沒有IP位置時，我們可以發送DHCP discovery給DHCP位置，之後DHCP server會回傳DHCP offer給我們，然後我們再回傳DHCP request 給DHCP server，最後DHCP再回傳一個DHCP acknowledgement message告訴我們我們已被指定為這個IP位置。
10. True <br>
若我們知道該server的IP位置，我們可以透過IP位置直接連到該server，但缺少DNS、NAT、DHCP、VPN可能使我們與該server之間的封包傳輸變得不安全且不順暢。
### 2.  Short Answer
1. <br>
    (a) <br>
    Gateway是一個可使兩種不同的通信或異質網路協定交換資料的機器，我們可以在各種不同層的地方發現Gateway的存在。<br> 
    (b) <br>
    Switch是一個將一個Mac位置的封包傳送到另一個Mac位置的機器。他會記憶每一個他所連接的Mac位置。他能將封包傳到已知的Mac位置。若目的Mac位置不存在，則他會將封包傳給每一個埠。<br>
    (c) <br>
    Port forwarding 是一種在NAT裡所使用的技巧，他能讓Router外的設備連接到Router內的設備。透過將Router內的設備指定為Router的特定端口(如80端口)將資料轉發到私有網路上指定的IP地址和端口，使外部設備藉由IP位置和特定的端口連接到Router內的設備。
2. <br>
    (a) <br>
    (b) <br>
    (c) <br>
    (d) <br>
3. 
4. <br>
    (a) <br>
    (b) <br>
    (c) <br>
    (d) <br>
5. <br>
    (a) <br> 
    (b) <br>
    (c) <br>