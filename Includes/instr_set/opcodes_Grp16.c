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
 *
 * ==================================================================== */
void __bea_callspec__ G16_(PDISASM pMyDisasm)
{
    GV.REGOPCODE = ((*((UInt8*)(UIntPtr) (GV.EIP_))) >> 3) & 0x7;
    if (GV.REGOPCODE == 0) {
        MOD_RM(&(*pMyDisasm).Argument2, pMyDisasm);
        if (GV.MOD_!= 0x3) {
            (*pMyDisasm).Argument2.ArgSize = 8;
            (*pMyDisasm).Instruction.Category = SSE_INSTRUCTION+CACHEABILITY_CONTROL;
            (*pMyDisasm).Instruction.Mnemonic = I_PREFETCHNTA;
        }
        else {
            FailDecode(pMyDisasm);
        }
    }
    else if (GV.REGOPCODE == 1) {
        MOD_RM(&(*pMyDisasm).Argument2, pMyDisasm);
        if (GV.MOD_!= 0x3) {
            (*pMyDisasm).Argument2.ArgSize = 8;
            (*pMyDisasm).Instruction.Category = SSE_INSTRUCTION+CACHEABILITY_CONTROL;
            (*pMyDisasm).Instruction.Mnemonic = I_PREFETCHT0;
        }
        else {
            FailDecode(pMyDisasm);
        }

    }
    else if (GV.REGOPCODE == 2) {
        MOD_RM(&(*pMyDisasm).Argument2, pMyDisasm);
        if (GV.MOD_!= 0x3) {
            (*pMyDisasm).Argument2.ArgSize = 8;
            (*pMyDisasm).Instruction.Category = SSE_INSTRUCTION+CACHEABILITY_CONTROL;
            (*pMyDisasm).Instruction.Mnemonic = I_PREFETCHT1;
        }
        else {
            FailDecode(pMyDisasm);
        }

    }
    else if (GV.REGOPCODE == 3) {
        MOD_RM(&(*pMyDisasm).Argument2, pMyDisasm);
        if (GV.MOD_!= 0x3) {
            (*pMyDisasm).Argument2.ArgSize = 8;
            (*pMyDisasm).Instruction.Category = SSE_INSTRUCTION+CACHEABILITY_CONTROL;
            (*pMyDisasm).Instruction.Mnemonic = I_PREFETCHT2;
        }
        else {
            FailDecode(pMyDisasm);
        }

    }

    else {
        FailDecode(pMyDisasm);
    }
    GV.EIP_+= GV.DECALAGE_EIP;
}
