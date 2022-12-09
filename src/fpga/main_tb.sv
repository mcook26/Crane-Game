// main_tb.sv
// Miles Cook
// mdcook@g.hmc.edu

module main_tb();
	// Internal Signals 
	logic en, reset, clk_out, latch, oe, slowClk1;
	logic[3:0] row_out;
	logic[2:0] rgb0, rgb1;
	

	// Instantiate dut
	main_fsm dut(slowClk1, en, reset, row_out, rgb0, rgb1, clk_out, latch, oe);

	// Generate clk
	initial
	  forever begin 
		slowClk1 = 1'b0; #5;
		slowClk1 = 1'b1; #5;
	  end 
	  
	initial 
	  begin 
		en = 1'b0; #5;
		en = 1'b1;
		reset = 1'b1;
	  end
	
endmodule 
	


