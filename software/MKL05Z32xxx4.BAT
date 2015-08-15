SET PATH=C:\Keil_v5\ARM\ARMCC\Bin;C:\windows\system32;C:\windows;C:\windows\system32\wbem
SET CPU_TYPE=MKL05Z32xxx4
SET CPU_VENDOR=Freescale
SET UV2_TARGET=MKL05Z32xxx4
SET CPU_CLOCK=0x007A1200
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\uvbuild\cpu.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\uvbuild\events.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\uvbuild\pe_ldd.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\uvbuild\vectors.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\uvbuild\main.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\uvbuild\startup_arm_cc.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\uvbuild\bitioldd1.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\uvbuild\led1.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\uvbuild\ledpin1.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\uvbuild\wait1.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\uvbuild\da1.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\uvbuild\cs1.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\uvbuild\ti1.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\uvbuild\tu1.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\uvbuild\ax25.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmLink" --Via ".\UVBuild\kl05test.lnp"
"C:\Keil_v5\ARM\ARMCC\Bin\fromelf.exe" ".\UVBuild\kl05test.axf" --i32combined --output ".\UVBuild\kl05test.hex"
