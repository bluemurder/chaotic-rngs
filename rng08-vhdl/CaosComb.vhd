----------------------------------------------------------------------------------
-- Company:        University of Genoa
-- Engineer:       Alessio Leoncini
-- 
-- Create Date:    14:28:47 10/06/2011 
-- Design Name: 
-- Module Name:    CaosComb - Behavioral 
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

entity CaosComb is
    Port ( res : in  STD_LOGIC;
           out0 : out  STD_LOGIC);
end CaosComb;

architecture Behavioral of CaosComb is
    
    -- Integer part is ALWAYS 2 bits
    constant nbit : integer := 128; -- total bits num
    
    signal reg_in : signed(nbit-1 downto 0);
    signal reg_out : signed(nbit-1 downto 0);
    -- Supposing 2 integer bits and two's complement, one and minus one values
    constant zero : signed(nbit-1 downto 0) := (others => '0');
    constant one : signed(nbit-1 downto 0) := (nbit-2 => '1', others => '0');
    constant minusone : signed(nbit-1 downto 0) := (nbit-1 => '1', nbit-2 => '1', others => '0');
    -- x0 = 0.5
    constant x0  : signed(nbit-1 downto 0) := (nbit-3 => '1', others => '0');
    
begin
    
    -- only sign of register in output
    out0 <= reg_out(nbit-1);

    -- map
    proc_map: process(reg_in)
    begin
        -- 1.875 * reg  =  (2*reg) - (reg/8)  =  (reg<<1) - (reg>>3)
        if (reg_in < zero) then
            -- if reg<1, reg = 1.875 * reg + 1
            reg_out <= (( reg_in(nbit-2 downto 0) & '0' ) - ( "111" & reg_in(nbit-1 downto 3) )) + one;
        else
            -- else, reg = 1.875 * reg - 1
            reg_out <= (( reg_in(nbit-2 downto 0)&'0' ) - ( "000" & reg_in(nbit-1 downto 3) )) + minusone;
        end if;
    end process;
    
    -- init condition and loop processing
    proc_loop: process(reg_out,res)
    begin
        if res = '0' then
            -- normal behavior (loop)
            reg_in <= reg_out;
        else
            -- if reset, init with specified x0
            reg_in <= x0;
        end if;
    end process;

end Behavioral;