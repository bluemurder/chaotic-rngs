library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;

use work.randgen_package.all;

entity randgen is
	 Port ( clk : in  STD_LOGIC;
			reset : in  STD_LOGIC;
			ready : out STD_LOGIC;
			output : out  STD_LOGIC);
end randgen;

architecture Behavioral of randgen is
	
	-- Components
	
	component chaoticMap is
		Port ( clk : in std_logic;
			reset : in std_logic;
			output : out std_logic);
	end component;
	
	component vonNeumannCorrector is
		Port ( clk : in std_logic;
			reset : in std_logic;
			data_in : in std_logic;
			ready_in : in std_logic;
			data_out : out std_logic;
			ready_out : out std_logic);
	end component;
	
	-- Signals
		
	signal counter : integer range 0 to SKIP := 0;
	signal signal_output : std_logic;
	signal signal_ready_in : std_logic;
	
begin

	-- Port maps
	
	inst_chaoticMap : chaoticMap 
	port map ( clk => clk,
		reset => reset,
		output => signal_output);
		
	inst_vonNeumannCorrector : vonNeumannCorrector
	port map ( clk => clk,
		reset => reset,
		data_in => signal_output,
		ready_in => signal_ready_in,
		data_out => output,
		ready_out => ready);
		
	-- Processes
		
	proc_ready : process(clk,counter,reset)
	begin
		if reset = '1' then
			signal_ready_in <= '0';
		elsif rising_edge(clk) then
			if counter = SKIP then
				signal_ready_in <= '1';
			else
				signal_ready_in <= '0';
			end if;
		end if;
	end process;
	
	proc_counter : process(clk,reset)
	begin
		if reset = '1' then
			counter <= 0;
		elsif rising_edge(clk) then
			if counter = SKIP then
				counter <= 0;
			else
				counter <= counter+1;
			end if;
		end if;
	end process;

end Behavioral;
