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
 *      0f01h
 * ==================================================================== */
void __bea_callspec__ G7_(PDISASM pMyDisasm)
{
    (*pMyDisasm).Instruction.Category = SYSTEM_INSTRUCTION;
    if (!Security1(pMyDisasm)) return;
    GV.REGOPCODE = ((*((UInt8*)(UIntPtr) (GV.EIP_))) >> 3) & 0x7;
    GV.MOD_= ((*((UInt8*)(UIntPtr) (GV.EIP_))) >> 6);
    GV.RM_  = (*((UInt8*)(UIntPtr) (GV.EIP_))) & 0x7;
    if (GV.REGOPCODE == 0) {
        if (GV.MOD_== 0x3) {
            if (GV.RM_ == 0x1) {
                (*pMyDisasm).Instruction.Category = VM_INSTRUCTION;
                (*pMyDisasm).Instruction.Mnemonic = I_VMCALL;
                GV.EIP_++;
            }
            else if (GV.RM_ == 0x2) {
                (*pMyDisasm).Instruction.Category = VM_INSTRUCTION;
                (*pMyDisasm).Instruction.Mnemonic = I_VMLAUNCH;
                GV.EIP_++;
            }
            else if (GV.RM_ == 0x3) {
                (*pMyDisasm).Instruction.Category = VM_INSTRUCTION;
                (*pMyDisasm).Instruction.Mnemonic = I_VMRESUME;
                GV.EIP_++;
            }
            else if (GV.RM_ == 0x4) {
                (*pMyDisasm).Instruction.Category = VM_INSTRUCTION;
                (*pMyDisasm).Instruction.Mnemonic = I_VMXOFF;
                GV.EIP_++;
            }
            else {
                FailDecode(pMyDisasm);
            }
        }
        else {
            MOD_RM(&(*pMyDisasm).Argument1, pMyDisasm);
            (*pMyDisasm).Argument1.ArgSize = 48;
            (*pMyDisasm).Instruction.Mnemonic = I_SGDT;
            (*pMyDisasm).Argument2.ArgType = IMPLICIT_ARG+REGISTER_TYPE+MEMORY_MANAGEMENT_REG+REG0;
            (*pMyDisasm).Argument2.ArgSize = 48;
            GV.EIP_+= GV.DECALAGE_EIP;
        }
    }
    else if (GV.REGOPCODE == 1) {
        if (GV.MOD_== 0x3) {
            if (GV.RM_ == 0x00) {
                (*pMyDisasm).Instruction.Category = SSE3_INSTRUCTION+AGENT_SYNCHRONISATION;
                (*pMyDisasm).Instruction.Mnemonic = I_MONITOR;
                GV.EIP_++;
            }
            else if (GV.RM_ == 0x01) {
                (*pMyDisasm).Instruction.Category = SSE3_INSTRUCTION+AGENT_SYNCHRONISATION;
                (*pMyDisasm).Instruction.Mnemonic = I_MWAIT;
                GV.EIP_++;
            }
            else {
                FailDecode(pMyDisasm);
            }
        }
        else {
            (*pMyDisasm).Argument1.ArgSize = 48;
            MOD_RM(&(*pMyDisasm).Argument1, pMyDisasm);
            (*pMyDisasm).Instruction.Category = SYSTEM_INSTRUCTION;
            (*pMyDisasm).Instruction.Mnemonic = I_SIDT;
            (*pMyDisasm).Argument2.ArgType = IMPLICIT_ARG+REGISTER_TYPE+MEMORY_MANAGEMENT_REG+REG2;
            (*pMyDisasm).Argument2.ArgSize = 48;
            GV.EIP_+= GV.DECALAGE_EIP;
        }
    }
    else if (GV.REGOPCODE == 2) {
        if (GV.MOD_== 0x3) {
            if (GV.RM_ == 0x0) {
                (*pMyDisasm).Instruction.Category = VM_INSTRUCTION;
                (*pMyDisasm).Instruction.Mnemonic = I_XGETBV;
                GV.EIP_++;
            }
            else if (GV.RM_ == 0x1) {
                (*pMyDisasm).Instruction.Category = VM_INSTRUCTION;
                (*pMyDisasm).Instruction.Mnemonic = I_XSETBV;
                GV.EIP_++;
            }
            else {
                FailDecode(pMyDisasm);
            }
        }
        else {
            (*pMyDisasm).Argument2.ArgSize = 48;
            MOD_RM(&(*pMyDisasm).Argument2, pMyDisasm);
            (*pMyDisasm).Instruction.Category = SYSTEM_INSTRUCTION;
            (*pMyDisasm).Instruction.Mnemonic = I_LGDT;
            (*pMyDisasm).Argument1.ArgType = IMPLICIT_ARG+REGISTER_TYPE+MEMORY_MANAGEMENT_REG+REG0;
            (*pMyDisasm).Argument1.ArgSize = 48;
            GV.EIP_+= GV.DECALAGE_EIP;
        }
    }
    else if (GV.REGOPCODE == 3) {
        if (GV.MOD_== 0x3) {
            if (GV.RM_ == 0x0) {
                (*pMyDisasm).Instruction.Category = VM_INSTRUCTION;
                (*pMyDisasm).Instruction.Mnemonic = I_VMRUN;
                GV.EIP_++;
            }
            else if (GV.RM_ == 0x1) {
                (*pMyDisasm).Instruction.Category = VM_INSTRUCTION;
                (*pMyDisasm).Instruction.Mnemonic = I_VMMCALL;
                GV.EIP_++;
            }
            else if (GV.RM_ == 0x2) {
                (*pMyDisasm).Instruction.Category = VM_INSTRUCTION;
                (*pMyDisasm).Instruction.Mnemonic = I_VMLOAD;
                GV.EIP_++;
            }
            else if (GV.RM_ == 0x3) {
                (*pMyDisasm).Instruction.Category = VM_INSTRUCTION;
                (*pMyDisasm).Instruction.Mnemonic = I_VMSAVE;
                GV.EIP_++;
            }
            else if (GV.RM_ == 0x4) {
                (*pMyDisasm).Instruction.Category = VM_INSTRUCTION;
                (*pMyDisasm).Instruction.Mnemonic = I_STGI;
                GV.EIP_++;
            }
            else if (GV.RM_ == 0x5) {
                (*pMyDisasm).Instruction.Category = VM_INSTRUCTION;
                (*pMyDisasm).Instruction.Mnemonic = I_CLGI;
                GV.EIP_++;
            }
            else if (GV.RM_ == 0x6) {
                (*pMyDisasm).Instruction.Category = VM_INSTRUCTION;
                (*pMyDisasm).Instruction.Mnemonic = I_SKINIT;
                GV.EIP_++;
            }
            else if (GV.RM_ == 0x7) {
                (*pMyDisasm).Instruction.Category = VM_INSTRUCTION;
                (*pMyDisasm).Instruction.Mnemonic = I_INVLPGA;
                GV.EIP_++;
            }
            else {
                FailDecode(pMyDisasm);
            }
        }
        else {
            MOD_RM(&(*pMyDisasm).Argument2, pMyDisasm);
            (*pMyDisasm).Argument2.ArgSize = 48;
            (*pMyDisasm).Instruction.Category = SYSTEM_INSTRUCTION;
            (*pMyDisasm).Instruction.Mnemonic = I_LIDT;
            (*pMyDisasm).Argument1.ArgType = IMPLICIT_ARG+REGISTER_TYPE+MEMORY_MANAGEMENT_REG+REG2;
            (*pMyDisasm).Argument1.ArgSize = 48;
            GV.EIP_+= GV.DECALAGE_EIP;
        }
    }

    else if (GV.REGOPCODE == 4) {
        MOD_RM(&(*pMyDisasm).Argument2, pMyDisasm);
        (*pMyDisasm).Argument2.ArgSize = 16;
        (*pMyDisasm).Instruction.Category = SYSTEM_INSTRUCTION;
        (*pMyDisasm).Instruction.Mnemonic = I_SMSW;
        (*pMyDisasm).Argument1.ArgType = IMPLICIT_ARG+REGISTER_TYPE+CR_REG+REG0;
        (*pMyDisasm).Argument1.ArgSize = 16;
        GV.EIP_+= GV.DECALAGE_EIP;
    }

    else if (GV.REGOPCODE == 6) {
        MOD_RM(&(*pMyDisasm).Argument1, pMyDisasm);
        (*pMyDisasm).Argument1.ArgSize = 16;
        (*pMyDisasm).Instruction.Category = SYSTEM_INSTRUCTION;
        (*pMyDisasm).Instruction.Mnemonic = I_LMSW;
        (*pMyDisasm).Argument2.ArgType = IMPLICIT_ARG+REGISTER_TYPE+CR_REG+REG0;
        (*pMyDisasm).Argument2.ArgSize = 16;
        GV.EIP_+= GV.DECALAGE_EIP;
    }
    else if (GV.REGOPCODE == 7) {
        if (GV.MOD_== 0x3) {
            if ((*pMyDisasm).Archi == 64) {
                if (GV.RM_ == 0x0) {
                    (*pMyDisasm).Instruction.Category = SYSTEM_INSTRUCTION;
                    (*pMyDisasm).Instruction.Mnemonic = I_SWAPGS;
                    GV.EIP_++;
                }
                else {
                    FailDecode(pMyDisasm);
                }
            }
            else {
                if (GV.RM_ == 0x1) {
                    (*pMyDisasm).Instruction.Category = SYSTEM_INSTRUCTION;
                    (*pMyDisasm).Instruction.Mnemonic = I_RDTSCP;
                    GV.EIP_++;
                }
                else {
                    FailDecode(pMyDisasm);
                }
            }
        }
        else {
            MOD_RM(&(*pMyDisasm).Argument2, pMyDisasm);
            (*pMyDisasm).Argument2.ArgSize = 8;
            (*pMyDisasm).Instruction.Category = SYSTEM_INSTRUCTION;
            (*pMyDisasm).Instruction.Mnemonic = I_INVLPG;
            GV.EIP_+= GV.DECALAGE_EIP;
        }
    }
    else {
        FailDecode(pMyDisasm);
    }


}

