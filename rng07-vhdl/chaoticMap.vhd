-- This block describes the chaotic map used for the random generator --

library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;

use work.randgen_package.all;

entity chaoticMap is
    Port ( clk : in std_logic;
        reset : in std_logic;
        output : out std_logic);
end chaoticMap;

architecture Behavioral of chaoticMap is

    -- Supposing 2 integer bits and two's complement, the constants 
    -- correspond to zero, one and minus one values
    constant zero : signed(N_BIT-1 downto 0) := (others => '0');
    constant one : signed(N_BIT-1 downto 0) := (N_BIT-2 => '1', others => '0');
    constant minusone : signed(N_BIT-1 downto 0) := (N_BIT-1 => '1', N_BIT-2 => '1', others => '0');
    
    -- Stores the current state
    signal reg : signed(N_BIT-1 downto 0);

begin

    -- update map
    proc_map: process(clk,reset)
    begin
        if reset = '0' then
            if rising_edge(clk) then
                -- 1.875 * reg  =  (2*reg) - (reg/8)  =  (reg<<1) - (reg>>3)
                if (reg < zero) then
                    -- reg = 1.875 * reg + 1
                    reg <= (( reg(N_BIT-2 downto 0) & '0' ) - ( "111" & reg(N_BIT-1 downto 3) )) + one;
                else
                    -- reg = 1.875 * reg - 1
                    reg <= (( reg(N_BIT-2 downto 0)&'0' ) - ( "000" & reg(N_BIT-1 downto 3) )) + minusone;
                end if;
            end if;
        else
            -- init
            reg <= X0;
        end if;
    end process;

    output <= reg(N_BIT-1);

end Behavioral;

