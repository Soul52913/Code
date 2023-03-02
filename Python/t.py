encrypted = "A{Dhi:<oP1sS4gNTcuy_@kln#%are+*f&t^>}"
mapping =   "0123456789abcdefghijklmnopqrstuvwxyzA"
flag = "e0b0189cjf34akmqrdsov4msp4atahg3uqnwqaa37msy27nx5i7h6x34nlza7A"
ans = ""
for c in flag:
    if c in mapping and c in encrypted:
        ans += mapping[encrypted.find(c)]
print(ans)
