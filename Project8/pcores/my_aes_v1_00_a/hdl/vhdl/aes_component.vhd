library ieee;
use ieee.std_logic_1164.all;

entity SBOX_MEM is
  port(clk                : in std_logic;
       SBOX_MEM_ADDRESS_A : in integer range 0 to 255;
       SBOX_MEM_ADDRESS_B : in integer range 0 to 255;   
       SBOX_DATA_OUT_A    : out std_logic_vector(7 downto 0);
       SBOX_DATA_OUT_B    : out std_logic_vector(7 downto 0)
       );
end SBOX_MEM;

architecture beh of SBOX_MEM is
type tSBOX_MEM is array (0 to 255) of std_logic_vector(7 downto 0);
signal sSBOX_MEM : tSBOX_MEM :=
(x"63", x"7c", x"77", x"7b", x"f2", x"6b", x"6f", x"c5", x"30", x"01", x"67", x"2b", x"fe", x"d7", x"ab", x"76",
 x"ca", x"82", x"c9", x"7d", x"fa", x"59", x"47", x"f0", x"ad", x"d4", x"a2", x"af", x"9c", x"a4", x"72", x"c0", 
 x"b7", x"fd", x"93", x"26", x"36", x"3f", x"f7", x"cc", x"34", x"a5", x"e5", x"f1", x"71", x"d8", x"31", x"15",
 x"04", x"c7", x"23", x"c3", x"18", x"96", x"05", x"9a", x"07", x"12", x"80", x"e2", x"eb", x"27", x"b2", x"75", 
 x"09", x"83", x"2c", x"1a", x"1b", x"6e", x"5a", x"a0", x"52", x"3b", x"d6", x"b3", x"29", x"e3", x"2f", x"84", 
 x"53", x"d1", x"00", x"ed", x"20", x"fc", x"b1", x"5b", x"6a", x"cb", x"be", x"39", x"4a", x"4c", x"58", x"cf",
 x"d0", x"ef", x"aa", x"fb", x"43", x"4d", x"33", x"85", x"45", x"f9", x"02", x"7f", x"50", x"3c", x"9f", x"a8", 
 x"51", x"a3", x"40", x"8f", x"92", x"9d", x"38", x"f5", x"bc", x"b6", x"da", x"21", x"10", x"ff", x"f3", x"d2", 
 x"cd", x"0c", x"13", x"ec", x"5f", x"97", x"44", x"17", x"c4", x"a7", x"7e", x"3d", x"64", x"5d", x"19", x"73",
 x"60", x"81", x"4f", x"dc", x"22", x"2a", x"90", x"88", x"46", x"ee", x"b8", x"14", x"de", x"5e", x"0b", x"db", 
 x"e0", x"32", x"3a", x"0a", x"49", x"06", x"24", x"5c", x"c2", x"d3", x"ac", x"62", x"91", x"95", x"e4", x"79", 
 x"e7", x"c8", x"37", x"6d", x"8d", x"d5", x"4e", x"a9", x"6c", x"56", x"f4", x"ea", x"65", x"7a", x"ae", x"08",
 x"ba", x"78", x"25", x"2e", x"1c", x"a6", x"b4", x"c6", x"e8", x"dd", x"74", x"1f", x"4b", x"bd", x"8b", x"8a", 
 x"70", x"3e", x"b5", x"66", x"48", x"03", x"f6", x"0e", x"61", x"35", x"57", x"b9", x"86", x"c1", x"1d", x"9e", 
 x"e1", x"f8", x"98", x"11", x"69", x"d9", x"8e", x"94", x"9b", x"1e", x"87", x"e9", x"ce", x"55", x"28", x"df",
 x"8c", x"a1", x"89", x"0d", x"bf", x"e6", x"42", x"68", x"41", x"99", x"2d", x"0f", x"b0", x"54", x"bb", x"16");

begin

process(clk)
begin
  if clk'event and clk='1' then
    SBOX_DATA_OUT_A <= sSBOX_MEM(SBOX_MEM_ADDRESS_A);
    SBOX_DATA_OUT_B <= sSBOX_MEM(SBOX_MEM_ADDRESS_B);
  end if;
end process;
end architecture beh;

----------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use ieee.std_logic_unsigned.all;

library proc_common_v3_00_a;
use proc_common_v3_00_a.proc_common_pkg.all;

entity AES_component is
    port ( 
	        clk         : in  STD_LOGIC;
           AES_Control : in  STD_LOGIC_VECTOR (31 downto 0);
	        AES_Key     : in  STD_LOGIC_VECTOR (127 downto 0);
           AES_PT      : in  STD_LOGIC_VECTOR (127 downto 0);

           AES_CT      : out  STD_LOGIC_VECTOR (127 downto 0)
);
end AES_component;

architecture Behavioral of AES_component is

type   tKEY_MEM is array (0 to 15) of std_logic_vector(127 downto 0);
signal sKEY_MEM : tKEY_MEM;

component SBOX_MEM 
  port(clk                : in std_logic;
       SBOX_MEM_ADDRESS_A : in integer range 0 to 255;
       SBOX_MEM_ADDRESS_B : in integer range 0 to 255;   
       SBOX_DATA_OUT_A    : out std_logic_vector(7 downto 0);
       SBOX_DATA_OUT_B    : out std_logic_vector(7 downto 0)
       );
end component;

type tRcon is array (0 to 15) of std_logic_vector(7 downto 0);
constant cRcon	: tRcon := (x"01", x"02", x"04", x"08", x"10", x"20", x"40", x"80", x"1b", x"36", others => x"00");

type tREDUCE is array (0 to 3) of std_logic_vector(31 downto 0);
signal sREDUCE : tREDUCE;

type tREG is array (0 to 3) of std_logic_vector(31 downto 0);

signal sKEY_REG_128 : std_logic_vector(127 downto 0);

signal sKEY_REG, sPT_REG, sCT_STATE, sCT_AFTER_SBOX, sCT_AFTER_SHIFT_ROWS, sCT_AFTER_MIX_COL,
sCT_STATE_FIRST, sCT_STATE_MAIN, sCT_STATE_LAST, sXOR : tREG;

signal sROTATE   : std_logic_vector(31 downto 0);
signal sSBOX_out : std_logic_vector(31 downto 0);
signal sRcon_out : std_logic_vector(31 downto 0);

type   tstate is (idle, getKEY, getPT, encryptMAIN, encryptLAST, encryptDONE,  
                  keyEXP_1, keyEXP_2, keyEXP_DONE);
signal sstate : tstate := idle;

signal scount : integer range 0 to 15 := 0;

signal sKEY_EXP_CNT : integer range 0 to 15 := 0;
signal sENCRYPT_CNT : integer range 0 to 15 := 0;

signal sKEY_MEM_WRITE_ADDRESS : integer range 0 to 15;
signal sKEY_MEM_READ_ADDRESS  : integer range 0 to 15;

signal sKEY_MEM_WE           : std_logic;
signal sKEY_MEM_DATA_IN      : std_logic_vector (127 downto 0);
signal sKEY_MEM_DATA_OUT     : std_logic_vector (127 downto 0);

begin
----------------------------------------
process(clk)
begin
  if clk'event and clk='1' then
    case sstate is
	   when idle        => case AES_Control is
		                      when X"00000001" => sstate <= getKEY;
							       when X"00000010" => sstate <= getPT;
						          when others      => sstate <= idle; 	
                          end case;   
      when getKEY      => sstate <= keyEXP_1;  
		when keyEXP_1    => sstate <= keyEXP_2;
		when keyEXP_2    => if sKEY_EXP_CNT = 11 then
		                      sstate <= keyEXP_DONE;
							     else
							       sstate <= keyEXP_1;
							     end if;
      when keyEXP_DONE => if AES_CONTROL(0) = '0' then
		                      sstate <= idle;
                          end if;
		
      when getPT       => sstate <= encryptMAIN;
		
      when encryptMAIN  => if sKEY_MEM_READ_ADDRESS = 10 then
	                          sstate <= encryptLAST;
							      else  
							        sstate <= encryptMAIN;
							      end if;
	  
  	  when encryptLAST   => sstate <= encryptDONE;

     when encryptDONE   => if AES_CONTROL(1)= '0' then 
                              sstate <= idle;   
                            end if;		
		
		when others      => sstate <= idle;
    end case;
  end if;	 
end process;

--**********************************************
-- AES encrypt
------------------------------------------------
sKEY_MEM_READ_ADDRESS <= 0 when sstate=getPT else sENCRYPT_CNT+1;

process(clk)
begin
  if clk'event and clk='1' then
    case sstate is
	    when encryptMAIN  => sENCRYPT_CNT <= sENCRYPT_CNT +1;	      
		 when others       => sENCRYPT_CNT <= 0;
    end case;
  end if;
end process;

------------------------------------------------
-- Different steps for different rounds
------------------------------------------------

gen_STATE_FIRST: for i in 0 to 3 generate
  sCT_STATE_FIRST(i) <= sPT_REG(i) xor sKEY_MEM_DATA_OUT(31+(3-i)*32 downto (3-i)*32);
end generate;  

gen_STATE_MAIN: for i in 0 to 3 generate
  sCT_STATE_MAIN(i) <= sCT_AFTER_MIX_COL(i) xor sKEY_MEM_DATA_OUT(31+(3-i)*32 downto (3-i)*32);
end generate;  

gen_STATE_LAST: for i in 0 to 3 generate
  sCT_STATE_LAST(i) <= sCT_AFTER_SHIFT_ROWS(i) xor sKEY_MEM_DATA_OUT(31+(3-i)*32 downto (3-i)*32);
end generate;  

sCT_STATE <= sCT_STATE_FIRST when sENCRYPT_CNT = 0 else sCT_STATE_MAIN;

------------------------------------------------
-- State register update
------------------------------------------------

process(clk)
begin
  if clk'event and clk='1' then
    case sstate is
      when encryptLAST =>  AES_CT <= sCT_STATE_LAST(0)&sCT_STATE_LAST(1)&sCT_STATE_LAST(2)&sCT_STATE_LAST(3);
	   when others      =>  null;
    end case; 
  end if;
end process;

------------------------------------------------
-- SBOXs for encryption
------------------------------------------------

SBOX_ENCRYPT: for i in 0 to 3 generate

SBOX_1_0 : SBOX_MEM port map
         (clk               => clk,
          SBOX_MEM_ADDRESS_A => CONV_INTEGER(sCT_STATE(i)(31 downto 24)),
          SBOX_MEM_ADDRESS_B => CONV_INTEGER(sCT_STATE(i)(23 downto 16)),
          SBOX_DATA_OUT_A   => sCT_AFTER_SBOX(i)(31 downto 24),
          SBOX_DATA_OUT_B   => sCT_AFTER_SBOX(i)(23 downto 16));

SBOX_2_0 : SBOX_MEM port map
         (clk               => clk,
          SBOX_MEM_ADDRESS_A => CONV_INTEGER(sCT_STATE(i)(15 downto 8)),
          SBOX_MEM_ADDRESS_B => CONV_INTEGER(sCT_STATE(i)(7 downto 0)),
          SBOX_DATA_OUT_A   => sCT_AFTER_SBOX(i)(15 downto 8),
          SBOX_DATA_OUT_B   => sCT_AFTER_SBOX(i)(7 downto 0));

end generate;

------------------------------------------------
-- Shift rows
------------------------------------------------

sCT_AFTER_SHIFT_ROWS(0) <= sCT_AFTER_SBOX(0)(31 downto 24) & sCT_AFTER_SBOX(1)(23 downto 16) & 
                           sCT_AFTER_SBOX(2)(15 downto  8) & sCT_AFTER_SBOX(3) (7 downto  0);

sCT_AFTER_SHIFT_ROWS(1) <= sCT_AFTER_SBOX(1)(31 downto 24) & sCT_AFTER_SBOX(2)(23 downto 16) & 
                           sCT_AFTER_SBOX(3)(15 downto  8) & sCT_AFTER_SBOX(0) (7 downto  0);

sCT_AFTER_SHIFT_ROWS(2) <= sCT_AFTER_SBOX(2)(31 downto 24) & sCT_AFTER_SBOX(3)(23 downto 16) & 
                           sCT_AFTER_SBOX(0)(15 downto  8) & sCT_AFTER_SBOX(1) (7 downto  0);
                           
sCT_AFTER_SHIFT_ROWS(3) <= sCT_AFTER_SBOX(3)(31 downto 24) & sCT_AFTER_SBOX(0)(23 downto 16) & 
                           sCT_AFTER_SBOX(1)(15 downto  8) & sCT_AFTER_SBOX(2) (7 downto  0);

------------------------------------------------
-- Mix cols
------------------------------------------------


gen_MIX_COL: for i in 0 to 3 generate
						   
  sREDUCE(i)(31 downto 24)           <= X"1B" when ( (sCT_AFTER_SHIFT_ROWS(i)(31) xor sCT_AFTER_SHIFT_ROWS(i)(23)) ='1') else X"00"; 				 
  sCT_AFTER_MIX_COL(i)(31 downto 24) <= sCT_AFTER_SHIFT_ROWS(i)(30 downto 24) & '0' xor sCT_AFTER_SHIFT_ROWS(i)(22 downto 16) &
                                        '0' xor sCT_AFTER_SHIFT_ROWS(i)(23 downto 16) xor sCT_AFTER_SHIFT_ROWS(i)(15 downto 8) xor
                                        sCT_AFTER_SHIFT_ROWS(i)(7 downto 0) xor sREDUCE(i)(31 downto 24);

  sREDUCE(i)(23 downto 16)           <= X"1B" when ( (sCT_AFTER_SHIFT_ROWS(i)(23) xor sCT_AFTER_SHIFT_ROWS(i)(15)) ='1') else X"00"; 				 
  sCT_AFTER_MIX_COL(i)(23 downto 16) <= sCT_AFTER_SHIFT_ROWS(i)(31 downto 24) xor sCT_AFTER_SHIFT_ROWS(i)(22 downto 16) & 
                                        '0' xor sCT_AFTER_SHIFT_ROWS(i)(14 downto 8) & '0' xor sCT_AFTER_SHIFT_ROWS(i)(15 downto 8) xor
                                        sCT_AFTER_SHIFT_ROWS(i)(7 downto 0) xor sREDUCE(i)(23 downto 16);
									  
  sREDUCE(i)(15 downto 8)            <= X"1B" when ( (sCT_AFTER_SHIFT_ROWS(i)(15) xor sCT_AFTER_SHIFT_ROWS(i)(7)) ='1') else X"00"; 				 
  sCT_AFTER_MIX_COL(i)(15 downto 8)  <= sCT_AFTER_SHIFT_ROWS(i)(31 downto 24) xor sCT_AFTER_SHIFT_ROWS(i)(23 downto 16) xor 
                                        sCT_AFTER_SHIFT_ROWS(i)(14 downto 8) & '0' xor sCT_AFTER_SHIFT_ROWS(i)(6 downto 0) & 
                                        '0' xor sCT_AFTER_SHIFT_ROWS(i)(7 downto 0) xor sREDUCE(i)(15 downto 8);
					
  sREDUCE(i)(7 downto 0)             <= X"1B" when ( (sCT_AFTER_SHIFT_ROWS(i)(31) xor sCT_AFTER_SHIFT_ROWS(i)(7)) ='1') else X"00"; 				 
  sCT_AFTER_MIX_COL(i)(7 downto 0)   <= sCT_AFTER_SHIFT_ROWS(i)(30 downto 24) & '0' xor sCT_AFTER_SHIFT_ROWS(i)(31 downto 24) xor 
                                        sCT_AFTER_SHIFT_ROWS(i)(23 downto 16) xor sCT_AFTER_SHIFT_ROWS(i)(15 downto 8) xor 
                                        sCT_AFTER_SHIFT_ROWS(i)(6 downto 0) & '0' xor sREDUCE(i)(7 downto 0);
end generate;

--**********************************************
-- Key expansion
------------------------------------------------

process(clk)
begin
  if clk'event and clk='1' then
    case sstate is
	    when idle     => sKEY_EXP_CNT <= 0;
	    when keyExp_2 => sKEY_EXP_CNT <= sKEY_EXP_CNT +1;
       when others   => null;
      end case;
  end if;
end process;

sKEY_MEM_WRITE_ADDRESS <= 0 when sKEY_EXP_CNT = 0 else (sKEY_EXP_CNT-1);
sKEY_MEM_WE            <= '1' when sstate = keyExp_2 else '0';
sKEY_MEM_DATA_IN       <= sKEY_REG_128;

process(clk)
begin
  if clk'event and clk='1' then
    if sKEY_MEM_WE = '1' then
      sKEY_MEM(sKEY_MEM_WRITE_ADDRESS) <= sKEY_MEM_DATA_IN;
    end if;      
    sKEY_MEM_DATA_OUT <= sKEY_MEM(sKEY_MEM_READ_ADDRESS);
  end if;
end process; 

sROTATE <= sKEY_REG_128(23 downto 16)&sKEY_REG_128(15 downto 8)&
           sKEY_REG_128( 7 downto  0)&sKEY_REG_128(31 downto 24);   

SBOX_01: SBOX_MEM port map
       (clk               => clk,
        SBOX_MEM_ADDRESS_A => CONV_INTEGER(sROTATE (31 downto 24)),
        SBOX_MEM_ADDRESS_B => CONV_INTEGER(sROTATE (23 downto 16)), 
        SBOX_DATA_OUT_A   => sSBOX_out(31 downto 24),
        SBOX_DATA_OUT_B   => sSBOX_out(23 downto 16)
);

SBOX_02: SBOX_MEM port map
       (clk               => clk,
        SBOX_MEM_ADDRESS_A => CONV_INTEGER(sROTATE (15 downto 8)),
        SBOX_MEM_ADDRESS_B => CONV_INTEGER(sROTATE ( 7 downto 0)), 
        SBOX_DATA_OUT_A   => sSBOX_out(15 downto 8),
        SBOX_DATA_OUT_B   => sSBOX_out( 7 downto 0)
);

sRcon_out <= sSBOX_out xor (cRcon(sKEY_MEM_WRITE_ADDRESS) & X"000000");
	
sXOR(0)  <= sRcon_out xor sKEY_REG_128(127 downto 96);
sXOR(1)  <= sXOR(0)  xor sKEY_REG_128( 95 downto 64);
sXOR(2)  <= sXOR(1)  xor sKEY_REG_128( 63 downto 32);
sXOR(3)  <= sXOR(2)  xor sKEY_REG_128( 31 downto 0);
	
process(clk)
begin
  if clk'event and clk='1' then
   if sstate=keyExp_2 then
      case sKEY_EXP_CNT is
        when 0      => sKEY_REG_128 <= sKEY_REG(0)&sKEY_REG(1)&sKEY_REG(2)&sKEY_REG(3);
        when others => sKEY_REG_128 <= sXOR(0)&sXOR(1)&sXOR(2)&sXOR(3);   		  
    end case;
    end if; 
  END IF;  
end process;				

--**********************************************
-- getKey and getPT
------------------------------------------------

process(clk)
begin
  if clk'event and clk='1' then
    case sstate is
      when getKEY => for i in 0 to 3 loop 
		                   sKEY_REG(3-i) <= AES_Key(32*(i+1)-1 downto 32*i);  
							  end loop;	 
      when getPT  => for i in 0 to 3 loop 
		                   sPT_REG(3-i) <= AES_PT(32*(i+1)-1 downto 32*i);  
							  end loop;	 
		when others   => null;
    end case;
  end if;	 
end process;
----------------------------------------

end Behavioral;

