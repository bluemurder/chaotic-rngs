--
--   Package File Template
--
--   Purpose: This package defines supplemental types, subtypes, 
--   constants, and functions 
--
--   To use any of the example code shown below, uncomment the lines and modify as necessary
--

library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_SIGNED.ALL; 
use ieee.std_logic_arith.all;

package variable_Caos is

constant numBit : integer :=32;
constant Val_init: real:= 0.5;
constant UNO: real:= 1.0;
constant Param: real:= 1.8;
--constant Param: real:= 0.125;
constant Nint: integer := 2;

constant scalamento:integer := numBit-Nint;

function convtosigned (val :   real) return std_logic_vector ;
function mult(k :  signed;
              x :  signed
               ) return integer;
end variable_Caos;

package body variable_Caos is

function convtosigned (val : real) return std_logic_vector  is 

variable temp       : integer;
variable uscita     : std_logic_vector(numBit-1 downto 0) :=  (others=>'0');
begin

    temp:=integer(val * real(2**(scalamento)));

    if temp = 0 then
        for i in 0 to numBit-1 loop
            uscita(i) := '0';
        end loop;

    else
    for i in 0 to  (scalamento) loop
        if( (temp -(2**((scalamento)- i))) > 0 )then
            temp := temp -(2**((scalamento)- i));
            uscita((scalamento)- i) := '1' ;
        elsif( (temp -(2**((scalamento)- i))) = 0 )then
            temp := temp -(2**((scalamento)- i));
            uscita((scalamento)- i) := '1' ;
        else
            uscita((scalamento)- i) := '0' ;
        end if;
    end loop;
    end if;
return uscita;
end function;
 
function mult(k :  signed;
              x :  signed
               ) return integer is

variable res: integer;
variable res1: integer;

begin

    res := ((2**(numBit-2))/(2**(numBit/2)))* (conv_integer(x)/(2**(numBit/2)));
    res1 := (2 * (2**(numBit - Nint - 3)))/( (2**(numBit/2)) ) * (conv_integer(x)/(2**(numBit/2)));

    res :=2*res-res1/2;
    res := (2**Nint) * res;

return res;

end function;
 
end variable_Caos;
