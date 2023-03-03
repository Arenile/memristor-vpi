module memristor;
    reg[7:0] a;
    reg[7:0] b;
    reg[7:0] c;

    initial begin
        a = 5;
        b = 2;
        $memristor(a, b, c);
        $display(c);
    end
endmodule