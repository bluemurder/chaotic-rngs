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
     Port ( ck : in  STD_LOGIC;
           res : in  STD_LOGIC;
              ready : out STD_LOGIC;
           out0 : out  STD_LOGIC);
end CaosAlAl;

architecture Behavioral of CaosAlAl is
    
    -- Integer part is ALWAYS 2 bits
constant nbit : integer := 16;
constant skip : integer := 3;
    
    signal reg : signed(nbit-1 downto 0);
    signal counter : integer range 0 to skip := 0;
    -- Supposing 2 integer bits and two's complement, one and minus one values
    constant zero : signed(nbit-1 downto 0) := (others => '0');
    constant one : signed(nbit-1 downto 0) := (nbit-2 => '1', others => '0');
    constant minusone : signed(nbit-1 downto 0) := (nbit-1 => '1', nbit-2 => '1', others => '0');
    -- x0 = 0.5
    constant x0  : signed(nbit-1 downto 0) := (nbit-3 => '1', others => '0');
    
    function minimum (a,b : integer) return integer is
    begin
        if a < b then
            return a;
        else
           return b;
        end if;
    end function;
    
begin
    
    -- 1 when positive, 0 otherwise
    --out0 <= not(reg(nbit-1)) when rising_edge(ck) and counter = 0;
    out0 <= not(reg(nbit-1)) when rising_edge(ck); --and counter = skip;
    --ready <= '1' when counter = minimum(1,skip) else
    ready <= '1' when counter = skip else
                '0';

    proc_map: process(ck,res)
    begin
        if res = '0' then
            if (ck'event and ck ='1') then
                -- 1.875 * reg  =  (2*reg) - (reg/8)  =  (reg<<1) - (reg>>3)
                if (reg < zero) then
                    -- reg = 1.875 * reg + 1
                    reg <= (( reg(nbit-2 downto 0) & '0' ) - ( "111" & reg(nbit-1 downto 3) )) + one;
                else
                    -- reg = 1.875 * reg - 1
                    reg <= (( reg(nbit-2 downto 0)&'0' ) - ( "000" & reg(nbit-1 downto 3) )) + minusone;
                end if;
            end if;
        else
            -- init
            reg <= x0;
        end if;
    end process;

    proc_counter: process(ck,res,counter)
    begin
        if res = '1' then
            counter <= 0;
        elsif rising_edge(ck) then
            if counter = skip then
                counter <= 0;
            else
               counter <= counter+1;
            end if;
        end if;
    end process;

end Behavioral;
