--------------------------------------------------------------------------------
-- Company: 
-- Engineer:
--
-- Create Date:   11:39:26 05/05/2011
-- Design Name:   
-- Module Name:   C:/Marcin/CCLI_AppliedCryptography/CourseMaterials/Week81_XPS_CustomComponent/ppc1/pcores/my_aes_v1_00_a/devl/projnav/tb.vhd
-- Project Name:  my_aes
-- Target Device:  
-- Tool versions:  
-- Description:   
-- 
-- VHDL Test Bench Created by ISE for module: AES_component
-- 
-- Dependencies:
-- 
-- Revision:
-- Revision 0.01 - File Created
-- Additional Comments:
--
-- Notes: 
-- This testbench has been automatically generated using types std_logic and
-- std_logic_vector for the ports of the unit under test.  Xilinx recommends
-- that these types always be used for the top-level I/O of a design in order
-- to guarantee that the testbench will bind correctly to the post-implementation 
-- simulation model.
--------------------------------------------------------------------------------
LIBRARY ieee;
USE ieee.std_logic_1164.ALL;
 
-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--USE ieee.numeric_std.ALL;
 
ENTITY tb IS
END tb;
 
ARCHITECTURE behavior OF tb IS 
 
    -- Component Declaration for the Unit Under Test (UUT)
 
    COMPONENT AES_component
    PORT(
         clk : IN  std_logic;
         AES_Control : IN  std_logic_vector(31 downto 0);
         AES_Key : IN  std_logic_vector(127 downto 0);
         AES_PT : IN  std_logic_vector(127 downto 0);
         AES_CT : OUT  std_logic_vector(127 downto 0)
        );
    END COMPONENT;
    

   --Inputs
   signal clk : std_logic := '0';
   signal AES_Control : std_logic_vector(31 downto 0) := (others => '0');
   signal AES_Key : std_logic_vector(127 downto 0) := (others => '0');
   signal AES_PT : std_logic_vector(127 downto 0) := (others => '0');

 	--Outputs
   signal AES_CT : std_logic_vector(127 downto 0);

   -- Clock period definitions
   constant clk_period : time := 10 ns;
 
BEGIN
 
	-- Instantiate the Unit Under Test (UUT)
   uut: AES_component PORT MAP (
          clk => clk,
          AES_Control => AES_Control,
          AES_Key => AES_Key,
          AES_PT => AES_PT,
          AES_CT => AES_CT
        );

   -- Clock process definitions
   clk_process :process
   begin
		clk <= '0';
		wait for clk_period/2;
		clk <= '1';
		wait for clk_period/2;
   end process;
 

   -- Stimulus process
   stim_proc: process
   begin		
		AES_Control <= (others =>'0');
		AES_Key     <= (others =>'0');
		AES_PT      <= (others =>'0');
      wait for 20 ns;	
		
		AES_PT  <= X"3243f6a8_885a308d_313198a2_e0370734";
      AES_Key <= X"2b7e1516_28aed2a6_abf71588_09cf4f3c";

      AES_Control <= X"00000001";
		wait until rising_edge(clk);
      wait until rising_edge(clk);      
      AES_Control <= X"00000000";

      for i in 0 to 39 loop
		  wait until rising_edge(clk);
		end loop;

      AES_Control <= X"00000010";
		wait until rising_edge(clk);
      wait until rising_edge(clk);      
      AES_Control <= X"00000000";

      wait;
   end process;

END;
