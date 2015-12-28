----------------------------------------------------------------------------------
-- Company:        University of Genova
-- Engineer:       Alessio Leoncini, Alberto Oliveri
-- 
-- Create Date:    14:28:47 10/06/2011 
-- Design Name: 
-- Module Name:    CaosAlAl - Behavioral 
-- Project Name: 
-- Target Devices: 
-- Tool versions: 
-- Description:    Random Bit Generator based on a chaotic map
--
-- Dependencies: 
--
-- Revision: 
-- Revision 0.01 - File Created
-- Additional Comments: 
--
----------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx primitives in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity CaosAlAl is
    generic (nbit : integer := 32);
	 Port ( ck : in  STD_LOGIC;
           res : in  STD_LOGIC;
           out0 : out  STD_LOGIC);
end CaosAlAl;

architecture Behavioral of CaosAlAl is
	signal reg : signed(nbit-1 downto 0);
	-- Supposing 2 integer bits and two's complement, one and minus one values
	constant zero : signed(nbit-1 downto 0) := "00000000000000000000000000000000";
	constant one : signed(nbit-1 downto 0) := "01000000000000000000000000000000";
	constant minusone : signed(nbit-1 downto 0) := "11000000000000000000000000000000";
	constant x0  : signed(nbit-1 downto 0) := "00100000000000000000000000000000";
begin
	
	out0 <= reg(nbit-1);

main:process(ck,res)
begin
	if res = '0' then
		if (ck'event and ck ='1') then
			if (reg < zero) then
				reg <= (( reg(nbit-2 downto 0) & '0' ) - ( "111" & reg(nbit-1 downto 3) )) + one;
			else
				reg <= (( reg(nbit-2 downto 0)&'0' ) - ( "000" & reg(nbit-1 downto 3) )) + minusone;
			end if;
		end if;
	else
		-- init
		reg <= x0;
	end if;
end process;

end Behavioral;