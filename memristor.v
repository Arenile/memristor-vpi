module memristor;
    reg[31:0] a;
    reg[31:0] b;
    reg[31:0] c;

    integer i;

    initial begin
         a = 0;
         b = 3;
         c = 0;
        // b = 2;
        // $memristor(1, 5);
        // $display(c);
        for (i = 0; i < 100; i = i + 1) begin
            $display(c);
            $memristor(a, b, c);
            $display(c);
        end
    end

endmodule