library IEEE;
use IEEE.STD_LOGIC_1164.all;
use IEEE.NUMERIC_STD.ALL;

package randgen_package is

-- Declare constants

	-- Number of bits used for internal register of the chaotic map
	constant N_BIT : integer := 16;

	-- Number of bits to skip in the output sequence
	constant SKIP : integer := 3;
	
	-- Initial condition for the chaotic map
	constant X0 : signed(N_BIT-1 downto 0) := (N_BIT-3 => '1', others => '0');	-- 0.5
	
	-- Enables the Von Neumann corrector
	constant ENABLE_VON_NEUMANN : boolean := true;
	
	-- Clock period for the simulation
	constant CLK_PERIOD : time := 10 ns;

end randgen_package;


package body randgen_package is

end randgen_package;
