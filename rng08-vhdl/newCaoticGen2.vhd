----------------------------------------------------------------------------------
-- Company:        University of Genoa
-- Engineer:       Alessio Leoncini, Alberto Oliveri
-- 
-- Create Date:    11:06:29 07/26/2011 
-- Design Name: 
-- Module Name:    newCaoticGen - Behavioral 
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
use IEEE.STD_LOGIC_SIGNED.ALL; 
use ieee.std_logic_arith.all;
--use ieee.Signed_to_Bit.all;
--use package Signed_to_Bit.all;

--Library YYY_math_lib ;
--use YYY_math_lib.ZZZ_fixed_pkg.all ;

use work.variable_Caos.all ;
-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx primitives in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity newCaoticGen2 is
    Port ( Clk : in  STD_LOGIC;
              reset : IN  std_logic;
           X_out : out  signed(numbit-1 downto 0));
end newCaoticGen2;




architecture Behavioral of newCaoticGen2 is


signal x : signed(numbit-1 downto 0):= signed(convtosigned(Val_init));

begin

process(Clk,reset)

variable k : signed(numbit-1 downto 0):= signed(convtosigned(Param));

variable temp: integer;

begin
X_out <= x;
    if reset = '0' then
        if (Clk'event and Clk ='1') then
            if (x < conv_signed(0,numBit)) then
                temp:=mult(k,x);
                x <= conv_signed(2**(scalamento)  + temp,numBit);
                temp := 0;
            else
                temp:=mult(k,x);
            
                x <= conv_signed(-2**(scalamento)+temp,numBit);
                temp:=0;
            
            end if;
        end if;
    end if;

--X_out <=k;
end process;


end Behavioral;

