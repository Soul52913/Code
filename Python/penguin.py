import unittest
import json

def checkAndSendFavorability(data, id):
    find = 0
    for i in data:
        if (i["id"] == id):
            find = 1
            print("您當前的好感度為 {}".format(id["favorability"]))
    if (find == 0):
        food = []
        new = {"id": id, "favorability": 0, "food": food}
        data.append(new)
    return data

id = input("請輸入您的學號:")
check = 0
if (len(id) != 9):
    check = 1
else:
    if (id[0] != "R" or id[0] != "B" or id[0] != "r" or id[0] != "b"):
        check = 1
    else:
        id = id.lower()
        for i in range(1, len(id)):
            if (id[i] <= '0' or id[i] >= '9'):
                check = 1
if (check == 0):
    with open("haremSystem.json") as f:
        data = json.load(f)
    data = checkAndSendFavorability(data, id)
    op = input("您想做什麼? (存食物/拿食物/清冰箱):")
    if (op == "存食物" or op == "存食物" or op == "存食物"):
        a = 0
    else:
        print("沒有此項服務")
    with open("haremSystem.json") as f:
        json.dump(data, f)
    f.close()
else:
    print("請輸入正確的學號!")