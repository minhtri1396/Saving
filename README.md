# Saving
Tính số tiền có được sau 1 năm gửi

## Main flow:
Nhập vào textbox(*) Money số tiền hiện tại đang có, nhập vào textbox(*) Interest rate lãi suất trong 1 năm,
click button Calculate để hiển thị kết quả, tổng tiền nhận được sau 1 năm gửi, trong Message box.
Ví dụ: nhập 100000 vào textbox Money và 0.51 vào textbox Interest rate, rối click button Calculate thì
Message box xuất hiện và hiển thị thông điệp: "After 1 year, we have 151,000(**).

## Additional flow:
- Bỏ trống một trong hai hoặc cả hai text box thì hiển thị thông báo: "Money and Interest Rate must be fill in completely."
- Nhập dấu '.' không hợp lệ thì thông báo: "You wrote invalid dots." và kèm theo các ví dụ dấu '.' hợp lệ và không hợp lệ.
- Nhập ký tự không hợp lệ, là ký tự khác 0 -> 9, khác dấu '.' và khác khoảng trắng thì thông báo:
	"You wrote invalid characters." và kèm theo thông báo các ký tự nào là hợp lệ.

**Chú thích:**  
- giá trị nhập vào textbox có thể nhập chuỗi có chứa ký tự:
	+ 0 -> 9
	+ Khoảng trắng, vd: 100 000. Nếu chỉ nhập khoẳng trắng vào textbox thì xem như đó là số 0
	+ Dấu '.' để ngăn cách phần thập phân hay chia ra từng phần đơn vị, chục, trăm, nghìn, ...
		VD: 100.001 thì chương trình xem đây là số thực có phần thập phân là .001
		    100.000.000 thì chương trình xem đây là số nguyên có giá trị là 100 000 000 (một trăm triệu)
		    100.000 thì chương trình xem đây là số nguyên có giá trị là 100 (một trăm)

- giá trị kết quả trả về có thể có chứa ký tự:
	+ Dấu ',' để thể hiện sự chia ra từng phần đơn vị, chục, trăm, nghìn, ...
		VD: 100,000 thì chương trình xem đây là số nguyên có giá trị là 100 000 (một trăm nghìn)
	+ Dấu '.' để ngăn cách phần thập phân.
		VD: 100.001 thì chương trình xem đây là số thực có phần thập phân là .001
