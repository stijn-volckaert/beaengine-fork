/* Copyright 2006-2009, BeatriX
 * File coded by BeatriX
 *
 * This file is part of BeaEngine.
 *
 *    BeaEngine is free software: you can redistribute it and/or modify
 *    it under the terms of the GNU Lesser General Public License as published by
 *    the Free Software Foundation, either version 3 of the License, or
 *    (at your option) any later version.
 *
 *    BeaEngine is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU Lesser General Public License for more details.
 *
 *    You should have received a copy of the GNU Lesser General Public License
 *    along with BeaEngine.  If not, see <http://www.gnu.org/licenses/>. */

/* ====================================================================
 *      0ffh
 * ==================================================================== */
void __bea_callspec__ G5_Ev(PDISASM pMyDisasm)
{
    GV.REGOPCODE = ((*((UInt8*)(UIntPtr) (GV.EIP_+1))) >> 3) & 0x7;
    if (GV.REGOPCODE == 0) {
        (*pMyDisasm).Instruction.Category = GENERAL_PURPOSE_INSTRUCTION+ARITHMETIC_INSTRUCTION;
        (*pMyDisasm).Instruction.MnemonicId = I_INC;
        #ifndef BEA_LIGHT_DISASSEMBLY
           (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "inc");
        #endif
        Ev(pMyDisasm);
        (*pMyDisasm).Argument1.AccessMode = READ+WRITE;
        FillFlags(pMyDisasm, EFLAGS_INC);
        if ((*pMyDisasm).Prefix.LockState == InvalidPrefix && (*pMyDisasm).Argument1.ArgType & MEMORY_TYPE) {
            (*pMyDisasm).Prefix.LockState = InUsePrefix;
        }
    }
    else if (GV.REGOPCODE == 1) {
        (*pMyDisasm).Instruction.Category = GENERAL_PURPOSE_INSTRUCTION+ARITHMETIC_INSTRUCTION;
        (*pMyDisasm).Instruction.MnemonicId = I_DEC;
        #ifndef BEA_LIGHT_DISASSEMBLY
           (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "dec");
        #endif
        Ev(pMyDisasm);
        (*pMyDisasm).Argument1.AccessMode = READ+WRITE;
        FillFlags(pMyDisasm, EFLAGS_DEC);
        if ((*pMyDisasm).Prefix.LockState == InvalidPrefix && (*pMyDisasm).Argument1.ArgType & MEMORY_TYPE) {
            (*pMyDisasm).Prefix.LockState = InUsePrefix;
        }
    }
    else if (GV.REGOPCODE == 2) {
        (*pMyDisasm).Instruction.Category = GENERAL_PURPOSE_INSTRUCTION+CONTROL_TRANSFER;
        (*pMyDisasm).Instruction.BranchType = CallType;
        (*pMyDisasm).Instruction.MnemonicId = I_CALL;
        #ifndef BEA_LIGHT_DISASSEMBLY
           (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "call");
        #endif
        if (GV.Architecture == 64) {
            GV.OperandSize = 64;
        }
        if (GV.OperandSize == 64) {
            GV.MemDecoration = Arg1qword;
        }
        else if (GV.OperandSize == 32) {
            GV.MemDecoration = Arg1dword;
        }
        else {
            GV.MemDecoration = Arg1word;
        }
        MOD_RM(&(*pMyDisasm).Argument1, pMyDisasm);
        (*pMyDisasm).Argument1.AccessMode = READ;
        GV.EIP_ += GV.DECALAGE_EIP+2;
        (*pMyDisasm).Instruction.ImplicitModifiedRegs = GENERAL_REG+REG4;
    }
    else if (GV.REGOPCODE == 3) {
        (*pMyDisasm).Instruction.Category = GENERAL_PURPOSE_INSTRUCTION+CONTROL_TRANSFER;
        (*pMyDisasm).Instruction.BranchType = CallType;
        (*pMyDisasm).Instruction.MnemonicId = I_CALL_FAR;
        if (GV.SYNTAX_ == ATSyntax) {
            #ifndef BEA_LIGHT_DISASSEMBLY
               (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "lcall");
            #endif
        }
        else {
            #ifndef BEA_LIGHT_DISASSEMBLY
               (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "call far");
            #endif
        }
        GV.MemDecoration = Arg1fword;
        MOD_RM(&(*pMyDisasm).Argument1, pMyDisasm);
        (*pMyDisasm).Argument1.AccessMode = READ;
        GV.EIP_ += GV.DECALAGE_EIP+2;
        (*pMyDisasm).Instruction.ImplicitModifiedRegs = GENERAL_REG+REG4;
    }
    else if (GV.REGOPCODE == 4) {
        (*pMyDisasm).Instruction.Category = GENERAL_PURPOSE_INSTRUCTION+CONTROL_TRANSFER;
        (*pMyDisasm).Instruction.BranchType = JmpType;
        (*pMyDisasm).Instruction.MnemonicId = I_JMP;
        #ifndef BEA_LIGHT_DISASSEMBLY
           (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "jmp");
        #endif
        if (GV.Architecture == 64) {
            GV.OperandSize = 64;
        }
        if (GV.OperandSize == 64) {
            GV.MemDecoration = Arg1qword;
        }
        else if (GV.OperandSize == 32) {
            GV.MemDecoration = Arg1dword;
        }
        else {
            GV.MemDecoration = Arg1word;
        }
        MOD_RM(&(*pMyDisasm).Argument1, pMyDisasm);
        (*pMyDisasm).Argument1.AccessMode = READ;
        GV.EIP_ += GV.DECALAGE_EIP+2;
    }
    else if (GV.REGOPCODE == 5) {
        (*pMyDisasm).Instruction.Category = GENERAL_PURPOSE_INSTRUCTION+CONTROL_TRANSFER;
        (*pMyDisasm).Instruction.BranchType = JmpType;
        (*pMyDisasm).Instruction.MnemonicId = I_JMP_FAR;
        if (GV.SYNTAX_ == ATSyntax) {
            #ifndef BEA_LIGHT_DISASSEMBLY
               (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "ljmp");
            #endif
        }
        else {
            #ifndef BEA_LIGHT_DISASSEMBLY
               (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "jmp far");
            #endif
        }
        GV.MemDecoration = Arg1fword;
        MOD_RM(&(*pMyDisasm).Argument1, pMyDisasm);
        (*pMyDisasm).Argument1.AccessMode = READ;
        GV.EIP_ += GV.DECALAGE_EIP+2;
    }
    else if (GV.REGOPCODE == 6) {
        (*pMyDisasm).Instruction.Category = GENERAL_PURPOSE_INSTRUCTION+DATA_TRANSFER;
        (*pMyDisasm).Instruction.MnemonicId = I_PUSH;
        #ifndef BEA_LIGHT_DISASSEMBLY
           (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "push");
        #endif
        if (GV.Architecture == 64) {
            GV.OperandSize = 64;
        }
        if (GV.OperandSize == 64) {
            GV.MemDecoration = Arg2qword;
        }
        else if (GV.OperandSize == 32) {
            GV.MemDecoration = Arg2dword;
        }
        else {
            GV.MemDecoration = Arg2word;
        }
        MOD_RM(&(*pMyDisasm).Argument2, pMyDisasm);
        GV.EIP_ += GV.DECALAGE_EIP+2;
        (*pMyDisasm).Argument1.ArgType = IMPLICIT_ARG+MEMORY_TYPE;
        (*pMyDisasm).Argument1.ArgSize = GV.OperandSize;
        (*pMyDisasm).Argument1.Memory.BaseRegister = REG4;
        (*pMyDisasm).Argument1.Memory.Displacement = -((Int32)(GV.Architecture >> 3));
        (*pMyDisasm).Instruction.ImplicitModifiedRegs = GENERAL_REG+REG4;
    }
    else {
        FailDecode(pMyDisasm);
    }
}

