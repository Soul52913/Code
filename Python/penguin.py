import unittest
import json
import time

def checkAndSendFavorability(data, id):
    find = 0
    for i in data:
        if (i["id"] == id):
            find = 1
            localtime = time.localtime(time.time())
            if (i["favorability"] >= 100):
                print("跟你回家")
            elif (i["favorability"] >= 80):
                print("抱抱")
            elif (i["favorability"] >= 50):
                print("跳舞")
            elif (i["favorability"] >= 30):
                print("討拍")
            elif (i["favorability"] >= 20):
                print("握手")
            elif (i["favorability"] >= 10):
                print("貼貼")
            elif (i["favorability"] >= 5):
                print("哈囉")
            elif (i["favorability"] < 0):
                print("不理你")
            elif (i["favorability"] < -30):
                print("瞪你")
            elif (i["favorability"] <= -50):
                print("大聲譴責你")
            if (len(i["food"]) != 0):
                for j in i["food"]:
                    checkday = 0
                    if (int(j["dueDate"][0]) < localtime.tm_year):
                        checkday = 1
                    elif (int(j["dueDate"][0]) == localtime.tm_year):
                        if (int(j["dueDate"][1]) < localtime.tm_mon):
                            checkday = 1
                        elif (int(j["dueDate"][1]) == localtime.tm_mon):
                            if (int(j["dueDate"][2]) <= localtime.tm_mday):
                                checkday = 1
                    if (checkday == 1):
                        print("{}過期了! 請拿出來丟掉!".format(j["foodId"]))
            break
    if (find == 0):
        food = []
        new = {"id": id, "favorability": 0, "food": food}
        data.append(new)
    return data

def saveFood(data, id, foodid, dueDate):
    dueyear = dueDate[0] + dueDate[1] + dueDate[2] + dueDate[3]
    duemonth = dueDate[5]  + dueDate[6]
    dueday = dueDate[8]  + dueDate[9]
    if (dueyear.isdigit() and duemonth.isdigit() and dueday.isdigit()):
        for i in data:
            if (i["id"] == id):
                localtime = time.localtime(time.time())
                checkday = 0
                if (int(dueyear) < localtime.tm_year):
                    checkday = 1
                elif (int(dueyear) == localtime.tm_year):
                    if (int(duemonth) < localtime.tm_mon):
                        checkday = 1
                    elif (int(duemonth) == localtime.tm_mon):
                        if (int(dueday) <= localtime.tm_mday):
                            checkday = 1
                if (checkday == 1):
                    print("{}過期了!".format(foodid))
                else:
                    temp = {"foodId": foodid, "dueDate": [dueyear, duemonth, dueday]}
                    i["food"].append(temp)
                    print("存好了!")
                break
    return data

def takeFood(data, id, foodid):
    checkrm = 0
    for i in data:
        if (i["id"] == id):
            if (len(i["food"]) != 0):
                for j in i["food"]:
                    if (j["foodId"] == foodid):
                        i["food"].remove(j)
                        checkrm = 1
                    break
            break
    if (checkrm == 0):
        print("不存在這個食物")
    else:
        print("Dozo")
    return data

def cleanFridge(data, id):
    checkrm = 0
    for i in data:
        localtime = time.localtime(time.time())
        if (len(i["food"]) != 0):
            for j in list(i["food"]):
                checkday = 0
                if (int(j["dueDate"][0]) < localtime.tm_year):
                    checkday = 1
                elif (int(j["dueDate"][0]) == localtime.tm_year):
                    if (int(j["dueDate"][1]) < localtime.tm_mon):
                        checkday = 1
                    elif (int(j["dueDate"][1]) == localtime.tm_mon):
                        if (int(j["dueDate"][2]) <= localtime.tm_mday):
                            checkday = 1
                if (checkday == 1):
                    print("移除了{}!".format(j["foodId"]))
                    i["food"].remove(j)
                    i["favorability"] -= 1
                    checkrm = 1
                    if (i["id"] == id):
                        checkrm = 2
    if (checkrm == 1):
        for i in data:
            if (i["id"] == id):
                i["favorability"] += 1
                print("謝謝你,好感度加一")
    elif(checkrm == 2):
        print("這是你應該做的!")
    else:
        print("沒東西可以清")
    return data

id = input("請輸入您的學號:")
check = 0
if (len(id) != 9):
    check = 1
else:
    if (id[0] != "R" and id[0] != "B" and id[0] != "r" and id[0] != "b"):
        check = 1
    else:
        id = id.lower()
        for i in range(1, len(id)):
            if (id[i] < '0' or id[i] > '9'):
                check = 1
if (check == 0):
    with open(r'C:\Users\habor\Desktop\Code\Code\Python\haremSystem.json') as f:
        data = json.load(f)
    data = checkAndSendFavorability(data, id)
    op = input("您想做什麼? (存食物(1) /拿食物(2) /清冰箱(3) /查詢好感度(4) ):")
    op = int(op)
    if (op == 1):
        foodid = input("您想存什麼")
        dueDate = input("什麼時候到期(YYYY/MM/DD)")
        saveFood(data, id, foodid, dueDate)
    elif (op == 2):
        foodid = input("您想拿什麼")
        takeFood(data, id, foodid)
    elif (op == 3):
        cleanFridge(data, id)
    elif (op == 4):
        for i in data:
            if (i["id"] == id):
                print("您的好感度為{}".format(i["favorability"]))
    else:
        print("沒有此項服務")
    with open(r'C:\Users\habor\Desktop\Code\Code\Python\haremSystem.json', 'w') as f:
        json.dump(data, f)
    f.close()
    print("掰掰")
else:
    print("請輸入正確的學號!")