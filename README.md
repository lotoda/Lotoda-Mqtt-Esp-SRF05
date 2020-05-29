# Lotoda MQTT ESP SRF05

Bạn dễ dàng kết nối đến LOTODA platform bằng Board ESP8266 để tạo một dự án đọc khoảng cách từ cảm biến siêu âm SRF05 và vẽ đồ thị trên app Lotoda theo thời gian thực! Hãy download code tại đây và sử dụng Arduno IDE để nạp code!

Để biết thêm chi tiết xem thêm video tại website: https://.lotoda.vn và https://shop.lotoda.vn

# Sơ đồ đấu nối như sau:

Kết nối từ NodeMCU ESP8266 tới SRF05 như sau:

- Chân GND -> GND 
- Chân 5V -> VCC 
- Chân D1 (GPIO 05) -> TRIG
- Chân D2 (GPIO 04) -> ECHO
# Sơ đồ chân của NodeMCU ESP8266 như sau:
![](https://raw.githubusercontent.com/lotoda/Lotoda-Mqtt-Esp/master/nodemcudevkit_v1-0_io.jpg)

# Cảm biến siêu âm SRF05
![](https://iotlabchannel.com/wp-content/uploads/2018/07/Module-c%E1%BA%A3m-bi%E1%BA%BFn-si%C3%AAu-%C3%A2m-SRF05_2-e1542634783735.jpg?v=e14da64a5617)

Thông số kỹ thuật:

- Điện áp hoạt động: 5V
- Dòng cấp: 30mA, 50mA Max.
- Tần số: 40KHz
- Khoảng cách đo được xa nhất: 3 m
- Phát hiện vật cản trong khoảng: 3cm đến 3m
- Kích thước: 43mm x 20mm x 17mm 

IoT LOTODA platform "Your IoT Connected Devices" www.lotoda.vn
