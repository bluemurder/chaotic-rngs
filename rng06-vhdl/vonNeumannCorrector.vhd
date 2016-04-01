-- This block performs a Von Neumann correction --

library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

use work.randgen_package.all;

entity vonNeumannCorrector is
    Port ( clk : in std_logic;
        reset : in std_logic;
        data_in : in std_logic;
        ready_in : in std_logic;
        data_out : out std_logic;
        ready_out : out std_logic);
end vonNeumannCorrector;

architecture Behavioral of vonNeumannCorrector is

    signal counter : integer range 0 to 1;
    signal reg : std_logic_vector(1 downto 0);
    signal reg_xor : std_logic;

begin

    proc_load_register : process(clk,reset)
    begin
        if reset = '1' then
            reg <= (others => '0');
        elsif rising_edge(clk) and ready_in = '1' then
            reg(counter) <= data_in;
        end if;
    end process;
    
    proc_counter : process(clk,reset)
    begin
        if reset = '1' then
            counter <= 0;
        elsif rising_edge(clk) and ready_in = '1' then
            if counter = 0 then
                counter <= 1;
            else
                counter <= 0;
            end if;
        end if;
    end process;
    
    -- Xor between the two bits of reg
    reg_xor <= reg(0) xor reg(1);

    -- If the block is disabled, data_out equals data_in else
    -- it is the first bit of the sequence of two bits
    data_out <= data_in when ENABLE_VON_NEUMANN = false else
                    reg(0);
                    
    ready_out <= ready_in when ENABLE_VON_NEUMANN = false else
                 '1' when (counter = 1 and reg_xor = '1') else
                 '0';
    
end Behavioral;

