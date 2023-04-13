module memristor;
    reg[31:0] a;
    reg[31:0] b;
    reg[31:0] c;

    integer i;
    real proper_state;
    real correcting = (2**15 / 2);

    integer f;

    initial begin
         a = 0;
         b = 3;
         c = 0;

         f = $fopen("verilog_with_memrist.csv", "w");
        // b = 2;
        // $memristor(1, 5);
        // $display(c);
        for (i = 0; i < 1000; i = i + 5) begin
            $memristor(a, b, c);
            $display("c = %d",c);
            proper_state = c / correcting;

            if (c > 0.5*(2**15 / 2)) begin
                a = 1;
            end

            $fwrite(f, "%d, %f, %d\n", i, proper_state, a);

            $display("a = %d", a);

        end
        $fclose(f);
    end

endmodule