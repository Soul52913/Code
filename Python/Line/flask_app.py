from flask import Flask, request, abort
from pyzbar import pyzbar
import cv2
from glob import glob

from linebot import (
    LineBotApi, WebhookHandler
)
# 引入 linebot 異常處理
from linebot.exceptions import (
    InvalidSignatureError
)

from linebot.models import (
    MessageEvent, TextMessage, TextSendMessage, ImageSendMessage
)

def decode(image):
    # decodes all barcodes from an image
    
    decoded_objects = pyzbar.decode(image)
    for obj in decoded_objects:
        image = draw_barcode(obj, image)
        print("Data:", obj.data)

    return image
def draw_barcode(decoded, image):
    # n_points = len(decoded.polygon)
    # for i in range(n_points):
    #     image = cv2.line(image, decoded.polygon[i], decoded.polygon[(i+1) % n_points], color=(0, 255, 0), thickness=5)
    # uncomment above and comment below if you want to draw a polygon and not a rectangle
    image = cv2.rectangle(image, (decoded.rect.left, decoded.rect.top), 
                            (decoded.rect.left + decoded.rect.width, decoded.rect.top + decoded.rect.height),
                            color=(0, 255, 0),
                            thickness=5)
    return image

data = []
observe = []
cata = [1, 0, 0, 0, 0, 0]
item = {}
temp = ''
inputlist = [] 
user_command_dict = {}

app = Flask(__name__)

line_bot_api = LineBotApi('trOYkxOp1N4ejMzjASmkX4ZFRaoCAhiJpeAwAWOxPv6E/DJCh2BeFk6vStb3Asr+T/dKl/Z7NLu6H7FpLEqAhcOnXXiX0bcq/vqZsdD4D0R2H7TNmdt970byu3j+qj3Bfr2r/YtY+8dORzRWRZnRKwdB04t89/1O/w1cDnyilFU=')
handler = WebhookHandler('8d958af468659cad7f389ca10125ba9e')

# 此為 Webhook callback endpoint
@app.route("/callback", methods=['POST'])

def callback():
    # 取得網路請求的標頭 X-Line-Signature 內容，會確認請求是從 LINE Server 送來的避免資訊安全問題
    signature = request.headers['X-Line-Signature']

    # 將送來的網路請求內容取出
    body = request.get_data(as_text=True)

    # handle webhook body（轉送給負責處理的 handler，ex. handle_message）
    try:
        handler.handle(body, signature)
    except InvalidSignatureError:
        print("Invalid signature. Please check your channel access token/channel secret.")
        abort(400)

    return 'OK'

# decorator 負責判斷 event 為 MessageEvent 實例，event.message 為 TextMessage 實例。所以此為處理 TextMessage 的 handler
@handler.add(MessageEvent, message=TextMessage)
def handle_message(event):
    user_message = event.message.text
    reply_message = TextSendMessage(text='請輸入正確指令')
    # 根據使用者輸入 event.message.text 條件判斷要回應哪一種訊息
    user_id = event.source.user_id
   # 根據使用者 ID 暫存指令
    user_command = user_command_dict.get(user_id)
    print('user_command', user_command)

    if user_message == '@價錢比較' and user_command != '@價錢比較':
        reply_message = TextSendMessage(text='請傳商品條碼圖片')
        user_command_dict[user_id] = '@價錢比較'
    elif user_command == '@價錢比較':
        reply_message = TextSendMessage(text='該產品為 御茶園!\n在LINE購物中有更低價格! 為23元')
        user_command_dict[user_id] = None
    elif user_message == '@觀察期追蹤' and user_command != '@觀察期追蹤':
        reply_message = TextSendMessage(text='請輸入商品名稱')
        user_command_dict[user_id] = '@觀察期追蹤'
    elif user_command == '@觀察期追蹤':
        temp = user_message
        observe.append(user_message)
        reply_message = TextSendMessage(text='已加入觀察期名單 !')
        user_command_dict[user_id] = None
    elif user_message == '@記帳' and user_command != '@記帳':
        reply_message = TextSendMessage(text='請輸入商品名稱')
        user_command_dict[user_id] = '@記帳2'
    elif user_command == '@記帳2':
        temp = user_message
        inputlist.append(user_message)
        reply_message = TextSendMessage(text='請輸入商品種類 (食 (1)/衣 (2)/住 (3)/行 (4)/樂 (5))')
        user_command_dict[user_id] = '@記帳3'
    elif user_command == '@記帳3':
        temp = user_message
        if (int(temp) == 1 or int(temp) == 2 or int(temp) == 3 or int(temp) == 4 or int(temp) == 5):
            reply_message = TextSendMessage(text='請輸入商品價格')
            user_command_dict[user_id] = '@記帳4'
            inputlist.append(temp)
        else:
            reply_message = TextSendMessage(text='輸入錯誤! 請重新輸入!')
            inputlist.clear()
            user_command_dict[user_id] = None
    elif user_command == '@記帳4':
        temp = user_message
        if (temp.isdigit()):
            item[inputlist[0]] = int(temp)
            data.append(item)
            item.clear()
            cata[int(inputlist[1])] += int(temp)
            cata[0] += int(temp)
            reply_message = TextSendMessage(text=f'當前比例: \n食 {cata[1]/cata[0] * 100}%, \n衣 {cata[2]/cata[0] * 100}%, \n住 {cata[3]/cata[0] * 100}%, \n行 {cata[4]/cata[0] * 100}%, \n樂 {cata[5]//cata[0] * 100}%')
        else:
            inputlist.clear()
        user_command_dict[user_id] = None
    elif user_message == '@查詢消費比例占比':
        reply_message = TextSendMessage(text=f'當前比例: \n食 {cata[1]/cata[0] * 100}%, \n衣 {cata[2]/cata[0] * 100}%, \n住 {cata[3]/cata[0] * 100}%, \n行 {cata[4]/cata[0] * 100}%, \n樂 {cata[5]//cata[0] * 100}%')
    else:
        reply_message = TextSendMessage(text='蛤?')
    # 回傳訊息給使用者
    line_bot_api.reply_message(
        event.reply_token,
        reply_message)

# __name__ 為內建變數，若程式不是被當作模組引入則為 __main__
if __name__ == "__main__":
    # 運行 Flask server，預設設定監聽 port 5000（網路 IP 位置搭配 Port 可以辨識出要把網路請求送到那邊 xxx.xxx.xxx.xxx:port）
    app.run()