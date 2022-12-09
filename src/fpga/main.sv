// Miles Cook - mdcook@g.hmc.edu
// 11/16/2022
// E155 Final Project Code 
// Credit to Reem Alkhamis and Sabrine Griffith's E155 Final Project 
// for a strong foundation to start.
// Code to control Adafruit 32x32 LED array and provide countdown
// with a decreasing "tank" size

// Ideas:
// 1. Decrement memory as time progrress (have to hold certain rgb at 
//    set values 

// Top Level Module 
module led_mat(input  logic en, 
               input  logic reset,
               output logic [3:0] row_out,
               output logic [2:0] rgb0,
               output logic [2:0] rgb1,
               output logic clk_out,
               output logic latch,
               output logic oe);

    // Declare internal signals 
    logic fast_clk;
	logic [2:0] slowClk1;
	logic [22:0] controlClk;
	logic lA, lB, lC, lD, lE;
	logic[31:0] timeCurr;			
	
    // Setup High Speed OSC
    HSOSC #(.CLKHF_DIV ("0b10")) hf_osc (.CLKHFEN(1'b1), .CLKHFPU(1'b1), .CLKHF(fast_clk)); // 12 Mhz
	
	// Clock Divider for most things
	always_ff@(posedge fast_clk, negedge reset)
		if (!reset) slowClk1 <=0;
		else slowClk1 <= slowClk1 + 1'b1;  // divide down to 850 kHz 
	
	// Clock divider for column decrementing 
	always_ff@(posedge fast_clk, negedge reset)
		if (!reset) controlClk <= 0;
		else controlClk <= controlClk + 1'b1;  // max val = 4194304 so 12*10^6 / 4194304 = 2.86s^-1
			
	
	
    // Call helper functions
	main_fsm main_fsm(slowClk1[2], controlClk[21], reset, en, timeCurr);
	
	// Case statement to determine logic inputs 
	assign lA = (timeCurr > 0 && timeCurr < 16)   ? 1 : 0;
	//assign lB = (timeCurr == 17)  ? 1 : 0;
	assign lC = (timeCurr > 18 && timeCurr < 82 && !(timeCurr % 4))  ? 1 : 0;
	//assign lD = (timeCurr == 20) ? 1 : 0;
	assign lE = (timeCurr > 84 && timeCurr < 97) ? 1 : 0;
	
	// Final call to get outputs
    main     main(slowClk1[2], controlClk[21], reset, en, lA, lB, lC, lD, lE, rgb0, rgb1, oe, latch, row_out, clk_out);

endmodule 


// Main FSM
module main_fsm(input logic clk,
				input logic controlClk,
				input logic reset, 
				input logic en,
				output logic [31:0] timeCurr);
				
	// Timing 
	always_ff @(posedge controlClk, negedge reset)
		if(!reset || !en)  timeCurr <= 0;
	else if (en) timeCurr <= timeCurr + 1;
endmodule


// Main control module 
module main(input logic clk,
			input logic controlClk,
			input logic reset, 
			input logic en,
			input logic lA, lB, lC, lD, lE,
			output logic [2:0] rgb0, rgb1,
			output logic oe,
			output logic latch,
			output logic [3:0] row,
			output logic clk_out);
	
	logic [95:0] RAM0[2:0], RAM1[2:0];
	logic [95:0] row0, row1;
	logic [5:0] counter; 
	logic [4:0] col;
	logic [3:0] radr, rowCon;
	logic hold, start;
	logic blink;
	logic [3:0] blink_threshold;
	logic [4:0] row_counter;
	
	// Read in input data 
	initial $readmemh("config_top.txt", RAM0);
	initial $readmemh("config_bottom.txt", RAM1);
	assign row0 = RAM0[0];
	assign row1 = RAM1[0];
	
	always_ff @(posedge clk, negedge reset) begin
		if(!reset) begin             // reset
					counter <= 0;
					col <=0;
					hold <= 1'b1;
					start <= 0;
				   end		   
		 else if (counter == 60 || hold == 1)  // wrap around 
				   begin 
					col <= 0;
					counter <= 0;
					hold <= 0;
				   end 
		 else if (counter>=31 && counter < 60) // select col 
				   begin 
				    col <= col;
					counter <= counter + 1'b1;
				   end 
		 else if (hold == 0) 				// increment counter 
				   begin 
					counter <= counter + 1'b1;
					col <= col+1'b1;
				   end 
	end 
	
	// Row control 
	/*
	always_ff @(posedge controlClk, negedge reset) begin
		if(!reset || !en) rowCon <= row; 
		else if (light_control[0]) rowCon <= rowCon + 2;  
		else if (light_control[1]) rowCon <= 16;
		else if (light_control[2]) rowCon <= rowCon - 1;
		else if (light_control[3]) rowCon <= 0;
		else  rowCon <= ~rowCon;
	end
	*/
	always_ff @(posedge controlClk, negedge reset) begin
		if(!reset || !en) rowCon <= row; 
		else if (lA) rowCon <= rowCon + 1;  // add in some sort of decrement cancel 
		else if (lB) rowCon <= 16;
		else if (lC) rowCon <= rowCon - 1;
		else if (lD) rowCon <= 0;
		else if (lE) rowCon <= ~rowCon;
	end

	// Row select 
	always_ff @(posedge clk, negedge reset) begin
		if (!reset) 
				row<=0; 
		else if (counter == 60 && (row < rowCon))
		  begin
			row <= row + 1;
		  end
		else 
		  begin
			if (counter == 60) row <= 0;
		  end
	end
	
	timControl timC(clk, reset, counter, oe, latch);
	driveColor color(clk, en, row0, row1, col, rgb0, rgb1);
	rowControl  rowC(clk, reset, latch, oe, radr);

	// Clk out control
	always_comb
		begin
			if(counter < 32)
				clk_out = clk;
			else if (counter == 60)
				clk_out = 0;
			else 
				clk_out = 1;
		end
endmodule 

// timControl: controls the timing of the latch and oe signals 
module timControl(input logic clk, reset,
				  input logic [5:0] counter,
				  output logic oe,
				  output logic latch);
	
	always_ff @(posedge clk) 
	begin 
		if (counter == 32) begin
			latch <= 1;
			oe <= 1; 
			end
		else if (counter == 33) begin
			latch <= 0;
			oe <= 0;
			end
		else if (counter >= 34 && counter <= 59) begin
			latch <= 0;
			oe <= 1;
			end 
		else begin
			oe <= 1;
			latch <= 0;
			end 
	end 
endmodule

// Color Drive: control colors sent over rgb 
module driveColor(input logic clk_out,
				  input logic start,
				  input logic [95:0] row0, row1,
				  input logic [4:0] col,
				  output logic [2:0] rgb0, rgb1);
	
	always_ff@(negedge clk_out)
	begin 
		rgb0[0] <= row0[3*col];
		rgb0[1] <= row0[3*col+1];
		rgb0[2] <= row0[3*col+2];
		
		rgb1[0] <= row1[3*col];
		rgb1[1] <= row1[3*col+1];
		rgb1[2] <= row1[3*col+2];
	end 

endmodule 
	
// Counter for which row to set 
module rowControl (input logic clk,
			input logic reset,
			input logic latch,
			input logic oe,
            output logic [3:0] radr);

    always_ff @(posedge clk, negedge reset) begin 
        if(!reset)  		   radr <= 0;
		else if (latch && oe)  radr <= radr + 1;
    end 

endmodule	
