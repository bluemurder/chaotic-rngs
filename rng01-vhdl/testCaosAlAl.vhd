--------------------------------------------------------------------------------
-- Company:       University of Genoa
-- Engineer:      Alessio Leoncini, Alberto Oliveri
--
-- Create Date:   16:27:59 10/06/2011
-- Design Name:   
-- Module Name:   testCaosAlAl.vhd
-- Project Name:  Caos
-- Target Device:  
-- Tool versions:  
-- Description:   
-- 
-- VHDL Test Bench Created by ISE for module: CaosAlAl
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
use ieee.std_logic_textio.all;
LIBRARY std;
use STD.textio.all;
 
-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--USE ieee.numeric_std.ALL;
 
ENTITY testCaosAlAl IS
END testCaosAlAl;
 
ARCHITECTURE behavior OF testCaosAlAl IS 
 
    -- Component Declaration for the Unit Under Test (UUT)
 
    COMPONENT CaosAlAl
    PORT(
         ck : IN  std_logic;
         res : IN  std_logic;
         out0 : OUT  std_logic
        );
    END COMPONENT;

    --Inputs
    signal ck : std_logic := '0';
    signal res : std_logic := '0';

    --Outputs
    signal out0 : std_logic;
    -- No clocks detected in port list. Replace ck below with 
    -- appropriate port name 
 
    constant ck_period : time := 10 ns;
 
BEGIN
 
    -- Instantiate the Unit Under Test (UUT)
    uut: CaosAlAl PORT MAP (
        ck => ck,
        res => res,
        out0 => out0
    );

    -- Clock process definitions
    ck_process :process
    begin
        ck <= '0';
        wait for ck_period/2;
        ck <= '1';
        wait for ck_period/2;
    end process;
 

    -- Stimulus process
    stim_proc: process
    begin
        -- hold reset state for 100 ns.
        res <= '1';
        wait for 100 ns;
        res<='0';
        -- write a single line
        wait;
    end process;

    -- Write bigregister process
    write_file: process (ck) is
        file my_output : TEXT open WRITE_MODE is "Test.out";
        variable my_output_line :  LINE;
    begin
        if rising_edge(ck) then
            write(my_output_line,out0);
            writeline(my_output, my_output_line);
        end if;
    end process write_file;

END;
