--------------------------------------------------------------------------------
-- Company:       University of Genoa
-- Engineer:      Alessio Leoncini, Alberto Oliveri
--
-- Create Date:   15:44:18 09/19/2011
-- Design Name:   
-- Module Name:   test.vhd
-- Project Name:  NewCaos
-- Target Device:  
-- Tool versions:  
-- Description:   
-- 
-- VHDL Test Bench Created by ISE for module: newCaoticGen2
-- 
-- Dependencies:
-- 
-- Revision:
-- Revision 0.01 - File Created
-- Additional Comments:
--
-- Notes: 
-- This testbench has been automatically generated using types std_logic and
-- std_logic_vector for the ports of the unit under test.  Xilinx recommends
-- that these types always be used for the top-level I/O of a design in order
-- to guarantee that the testbench will bind correctly to the post-implementation 
-- simulation model.
--------------------------------------------------------------------------------
LIBRARY ieee;
USE ieee.std_logic_1164.ALL;
USE ieee.std_logic_signed.all;
use ieee.std_logic_arith.all;

LIBRARY std;
USE std.textio.all;
use ieee.std_logic_textio.all;
--use ieee.Signed_to_Bit.all;
use work.variable_Caos.all ;
use STD.textio.all;
 
-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--USE ieee.numeric_std.ALL;
 
ENTITY test IS
END test;
 
ARCHITECTURE behavior OF test IS 
 
    -- Component Declaration for the Unit Under Test (UUT)
 
    COMPONENT newCaoticGen2
    PORT(
         Clk : IN  std_logic;
         reset : IN  std_logic;
         X_out : OUT  signed(numbit-1 downto 0)
        );
    END COMPONENT;
    

   --Inputs
   signal Clk : std_logic := '0';
   signal reset : std_logic := '0';

 	--Outputs
   signal X_out : signed(numbit-1 downto 0);

   -- Clock period definitions
   constant Clk_period : time := 10 ns;
 
BEGIN
 
	-- Instantiate the Unit Under Test (UUT)
   uut: newCaoticGen2 PORT MAP (
          Clk => Clk,
          reset => reset,
          X_out => X_out
        );

   -- Clock process definitions
   Clk_process :process
   begin
		Clk <= '0';
		wait for Clk_period/2;
		Clk <= '1';
		wait for Clk_period/2;
   end process;
 

   -- Stimulus process
   stim_proc: process
   begin		
      -- hold reset state for 100 ns.
      wait for 100 ns;	

      wait for Clk_period*100;
		reset <='1';
      wait for Clk_period;
		reset <='0';
      wait for Clk_period*100;
		wait;
		
   end process;


	process (clk)
        variable wrbuf :line;
     begin
         
			 
            if (Clk'event and Clk ='1') then
				 write(wrbuf, conv_std_logic_vector( X_out,numBit));
            -- write(wrbuf, string'("; lfsr_2: ")); write(wrbuf, conv_integer(lfsr_2));
             writeline(output, wrbuf);
				end if;
		 
     end process;
	  
--	-- Write file process
	write_file: process (Clk) is
		file my_output : TEXT open WRITE_MODE is "Test.out";
		variable my_line : LINE;
		variable my_output_line :  LINE;
	begin
		if rising_edge(Clk) then
			write(my_output_line,X_out(numBit-1));--std_logic_vector(X_out));
			writeline(my_output, my_output_line);
		end if;
	end process write_file;


END;
