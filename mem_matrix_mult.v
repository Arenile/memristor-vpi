module mem_matrix;
    reg[31:0] a [15:0];
    reg[31:0] w [15:0];
    reg[31:0] b [15:0];

    integer i;
    real proper_state;
    real correcting = (2**15 / 2);

    integer f;

    initial begin
        a[0] = 9; a[1] = 2; a[2] = 2; a[3] = 5;
        a[4] = 3; a[5] = 6; a[6] = 6; a[7] = 8;
        a[8] = 2; a[9] = 1; a[10] = 9; a[11] = 2;
        a[12] = 8; a[13] = 5; a[14] = 6; a[15] = 5;

        w[0] = 9; w[1] = 2; w[2] = 2; w[3] = 5;
        w[4] = 3; w[5] = 6; w[6] = 6; w[7] = 8;
        w[8] = 2; w[9] = 1; w[10] = 9; w[11] = 2;
        w[12] = 8; w[13] = 5; w[14] = 6; w[15] = 5;

        for (i = 0; i < 16; i = i + 1) begin
            b[i] = 0;
        end

        $crossbar(48, a[0], a[1], a[2], a[3],
                    a[4], a[5], a[6], a[7],
                    a[8], a[9], a[10], a[11],
                    a[12], a[13], a[14], a[15], 
                    w[0], w[1], w[2], w[3],
                    w[4], w[5], w[6], w[7],
                    w[8], w[9], w[10], w[11],
                    w[12], w[13], w[14], w[15], 
                    b[0], b[1], b[2], b[3],
                    b[4], b[5], b[6], b[7],
                    b[8], b[9], b[10], b[11],
                    b[12], b[13], b[14], b[15]);
        
        for (i = 0; i < 16; i = i + 1) begin
            $display("%d", b[i]);
        end

        
    end

endmodule