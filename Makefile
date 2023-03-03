debug: memristor.c memristor.v
	iverilog-vpi memristor.c 
	iverilog -o memristor.vvp memristor.v

test: memristor.vvp
	vvp -M . -m memristor memristor.vvp 
