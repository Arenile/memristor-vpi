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
    end
endmodule