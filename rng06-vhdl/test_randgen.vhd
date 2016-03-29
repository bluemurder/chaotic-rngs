LIBRARY ieee;
USE ieee.std_logic_1164.ALL;
use ieee.std_logic_textio.all;
LIBRARY std;
use STD.textio.all;
 
use work.randgen_package.all;
 
ENTITY test_randgen IS
END test_randgen;
 
ARCHITECTURE behavior OF test_randgen IS 
 
	-- Component Declaration for the Unit Under Test (UUT)
 
	component randgen is
		Port ( clk : in  STD_LOGIC;
			reset : in  STD_LOGIC;
			ready : out STD_LOGIC;
			output : out  STD_LOGIC);
	end component;

	--Inputs
	signal clk : std_logic := '0';
	signal reset : std_logic := '0';

	--Outputs
	signal output : std_logic;
	signal ready : std_logic;
   
BEGIN
 
	-- Instantiate the Unit Under Test (UUT)
	uut: randgen PORT MAP (
		clk => clk,
		reset => reset,
		ready => ready,
		output => output
	);

-- Clock process definitions
	clk_process :process
	begin
		clk <= '0';
		wait for CLK_PERIOD/2;
		clk <= '1';
		wait for CLK_PERIOD/2;
	end process;
 

	-- Stimulus process
	stim_proc: process
	begin
		-- hold reset state for 100 ns.
		reset <= '1';
		wait for 100 ns;	
		reset <='0';
		-- write a single line
		wait;
	end process;
	
	-- Write bigregister process
	write_file: process (clk) is
		file my_output : TEXT open WRITE_MODE is "Test.out";
		variable my_output_line :  LINE;
	begin
		if rising_edge(clk) then
		   if ready = '1' and reset = '0' then
				write(my_output_line,output);
				writeline(my_output, my_output_line);
			end if;
		end if;
	end process write_file;

END;
