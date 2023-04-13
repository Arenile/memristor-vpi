module mem_matrix;
    reg[31:0] a;
    reg[31:0] b;
    reg[31:0] c;

    integer i;
    real proper_state;
    real correcting = (2**15 / 2);

    integer f;

    initial begin
         a = 9;
         b = 3;
         c = 8;

         $crossbar(16, a, b, c, 6,
                   1, 4, 3, 7,
                   2, 6, 7, 3,
                   4, 5, 5, 1);
    end

endmodule