(*blackbox*)
module memristor(inout rInc, inout rDec);

    always @(*) begin
        $memristor(rInc, rDec);
        $display("rDec = %d", rDec);
    end

endmodule