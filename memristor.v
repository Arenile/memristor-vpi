<<<<<<< HEAD
module memristor;
    reg[7:0] a [3:0];
    reg[7:0] b;
    reg[7:0] c;

    initial begin
        a[0] = 8;
        a[1] = 1;
        a[2] = 0;
        b = 2;
        $memristor(1, 5);
        $display(c);
=======
(*blackbox*)
module memristor(inout rInc, inout rDec);

    always @(*) begin
        $memristor(rInc, rDec);
        $display("rDec = %d", rDec);
>>>>>>> 6f9b27f654df014a55eee110c5e10f826b0de222
    end

endmodule