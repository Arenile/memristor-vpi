module memristor (in v1, in v2, out m);

    reg prev_m;

    initial begin
        prev_m = 0;
    end

    always @(posedge clk ) begin
        m <= (v1 == 1'b1 && v2 == 1'b1) ? prev_m :
             (v1 == 1'b0 && v2 == 1'b0) ? prev_m :
             (v1 == 1'b1 && v2 == 1'b0) ? 1'b0 :
             (v1 == 1'b0 && v2 == 1'b1) ? 1'b1 :
    end

endmodule