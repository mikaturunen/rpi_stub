/*
 * instr.c
 *
 *  Created on: Apr 15, 2015
 *      Author: jaa
 */

/*
 * Stuff needed for finding out where to place traps in single stepping
 */

#include <stdint.h>
#include "instr.h"
#include "rpi2.h"

#define INSTR_COND_MASK 0xf0000000
#define INSTR_COND_AL 0xe0000000
#define INSTR_COND_UNCOND 0xf0000000

// Instruction classification
#define INSTR_CLASS_MASK 0x0e000000
#define INSTR_C0 0x00000000
#define INSTR_C1 0x02000000
#define INSTR_C2 0x04000000
#define INSTR_C3 0x06000000
#define INSTR_C4 0x08000000
#define INSTR_C5 0x0a000000
#define INSTR_C6 0x0c000000
#define INSTR_C7 0x0e000000

// Instruction secondary classification
#define INSTR_SC_MASK 0x01800000
#define INSTR_SC_0 0x00000000
#define INSTR_SC_1 0x00800000
#define INSTR_SC_2 0x01000000
#define INSTR_SC_3 0x01800000

// This is frequently used for secondary classification too
#define INSTR_BIT4_MASK 0x00000010

// Extension to secondary classification
#define INSTR_DPI2_MASK 0x00600000
#define INSTR_DPI2_0 0x00000000
#define INSTR_DPI2_1 0x00200000
#define INSTR_DPI2_2 0x00400000
#define INSTR_DPI2_3 0x00600000


// linear doesn't have branch address

void check_op_pc(uint32_t instr, branch_info *info)
{
	// if dest is PC
	if ((instr & 0x0000f000) == 0x0000f000)
	{
		if ((instr & INSTR_COND_MASK) == INSTR_COND_AL)
		{
			info->btype = INSTR_BRTYPE_BRANCH;
			info->bvaltype = INSTR_BRVAL_NONE;
			info->bval = (unsigned int) 0;
			return;
		}
		else
		{
			info->btype = INSTR_BRTYPE_CONDBR;
			info->bvaltype = INSTR_BRVAL_NONE;
			info->bval = (unsigned int) 0;
			return;
		}
	}
	else
	{
		info->btype = INSTR_BRTYPE_LINEAR;
		info->bvaltype = INSTR_BRVAL_NONE;
		info->bval = (unsigned int) 0;
		return;
	}
}

void check_branching(unsigned int address, branch_info *info)
{

	uint32_t instr;

	// some scratchpads for various uses
	uint32_t tmp1;
	uint32_t tmp2;
	uint32_t tmp3;
	uint32_t tmp4;
	uint64_t dtmp;

	instr = *((uint32_t *) address);

	if ((instr & INSTR_COND_MASK) == INSTR_COND_UNCOND)
	{
		// check unconditionals (= specials)
		info->btype = INSTR_BRTYPE_BRANCH;
		info->bvaltype = INSTR_BRVAL_IMM;
		info->bval = (unsigned int) 0;
		return;
	}

	switch (instr & INSTR_CLASS_MASK)
	{
		case INSTR_C0:
			switch (instr & INSTR_SC_MASK)
			{
				case INSTR_SC_1:
					if (instr & INSTR_BIT4_MASK) // mult
					{
						tmp1 = instr & 0x00000f00;
						tmp1 = rpi2_reg_context.storage[tmp1];
						tmp2 = instr & 0x0000000f;
						tmp2 = rpi2_reg_context.storage[tmp2];
						dtmp = tmp1 * tmp2;
						// high dest is PC?
						if (instr & 0x000f0000)
						{
							info->btype = INSTR_BRTYPE_LINEAR;
							info->bvaltype = INSTR_BRVAL_NONE;
							info->bval = (unsigned int) (dtmp >> 32);
						}
						// low dest is PC?
						else if (instr & 0x0000f000)
						{
							info->btype = INSTR_BRTYPE_LINEAR;
							info->bvaltype = INSTR_BRVAL_NONE;
							info->bval = (unsigned int) (dtmp & 0xffffffff);
						}
						else
						{
							info->btype = INSTR_BRTYPE_LINEAR;
							info->bvaltype = INSTR_BRVAL_NONE;
							info->bval = (unsigned int) 0;
						}
						return;
					}
					else
					{
						// arithmetic & locig
						check_op_pc(instr, info);
						return;
					}
					break;
				case INSTR_SC_2:
					if (instr & INSTR_BIT4_MASK)
					{
						// swap or msr/mrs
						return INSTR_BRTYPE_LIN;
					}
					else
					{
						// arithmetic & locig
						check_op_pc(instr);
						return;
					}
					break;
				default:
						// arithmetic & locig
						check_op_pc(instr);
						return;
					break
			}
			break;
		case INSTR_C1:
			switch (instr & INSTR_SC_MASK)
			{
				case INSTR_SC_2:
					if (instr & INSTR_BIT4_MASK)
					{
						// msr imm
						return INSTR_BRTYPE_LIN;
					}
					else
					{
						// arithmetic & locig
						return check_op_pc(instr);
					}
					break;
				default:
						// arithmetic & locig
						return check_op_pc(instr);
					break
			}
			break;
		case INSTR_C2:
			// Single Data Transfer - imm
			break;
		case INSTR_C3:
			if (instr & INSTR_BIT4_MASK)
			{
				// Media instructions / undef
			}
			else
			{
				// Single Data Transfer - register
			}
			break;
		case INSTR_C4:
			// Block Data Transfer
			break;
		case INSTR_C5:
			// branch
			if ((instr & INSTR_COND_MASK) == INSTR_COND_AL)
			{
				return INSTR_BRTYPE_BRANCH;
			}
			else
			{
				return INSTR_BRTYPE_CONDB;
			}
			break;
		case INSTR_C6:
			// LDC/STC
			return INSTR_BRTYPE_LIN;
			break;
		case INSTR_C7:
			if (instr & 0x01000000)
			{
				// Software interrupt
				return INSTR_BRTYPE_NONE;
			}
			else
			{
				if (instr & INSTR_BIT4_MASK)
				{
					// MRC/MCR
				}
				else
				{
					// Co-processor data operations
					return INSTR_BRTYPE_LIN;
				}
			}
			break;
		}
}

