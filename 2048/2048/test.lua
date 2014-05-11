a = moveAble();
while a do
	luaMoveLeftFunc();
	--.sleep(1);
	luaMoveUpFunc();
		--.sleep(1);
	luaMoveRightFunc();
		--.sleep(1);
	luaMoveDownFunc();
		--.sleep(1);
	
	a = moveAble();
end