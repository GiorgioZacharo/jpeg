/*
+--------------------------------------------------------------------------+
| CHStone : a suite of benchmark programs for C-based High-Level Synthesis |
| ======================================================================== |
|                                                                          |
| * Collected and Modified : Y. Hara, H. Tomiyama, S. Honda,               |
|                            H. Takada and K. Ishii                        |
|                            Nagoya University, Japan                      |
|                                                                          |
| * Remark :                                                               |
|    1. This source code is modified to unify the formats of the benchmark |
|       programs in CHStone.                                               |
|    2. Test vectors are added for CHStone.                                |
|    3. If "main_result" is 0 at the end of the program, the program is    |
|       correctly executed.                                                |
|    4. Please follow the copyright of each benchmark program.             |
+--------------------------------------------------------------------------+
 */
/*************************************************************
Copyright (C) 1990, 1991, 1993 Andy C. Hung, all rights reserved.
PUBLIC DOMAIN LICENSE: Stanford University Portable Video Research
Group. If you use this software, you agree to the following: This
program package is purely experimental, and is licensed "as is".
Permission is granted to use, modify, and distribute this program
without charge for any purpose, provided this license/ disclaimer
notice appears in the copies.  No warranty or maintenance is given,
either expressed or implied.  In no event shall the author(s) be
liable to you or a third party for any special, incidental,
consequential, or other damages, arising out of the use or inability
to use the program for any purpose (or the loss of data), even if we
have been advised of such possibilities.  Any public reference or
advertisement of this source code should refer to it as the Portable
Video Research Group (PVRG) code, and not by any author(s) (or
Stanford University) name.
 *************************************************************/

/*
 ************************************************************
decode.c (original: transform.c)

This file contains the reference DCT, the zig-zag and quantization
algorithms.

 ************************************************************
 */
/*
 *  Decoder
 *
 *  @(#) $Id: decode.c,v 1.2 2003/07/18 10:19:21 honda Exp $
 */

#include "decode.h"
#include "init.h"
#include <stdio.h>
#include "/home/giorgio/gem5/util/m5/m5op.h"


//void ChenIDct (int *x, int *y);
void ChenIDct_f2r_ChenIDct (int x[DCTSIZE2], int y[DCTSIZE2]);

//const int zigzag_index[64] =	/* Is zig-zag map for matrix -> scan array */
//{ 0, 1, 5, 6, 14, 15, 27, 28,
//  2, 4, 7, 13, 16, 26, 29, 42,
//  3, 8, 12, 17, 25, 30, 41, 43,
//  9, 11, 18, 24, 31, 40, 44, 53,
//  10, 19, 23, 32, 39, 45, 52, 54,
//  20, 22, 33, 38, 46, 51, 55, 60,
//  21, 34, 37, 47, 50, 56, 59, 61,
//  35, 36, 48, 49, 57, 58, 62, 63
//};


/*
 * IZigzagMatrix() performs an inverse zig-zag translation on the
 * input imatrix and places the output in omatrix.
 */

void
DecodeHuffMCU(int out_buf[DCTSIZE2], int num_cmp, char p_jinfo_comps_info_dc_tbl_no[NUM_COMPONENT], int p_jinfo_dc_xhuff_tbl_huffval[NUM_HUFF_TBLS][257],
                int p_jinfo_dc_dhuff_tbl_ml[NUM_HUFF_TBLS], int p_jinfo_dc_dhuff_tbl_maxcode[NUM_HUFF_TBLS][36], int p_jinfo_dc_dhuff_tbl_mincode[NUM_HUFF_TBLS][36], int p_jinfo_dc_dhuff_tbl_valptr[NUM_HUFF_TBLS][36],
                unsigned char CurHuffReadBuf[JPEG_FILE_SIZE], int p_jinfo_ac_xhuff_tbl_huffval[NUM_HUFF_TBLS][257], int p_jinfo_ac_dhuff_tbl_ml[NUM_HUFF_TBLS], int p_jinfo_ac_dhuff_tbl_maxcode[NUM_HUFF_TBLS][36], int p_jinfo_ac_dhuff_tbl_mincode[NUM_HUFF_TBLS][36],
                int p_jinfo_ac_dhuff_tbl_valptr[NUM_HUFF_TBLS][36])
{

        int s, diff, tbl_no, *mptr, k, n, r;
        static unsigned int current_read_byte;
        static int read_position = -1;

        const int bit_set_mask[32] = {  /* This is 2^i at ith position */
                        0x00000001, 0x00000002, 0x00000004, 0x00000008,
                        0x00000010, 0x00000020, 0x00000040, 0x00000080,
                        0x00000100, 0x00000200, 0x00000400, 0x00000800,
                        0x00001000, 0x00002000, 0x00004000, 0x00008000,
                        0x00010000, 0x00020000, 0x00040000, 0x00080000,
                        0x00100000, 0x00200000, 0x00400000, 0x00800000,
                        0x01000000, 0x02000000, 0x04000000, 0x08000000,
                        0x10000000, 0x20000000, 0x40000000, 0x80000000
        };

        const static int extend_mask[20] = {
                        0xFFFFFFFE, 0xFFFFFFFC, 0xFFFFFFF8, 0xFFFFFFF0, 0xFFFFFFE0, 0xFFFFFFC0,
                        0xFFFFFF80, 0xFFFFFF00, 0xFFFFFE00, 0xFFFFFC00, 0xFFFFF800, 0xFFFFF000,
                        0xFFFFE000, 0xFFFFC000, 0xFFFF8000, 0xFFFF0000, 0xFFFE0000, 0xFFFC0000,
                        0xFFF80000, 0xFFF00000
        };
        /*
         * Decode DC
         */
        tbl_no = p_jinfo_comps_info_dc_tbl_no[num_cmp];
        s = DecodeHuffman (&p_jinfo_dc_xhuff_tbl_huffval[tbl_no][0],
                        p_jinfo_dc_dhuff_tbl_ml[tbl_no],
                        &p_jinfo_dc_dhuff_tbl_maxcode[tbl_no][0],
                        &p_jinfo_dc_dhuff_tbl_mincode[tbl_no][0],
                        &p_jinfo_dc_dhuff_tbl_valptr[tbl_no][0],
                        &main_result, &current_read_byte, &read_position,
                        CurHuffReadBuf);

        if (s)
        {
                diff = buf_getv (s, &current_read_byte, &read_position, CurHuffReadBuf);
                s--;
                if ((diff & bit_set_mask[s]) == 0)
                {
                        diff |= extend_mask[s];
                        diff++;
                }

                diff += *out_buf;               /* Change the last DC */
                *out_buf = diff;
        }

        /*
         * Decode AC
         */
        /* Set all values to zero */
        reg_14_a:for (mptr = out_buf + 1; mptr < out_buf + DCTSIZE2; mptr++)
        {
                *mptr = 0;
        }

        reg_14_b:for (k = 1; k < DCTSIZE2;)
  {                               /* JPEG Mistake */
                r = DecodeHuffman (&p_jinfo_ac_xhuff_tbl_huffval[tbl_no][0],
                                p_jinfo_ac_dhuff_tbl_ml[tbl_no],
                                &p_jinfo_ac_dhuff_tbl_maxcode[tbl_no][0],
                                &p_jinfo_ac_dhuff_tbl_mincode[tbl_no][0],
                                &p_jinfo_ac_dhuff_tbl_valptr[tbl_no][0],
                                &main_result, &current_read_byte, &read_position,
                                CurHuffReadBuf);

                s = r & 0xf;            /* Find significant bits */
                n = (r >> 4) & 0xf;     /* n = run-length */

                if (s)
                {
                        if ((k += n) >= DCTSIZE2)       /* JPEG Mistake */
                                break;
                        out_buf[k] = buf_getv (s, &current_read_byte, &read_position, CurHuffReadBuf);  /* Get s bits */
                        s--;                    /* Align s */
                        if ((out_buf[k] & bit_set_mask[s]) == 0)
                        {                       /* Also (1 << s) */
                                out_buf[k] |= extend_mask[s];   /* Also  (-1 << s) + 1 */
                                out_buf[k]++;   /* Increment 2's c */
                        }
                        k++;                    /* Goto next element */
                }
                else if (n == 15)               /* Zero run length code extnd */
                        k += 16;
                else
                {
                        break;
                }
        }
}
                                     

void IZigzagMatrix_f2r_forBody_s2e_forEnd(int imatrix[DCTSIZE2], int omatrix[DCTSIZE2]){
	int i;
	const int zigzag_index[64] =	/* Is zig-zag map for matrix -> scan array */
	{ 0, 1, 5, 6, 14, 15, 27, 28,
			2, 4, 7, 13, 16, 26, 29, 42,
			3, 8, 12, 17, 25, 30, 41, 43,
			9, 11, 18, 24, 31, 40, 44, 53,
			10, 19, 23, 32, 39, 45, 52, 54,
			20, 22, 33, 38, 46, 51, 55, 60,
			21, 34, 37, 47, 50, 56, 59, 61,
			35, 36, 48, 49, 57, 58, 62, 63
	};
	for (i = 0; i < DCTSIZE2; i++)
	{

		*(omatrix++) = imatrix[zigzag_index[i]];

	}
}
void
//IZigzagMatrix_f2r_IZigzagMatrix (int *imatrix, int *omatrix)
IZigzagMatrix_f2r_IZigzagMatrix (int imatrix[DCTSIZE2], int omatrix[DCTSIZE2])
{
	//	int i;

	//	const int zigzag_index[64] =	/* Is zig-zag map for matrix -> scan array */
	//	{ 0, 1, 5, 6, 14, 15, 27, 28,
	//			2, 4, 7, 13, 16, 26, 29, 42,
	//			3, 8, 12, 17, 25, 30, 41, 43,
	//			9, 11, 18, 24, 31, 40, 44, 53,
	//			10, 19, 23, 32, 39, 45, 52, 54,
	//			20, 22, 33, 38, 46, 51, 55, 60,
	//			21, 34, 37, 47, 50, 56, 59, 61,
	//			35, 36, 48, 49, 57, 58, 62, 63
	//	};
#ifdef REG_10
  m5_reset_stats(0,0);
	IZigzagMatrix_f2r_forBody_s2e_forEnd(imatrix, omatrix);
  m5_dumpreset_stats(0,0);
#else
	IZigzagMatrix_f2r_forBody_s2e_forEnd(imatrix, omatrix);
#endif
//	IZigzagMatrix_f2r_forBody_s2e_forEnd(imatrix, omatrix);


	//	for (i = 0; i < DCTSIZE2; i++)
	//
	//	{
	//
	//		*(omatrix++) = imatrix[zigzag_index[i]];
	//
	//	}
}


/*
 * IQuantize() takes an input matrix and does an inverse quantization
 * and puts the output int qmatrix.
 */

IQuantize_f2r_forBody_s2e_forEndLoopexit(int matrix[DCTSIZE2], unsigned int qmatrix[DCTSIZE2], int * mptr){
	for (mptr = matrix; mptr < matrix + DCTSIZE2; mptr++)
		{
			*mptr = *mptr * (*qmatrix);
			qmatrix++;
		}
}

void IQuantize_f2r_entry_s2e_forEnd(int matrix[DCTSIZE2], unsigned int qmatrix[DCTSIZE2]){
	int *mptr;
#ifdef REG_12
  m5_reset_stats(0,0);
	IQuantize_f2r_forBody_s2e_forEndLoopexit(matrix, qmatrix, mptr);
  m5_dumpreset_stats(0,0);
#else
	IQuantize_f2r_forBody_s2e_forEndLoopexit(matrix, qmatrix, mptr);
#endif
//	IQuantize_f2r_forBody_s2e_forEndLoopexit(matrix, qmatrix, mptr);


//	for (mptr = matrix; mptr < matrix + DCTSIZE2; mptr++)
//	{
//		*mptr = *mptr * (*qmatrix);
//		qmatrix++;
//	}
}

void
IQuantize_f2r_IQuantize (int matrix[DCTSIZE2], unsigned int qmatrix[DCTSIZE2])
{

#ifdef REG_13
  m5_reset_stats(0,0);
	IQuantize_f2r_entry_s2e_forEnd(matrix, qmatrix);
  m5_dumpreset_stats(0,0);
#else
	IQuantize_f2r_entry_s2e_forEnd(matrix, qmatrix);
#endif
//	IQuantize_f2r_entry_s2e_forEnd(matrix, qmatrix);



	//	int *mptr;
	//
	//	for (mptr = matrix; mptr < matrix + DCTSIZE2; mptr++)
	//	{
	//		*mptr = *mptr * (*qmatrix);
	//		qmatrix++;
	//	}
}


/*
 * PostshiftIDctMatrix() adds 128 (2048) to all 64 elements of an 8x8 matrix.
 * This results in strictly positive values for all pixel coefficients.
 */
void
PostshiftIDctMatrix (int matrix[DCTSIZE2], int shift)
{
	int *mptr;
	for (mptr = matrix; mptr < matrix + DCTSIZE2; mptr++)
	{
		*mptr += shift;
	}
}


/*
 * BoundIDctMatrix bounds the inverse dct matrix so that no pixel has a
 * value greater than 255 (4095) or less than 0.
 */
void  BoundIDctMatrix_f2r_forBody_s2e_forEnd(int matrix[DCTSIZE2], int Bound){
	int *mptr;

	for (mptr = matrix; mptr < matrix + DCTSIZE2; mptr++)
	{
		if (*mptr < 0)
		{
			*mptr = 0;
		}
		else if (*mptr > Bound)
		{
			*mptr = Bound;
		}
	}
}

void
BoundIDctMatrix_f2r_BoundIDctMatrix (int matrix[DCTSIZE2], int Bound)
{
	BoundIDctMatrix_f2r_forBody_s2e_forEnd(matrix, Bound);
	//	int *mptr;
	//
	//	for (mptr = matrix; mptr < matrix + DCTSIZE2; mptr++)
	//	{
	//		if (*mptr < 0)
	//		{
	//			*mptr = 0;
	//		}
	//		else if (*mptr > Bound)
	//		{
	//			*mptr = Bound;
	//		}
	//	}
}

void WriteOneBlock_f2r_ifThen7Us_s2e_forCond2ForEnd_crit_edgeUs(int store[DCTSIZE2], unsigned char out_buf[DCTSIZE2], int width, int hoffs, int diff){
	int e;
	for (e = hoffs; e < hoffs + DCTSIZE; e++)
	{
		if (e < width)
		{
			out_buf[diff + e] = (unsigned char) (*(store++));
		}
		else
		{
			break;
		}
	}
}

void WriteOneBlock_f2r_ifThenUs_s2e_forEnd13Loopexit(int store[DCTSIZE2], unsigned char out_buf[DCTSIZE2], int width, int height,
		int voffs, int hoffs ){

#ifdef REG_4
  m5_reset_stats(0,0);
        int i;
        //      int e;
        for (i = voffs; i < voffs + DCTSIZE; i++)
        {
                if (i < height)
                {
                        int diff;
                        diff = width * i;
                        WriteOneBlock_f2r_ifThen7Us_s2e_forCond2ForEnd_crit_edgeUs(store, out_buf, width, hoffs, diff);
                        //                      for (e = hoffs; e < hoffs + DCTSIZE; e++)
                        //                      {
                        //                              if (e < width)
                        //                              {
                        //                                      out_buf[diff + e] = (unsigned char) (*(store++));
                        //                              }
                        //                              else
                        //                              {
                        //                                      break;
                        //                              }
                        //                      }
                }
                else
                {
                        break;
                }
        }

  m5_dumpreset_stats(0,0);
#else
	int i;
	//	int e;
	for (i = voffs; i < voffs + DCTSIZE; i++)
	{
		if (i < height)
		{
			int diff;
			diff = width * i;
			WriteOneBlock_f2r_ifThen7Us_s2e_forCond2ForEnd_crit_edgeUs(store, out_buf, width, hoffs, diff);
			//			for (e = hoffs; e < hoffs + DCTSIZE; e++)
			//			{
			//				if (e < width)
			//				{
			//					out_buf[diff + e] = (unsigned char) (*(store++));
			//				}
			//				else
			//				{
			//					break;
			//				}
			//			}
		}
		else
		{
			break;
		}
	}
#endif

}

void WriteOneBlock_f2r_entry_s2e_forEnd13(int store[DCTSIZE2], unsigned char out_buf[DCTSIZE2], int width, int height,
		int voffs, int hoffs){
	int i, e;

//#ifdef REG_4
//  m5_reset_stats(0,0);
//	WriteOneBlock_f2r_ifThenUs_s2e_forEnd13Loopexit(store, out_buf, width, height, voffs, hoffs);
 // m5_dumpreset_stats(0,0);
//#else
	WriteOneBlock_f2r_ifThenUs_s2e_forEnd13Loopexit(store, out_buf, width, height, voffs, hoffs);
//#endif
	//WriteOneBlock_f2r_ifThenUs_s2e_forEnd13Loopexit(store, out_buf, width, height, voffs, hoffs);


	/* Find vertical buffer offs. */
	//	for (i = voffs; i < voffs + DCTSIZE; i++)
	//	{
	//		if (i < height)
	//		{
	//			int diff;
	//			diff = width * i;
	//			for (e = hoffs; e < hoffs + DCTSIZE; e++)
	//			{
	//				if (e < width)
	//				{
	//					out_buf[diff + e] = (unsigned char) (*(store++));
	//				}
	//				else
	//				{
	//					break;
	//				}
	//			}
	//		}
	//		else
	//		{
	//			break;
	//		}
	//	}
}

void
WriteOneBlock_f2r_WriteOneBlock (int store[DCTSIZE2], unsigned char out_buf[DCTSIZE2], int width, int height,
		int voffs, int hoffs)
{
	WriteOneBlock_f2r_entry_s2e_forEnd13(store, out_buf, width, height, voffs, hoffs);
	//	int i, e;
	//
	//
	//	/* Find vertical buffer offs. */
	//	for (i = voffs; i < voffs + DCTSIZE; i++)
	//	{
	//		if (i < height)
	//		{
	//			int diff;
	//			diff = width * i;
	//			for (e = hoffs; e < hoffs + DCTSIZE; e++)
	//			{
	//				if (e < width)
	//				{
	//					out_buf[diff + e] = (unsigned char) (*(store++));
	//				}
	//				else
	//				{
	//					break;
	//				}
	//			}
	//		}
	//		else
	//		{
	//			break;
	//		}
	//	}


}

/*
 * WriteBlock() writes an array of data in the integer array pointed to
 * by store out to the driver specified by the IOB.  The integer array is
 * stored in row-major form, that is, the first row of (8) elements, the
 * second row of (8) elements....
 * ONLY for MCU 1:1:1
 */
void
WriteBlock_f2r_WriteBlock (int store[DCTSIZE2], int *p_out_vpos, int *p_out_hpos,
		unsigned char p_out_buf[DCTSIZE2], short p_jinfo_image_width, short p_jinfo_image_height, int p_jinfo_MCUWidth)
{
	int voffs, hoffs;

	/*
	 * Get vertical offsets
	 */
	voffs = *p_out_vpos * DCTSIZE;
	hoffs = *p_out_hpos * DCTSIZE;

	/*
	 * Write block
	 */
	WriteOneBlock_f2r_WriteOneBlock (store,
			p_out_buf,
			p_jinfo_image_width, p_jinfo_image_height, voffs, hoffs);

	/*
	 *  Add positions
	 */
	(*p_out_hpos)++;
	(*p_out_vpos)++;

	if (*p_out_hpos < p_jinfo_MCUWidth)
	{
		(*p_out_vpos)--;
	}
	else
	{
		*p_out_hpos = 0;		/* If at end of image (width) */
	}
}

/*
 *  4:1:1
 */

void Write4Blocks_f2r_entry_s2e_WriteOneBlockExit(int store[DCTSIZE2], unsigned char out_buf[DCTSIZE2], int width, int height,
		int *voffs, int *hoffs, int *p_out_vpos, int *p_out_hpos){
	*voffs = *p_out_vpos * DCTSIZE;
	*hoffs = *p_out_hpos * DCTSIZE;
	WriteOneBlock_f2r_WriteOneBlock (store, out_buf,
			p_jinfo_image_width, p_jinfo_image_height, *voffs, *hoffs);
}

void Write4Blocks_f2r_WriteOneBlockExit_s2e_WriteOneBlockExit121(int store[DCTSIZE2], unsigned char out_buf[DCTSIZE2], int width, int height,
		int *voffs, int *hoffs){
	*hoffs += DCTSIZE;
	WriteOneBlock_f2r_WriteOneBlock (store, out_buf,
			p_jinfo_image_width, p_jinfo_image_height, *voffs, *hoffs);
}

void Write4Blocks_f2r_WriteOneBlockExit121_s2e_WriteOneBlockExit93(int store[DCTSIZE2], unsigned char out_buf[DCTSIZE2], int width, int height,
		int *voffs, int *hoffs){
	*voffs += DCTSIZE;
	*hoffs -= DCTSIZE;
	WriteOneBlock_f2r_WriteOneBlock (store, out_buf,
			p_jinfo_image_width, p_jinfo_image_height, *voffs, *hoffs);
}

void Write4Blocks_f2r_WriteOneBlockExit93_s2e_WriteOneBlockExit65(int store[DCTSIZE2], unsigned char out_buf[DCTSIZE2], int width, int height,
		int *voffs, int *hoffs){
	*hoffs += DCTSIZE;
	WriteOneBlock_f2r_WriteOneBlock (store,
			out_buf, p_jinfo_image_width, p_jinfo_image_height,
			*voffs, *hoffs);

}

void
Write4Blocks_f2r_Write4Blocks(int store1[DCTSIZE2], int store2[DCTSIZE2], int store3[DCTSIZE2], int store4[DCTSIZE2],
		int *p_out_vpos, int *p_out_hpos, unsigned char p_out_buf[DCTSIZE2],
		short p_jinfo_image_width, short p_jinfo_image_height, int p_jinfo_MCUWidth)
{
	int voffs, hoffs;

#ifdef REG_5
  m5_reset_stats(0,0);
	Write4Blocks_f2r_entry_s2e_WriteOneBlockExit(store1, p_out_buf, p_jinfo_image_width, p_jinfo_image_height, &voffs, &hoffs, p_out_vpos, p_out_hpos);
  m5_dumpreset_stats(0,0);
#else
	Write4Blocks_f2r_entry_s2e_WriteOneBlockExit(store1, p_out_buf, p_jinfo_image_width, p_jinfo_image_height, &voffs, &hoffs, p_out_vpos, p_out_hpos);
#endif

//	Write4Blocks_f2r_entry_s2e_WriteOneBlockExit(store1, p_out_buf, p_jinfo_image_width, p_jinfo_image_height, &voffs, &hoffs, p_out_vpos, p_out_hpos);


	/*
	 * OX
	 * XX
	 */
	//	voffs = *p_out_vpos * DCTSIZE;
	//	hoffs = *p_out_hpos * DCTSIZE;
	//	WriteOneBlock (store1, p_out_buf,
	//			p_jinfo_image_width, p_jinfo_image_height, voffs, hoffs);


	Write4Blocks_f2r_WriteOneBlockExit_s2e_WriteOneBlockExit121(store2, p_out_buf,
			p_jinfo_image_width, p_jinfo_image_height, &voffs, &hoffs);
	/*
	 * XO
	 * XX
	 */
	//	hoffs += DCTSIZE;
	//	WriteOneBlock (store2, p_out_buf,
	//			p_jinfo_image_width, p_jinfo_image_height, voffs, hoffs);

#ifdef REG_3
  m5_reset_stats(0,0);
	Write4Blocks_f2r_WriteOneBlockExit121_s2e_WriteOneBlockExit93(store3, p_out_buf, p_jinfo_image_width, p_jinfo_image_height, &voffs, &hoffs);
  m5_dumpreset_stats(0,0);
#else
	Write4Blocks_f2r_WriteOneBlockExit121_s2e_WriteOneBlockExit93(store3, p_out_buf, p_jinfo_image_width, p_jinfo_image_height, &voffs, &hoffs);
#endif
	//Write4Blocks_f2r_WriteOneBlockExit121_s2e_WriteOneBlockExit93(store3, p_out_buf, p_jinfo_image_width, p_jinfo_image_height, &voffs, &hoffs);




	/*
	 * XX
	 * OX
	 */
	//	voffs += DCTSIZE;
	//	hoffs -= DCTSIZE;
	//	WriteOneBlock (store3, p_out_buf,
	//			p_jinfo_image_width, p_jinfo_image_height, voffs, hoffs);

#ifdef REG_7
  m5_reset_stats(0,0);
	Write4Blocks_f2r_WriteOneBlockExit93_s2e_WriteOneBlockExit65(store4, p_out_buf, p_jinfo_image_width, p_jinfo_image_height, &voffs, &hoffs);
  m5_dumpreset_stats(0,0);
#else
	Write4Blocks_f2r_WriteOneBlockExit93_s2e_WriteOneBlockExit65(store4, p_out_buf, p_jinfo_image_width, p_jinfo_image_height, &voffs, &hoffs);
#endif
//	Write4Blocks_f2r_WriteOneBlockExit93_s2e_WriteOneBlockExit65(store4, p_out_buf, p_jinfo_image_width, p_jinfo_image_height, &voffs, &hoffs);
	
	/*
	 * XX
	 * XO
	 */
	//	hoffs += DCTSIZE;
	//	WriteOneBlock (store4,
	//			p_out_buf, p_jinfo_image_width, p_jinfo_image_height,
	//			voffs, hoffs);

	/*
	 * Add positions
	 */
	*p_out_hpos = *p_out_hpos + 2;
	*p_out_vpos = *p_out_vpos + 2;


	if (*p_out_hpos < p_jinfo_MCUWidth)
	{
		*p_out_vpos = *p_out_vpos - 2;
	}
	else
	{
		*p_out_hpos = 0;		/* If at end of image (width) */
	}
}

void YuvToRgb_f2r_forBody(int p, int y_buf[DCTSIZE2], int u_buf[DCTSIZE2], int v_buf[DCTSIZE2], int rgb_buf[4][RGB_NUM][DCTSIZE2],
		int * r, int * g, int * b, int * y, int * u, int * v, int i){
	*y = y_buf[i];
	*u = u_buf[i] - 128;
	*v = v_buf[i] - 128;

	*r = (*y * 256 + *v * 359 + 128) >> 8;
	*g = (*y * 256 - *u * 88 - *v * 182 + 128) >> 8;
	*b = (*y * 256 + *u * 454 + 128) >> 8;

	if (*r < 0)
		*r = 0;
	else if (*r > 255)
		*r = 255;

	if (*g < 0)
		*g = 0;
	else if (*g > 255)
		*g = 255;

	if (*b < 0)
		*b = 0;
	else if (*b > 255)
		*b = 255;

	rgb_buf[p][0][i] = *r;
	rgb_buf[p][1][i] = *g;
	rgb_buf[p][2][i] = *b;

}


void YuvToRgb_f2r_forBody_s2e_forEndLoopexit(int p, int y_buf[DCTSIZE2], int u_buf[DCTSIZE2], int v_buf[DCTSIZE2], int rgb_buf[4][RGB_NUM][DCTSIZE2],
		int * r, int * g, int * b, int * y, int * u, int * v){
	int i;

	for (i = 0; i < DCTSIZE2; i++)
	{
		YuvToRgb_f2r_forBody(p, y_buf, u_buf, v_buf, rgb_buf, r, g, b, y, u, v, i);
		//		*y = y_buf[i];
		//		*u = u_buf[i] - 128;
		//		*v = v_buf[i] - 128;
		//
		//		*r = (*y * 256 + *v * 359 + 128) >> 8;
		//		*g = (*y * 256 - *u * 88 - *v * 182 + 128) >> 8;
		//		*b = (*y * 256 + *u * 454 + 128) >> 8;
		//
		//		if (*r < 0)
		//			*r = 0;
		//		else if (*r > 255)
		//			*r = 255;
		//
		//		if (*g < 0)
		//			*g = 0;
		//		else if (*g > 255)
		//			*g = 255;
		//
		//		if (*b < 0)
		//			*b = 0;
		//		else if (*b > 255)
		//			*b = 255;
		//
		//		rgb_buf[p][0][i] = *r;
		//		rgb_buf[p][1][i] = *g;
		//		rgb_buf[p][2][i] = *b;

	}
}

void YuvToRgb_f2r_entry_s2e_forEnd(int p, int y_buf[DCTSIZE2], int u_buf[DCTSIZE2], int v_buf[DCTSIZE2], int rgb_buf[4][RGB_NUM][DCTSIZE2]){
	int r, g, b;
	int y, u, v;

#ifdef REG_9
  m5_reset_stats(0,0);
	YuvToRgb_f2r_forBody_s2e_forEndLoopexit(p, y_buf, u_buf, v_buf, rgb_buf, &r, &g, &b, &y, &u, &v);
  m5_dumpreset_stats(0,0);
#else
	YuvToRgb_f2r_forBody_s2e_forEndLoopexit(p, y_buf, u_buf, v_buf, rgb_buf, &r, &g, &b, &y, &u, &v);
#endif

	//YuvToRgb_f2r_forBody_s2e_forEndLoopexit(p, y_buf, u_buf, v_buf, rgb_buf, &r, &g, &b, &y, &u, &v);


	//	int i;
	//
	//	for (i = 0; i < DCTSIZE2; i++)
	//	{
	//		y = y_buf[i];
	//		u = u_buf[i] - 128;
	//		v = v_buf[i] - 128;
	//
	//		r = (y * 256 + v * 359 + 128) >> 8;
	//		g = (y * 256 - u * 88 - v * 182 + 128) >> 8;
	//		b = (y * 256 + u * 454 + 128) >> 8;
	//
	//		if (r < 0)
	//			r = 0;
	//		else if (r > 255)
	//			r = 255;
	//
	//		if (g < 0)
	//			g = 0;
	//		else if (g > 255)
	//			g = 255;
	//
	//		if (b < 0)
	//			b = 0;
	//		else if (b > 255)
	//			b = 255;
	//
	//		rgb_buf[p][0][i] = r;
	//		rgb_buf[p][1][i] = g;
	//		rgb_buf[p][2][i] = b;
	//
	//	}
}

/*
 * Transform from Yuv into RGB
 */
void
YuvToRgb_f2r_YuvToRgb (int p, int y_buf[DCTSIZE2], int u_buf[DCTSIZE2], int v_buf[DCTSIZE2], int rgb_buf[4][RGB_NUM][DCTSIZE2])
{
	YuvToRgb_f2r_entry_s2e_forEnd(p, y_buf, u_buf, v_buf, rgb_buf);
	//	int r, g, b;
	//	int y, u, v;
	//	int i;
	//
	//	for (i = 0; i < DCTSIZE2; i++)
	//	{
	//		y = y_buf[i];
	//		u = u_buf[i] - 128;
	//		v = v_buf[i] - 128;
	//
	//		r = (y * 256 + v * 359 + 128) >> 8;
	//		g = (y * 256 - u * 88 - v * 182 + 128) >> 8;
	//		b = (y * 256 + u * 454 + 128) >> 8;
	//
	//		if (r < 0)
	//			r = 0;
	//		else if (r > 255)
	//			r = 255;
	//
	//		if (g < 0)
	//			g = 0;
	//		else if (g > 255)
	//			g = 255;
	//
	//		if (b < 0)
	//			b = 0;
	//		else if (b > 255)
	//			b = 255;
	//
	//		rgb_buf[p][0][i] = r;
	//		rgb_buf[p][1][i] = g;
	//		rgb_buf[p][2][i] = b;
	//
	//	}
}


/*
 * Decode one block
 */

void decode_block_f2r_forBodyI_s2e_IZigzagMatrixExit(int comp_no, int HuffBuff[DCTSIZE2],
		char p_jinfo_comps_info_dc_tbl_no[NUM_COMPONENT], int p_jinfo_dc_xhuff_tbl_huffval[NUM_HUFF_TBLS][257],
		int p_jinfo_dc_dhuff_tbl_ml[NUM_HUFF_TBLS], int p_jinfo_dc_dhuff_tbl_maxcode[NUM_HUFF_TBLS][36], int p_jinfo_dc_dhuff_tbl_mincode[NUM_HUFF_TBLS][36], int p_jinfo_dc_dhuff_tbl_valptr[NUM_HUFF_TBLS][36],
		unsigned char CurHuffReadBuf[JPEG_FILE_SIZE], int p_jinfo_ac_xhuff_tbl_huffval[NUM_HUFF_TBLS][257], int p_jinfo_ac_dhuff_tbl_ml[NUM_HUFF_TBLS], int p_jinfo_ac_dhuff_tbl_maxcode[NUM_HUFF_TBLS][36], int p_jinfo_ac_dhuff_tbl_mincode[NUM_HUFF_TBLS][36],
int p_jinfo_ac_dhuff_tbl_valptr[NUM_HUFF_TBLS][36], int QuantBuff[DCTSIZE2]){

        DecodeHuffMCU (HuffBuff, comp_no, p_jinfo_comps_info_dc_tbl_no, p_jinfo_dc_xhuff_tbl_huffval,
                        p_jinfo_dc_dhuff_tbl_ml, p_jinfo_dc_dhuff_tbl_maxcode, p_jinfo_dc_dhuff_tbl_mincode, p_jinfo_dc_dhuff_tbl_valptr, CurHuffReadBuf,
                        p_jinfo_ac_xhuff_tbl_huffval, p_jinfo_ac_dhuff_tbl_ml, p_jinfo_ac_dhuff_tbl_maxcode, p_jinfo_ac_dhuff_tbl_mincode,
                        p_jinfo_ac_dhuff_tbl_valptr);

        IZigzagMatrix_f2r_IZigzagMatrix (HuffBuff, QuantBuff);


}

void decode_block_f2r_forBodyI11_s2e_BoundIDctMatrixExit(int out_buf[DCTSIZE2], int Bound){
	BoundIDctMatrix_f2r_BoundIDctMatrix (out_buf, Bound);
}


void
decode_block (int comp_no, int out_buf[DCTSIZE2], int HuffBuff[DCTSIZE2], unsigned int p_jinfo_quant_tbl_quantval[NUM_QUANT_TBLS][DCTSIZE2], char p_jinfo_comps_info_quant_tbl_no[NUM_COMPONENT],
		char p_jinfo_comps_info_dc_tbl_no[NUM_COMPONENT], int p_jinfo_dc_xhuff_tbl_huffval[NUM_HUFF_TBLS][257],
		int p_jinfo_dc_dhuff_tbl_ml[NUM_HUFF_TBLS], int p_jinfo_dc_dhuff_tbl_maxcode[NUM_HUFF_TBLS][36], int p_jinfo_dc_dhuff_tbl_mincode[NUM_HUFF_TBLS][36], int p_jinfo_dc_dhuff_tbl_valptr[NUM_HUFF_TBLS][36],
		unsigned char CurHuffReadBuf[JPEG_FILE_SIZE], int p_jinfo_ac_xhuff_tbl_huffval[NUM_HUFF_TBLS][257], int p_jinfo_ac_dhuff_tbl_ml[NUM_HUFF_TBLS], int p_jinfo_ac_dhuff_tbl_maxcode[NUM_HUFF_TBLS][36], int p_jinfo_ac_dhuff_tbl_mincode[NUM_HUFF_TBLS][36],
		int p_jinfo_ac_dhuff_tbl_valptr[NUM_HUFF_TBLS][36])
{
	int QuantBuff[DCTSIZE2];
	unsigned int *p_quant_tbl;


        decode_block_f2r_forBodyI_s2e_IZigzagMatrixExit(comp_no, HuffBuff, p_jinfo_comps_info_dc_tbl_no, p_jinfo_dc_xhuff_tbl_huffval,
                        p_jinfo_dc_dhuff_tbl_ml, p_jinfo_dc_dhuff_tbl_maxcode, p_jinfo_dc_dhuff_tbl_mincode, p_jinfo_dc_dhuff_tbl_valptr, CurHuffReadBuf,
                        p_jinfo_ac_xhuff_tbl_huffval, p_jinfo_ac_dhuff_tbl_ml, p_jinfo_ac_dhuff_tbl_maxcode, p_jinfo_ac_dhuff_tbl_mincode,
                        p_jinfo_ac_dhuff_tbl_valptr, QuantBuff);


	//		DecodeHuffMCU (HuffBuff, comp_no, p_jinfo_comps_info_dc_tbl_no, p_jinfo_dc_xhuff_tbl_huffval,
	//				p_jinfo_dc_dhuff_tbl_ml, p_jinfo_dc_dhuff_tbl_maxcode, p_jinfo_dc_dhuff_tbl_mincode, p_jinfo_dc_dhuff_tbl_valptr, CurHuffReadBuf,
	//				p_jinfo_ac_xhuff_tbl_huffval, p_jinfo_ac_dhuff_tbl_ml, p_jinfo_ac_dhuff_tbl_maxcode, p_jinfo_ac_dhuff_tbl_mincode,
	//				p_jinfo_ac_dhuff_tbl_valptrs);
	//
	//		IZigzagMatrix_f2r_IZigzagMatrix (HuffBuff, QuantBuff);

	p_quant_tbl =
			&p_jinfo_quant_tbl_quantval[(int)p_jinfo_comps_info_quant_tbl_no[comp_no]][DCTSIZE2];
	IQuantize_f2r_IQuantize (QuantBuff, p_quant_tbl);

	ChenIDct_f2r_ChenIDct (QuantBuff, out_buf);

	PostshiftIDctMatrix (out_buf, IDCT_SHIFT);

	#ifdef REG_11
 	 m5_reset_stats(0,0);
	decode_block_f2r_forBodyI11_s2e_BoundIDctMatrixExit(out_buf, IDCT_BOUNT);
 	 m5_dumpreset_stats(0,0);
	#else
	decode_block_f2r_forBodyI11_s2e_BoundIDctMatrixExit(out_buf, IDCT_BOUNT);
	#endif
	//decode_block_f2r_forBodyI11_s2e_BoundIDctMatrixExit(out_buf, IDCT_BOUNT);


	//	BoundIDctMatrix_f2r_BoundIDctMatrix (out_buf, IDCT_BOUNT);

}

void decode_start_f2r_vectorBody_s2e_YuvToRgbExit324(int i, int y_buf[DCTSIZE2], int u_buf[DCTSIZE2], int v_buf[DCTSIZE2], int rgb_buf[4][RGB_NUM][DCTSIZE2]){
	YuvToRgb_f2r_YuvToRgb (i, &y_buf[i], &u_buf[4], &v_buf[5], rgb_buf);
}

void decode_start_f2r_vectorPh_s2e_forBody96Preheader(int i, int y_buf[DCTSIZE2], int u_buf[DCTSIZE2], int v_buf[DCTSIZE2], int rgb_buf[4][RGB_NUM][DCTSIZE2]){
	for (i = 0; i < 4; (i)++)
	{

#ifdef REG_1
  m5_reset_stats(0,0);
		decode_start_f2r_vectorBody_s2e_YuvToRgbExit324(i, y_buf, u_buf, v_buf, rgb_buf);
  m5_dumpreset_stats(0,0);
#else
		decode_start_f2r_vectorBody_s2e_YuvToRgbExit324(i, y_buf, u_buf, v_buf, rgb_buf);
#endif
	//	decode_start_f2r_vectorBody_s2e_YuvToRgbExit324(i, y_buf, u_buf, v_buf, rgb_buf);
		//		YuvToRgb_f2r_YuvToRgb (*i, &y_buf[*i], &u_buf[4], &v_buf[5], rgb_buf);
	}
}

void
decode_start (int *out_data_image_width, int *out_data_image_height,
		int out_data_comp_vpos[RGB_NUM], int out_data_comp_hpos[RGB_NUM],
		unsigned int p_jinfo_quant_tbl_quantval[NUM_QUANT_TBLS][DCTSIZE2], char p_jinfo_comps_info_quant_tbl_no[NUM_COMPONENT],
		unsigned char CurHuffReadBuf[JPEG_FILE_SIZE], unsigned char p_jinfo_jpeg_data[JPEG_FILE_SIZE], short p_jinfo_image_width, short p_jinfo_image_height, int p_jinfo_MCUWidth,
		int p_jinfo_smp_fact, int p_jinfo_NumMCU,
		char p_jinfo_comps_info_dc_tbl_no[NUM_COMPONENT], int p_jinfo_dc_xhuff_tbl_huffval[NUM_HUFF_TBLS][257], int p_jinfo_dc_dhuff_tbl_ml[NUM_HUFF_TBLS],
		int p_jinfo_dc_dhuff_tbl_maxcode[NUM_HUFF_TBLS][36], int p_jinfo_dc_dhuff_tbl_mincode[NUM_HUFF_TBLS][36], int p_jinfo_dc_dhuff_tbl_valptr[NUM_HUFF_TBLS][36],
		int rgb_buf[4][RGB_NUM][DCTSIZE2], unsigned char OutData_comp_buf[RGB_NUM][BMP_OUT_SIZE], int p_jinfo_ac_xhuff_tbl_huffval[NUM_HUFF_TBLS][257], int p_jinfo_ac_dhuff_tbl_ml[NUM_HUFF_TBLS], int p_jinfo_ac_dhuff_tbl_maxcode[NUM_HUFF_TBLS][36], int p_jinfo_ac_dhuff_tbl_mincode[NUM_HUFF_TBLS][36],
		int p_jinfo_ac_dhuff_tbl_valptr[NUM_HUFF_TBLS][36])
{
	int i;
	int CurrentMCU = 0;
	int HuffBuff[NUM_COMPONENT][DCTSIZE2];
	int IDCTBuff[6][DCTSIZE2];

	/* Read buffer */
	CurHuffReadBuf = p_jinfo_jpeg_data;

	/*
	 * Initial value of DC element is 0
	 */
	for (i = 0; i < NUM_COMPONENT; i++)
	{
		HuffBuff[i][0] = 0;
	}

	/*
	 * Set the size of image to output buffer
	 */
	*out_data_image_width = p_jinfo_image_width;
	*out_data_image_height = p_jinfo_image_height;

	/*
	 * Initialize output buffer
	 */
	for (i = 0; i < RGB_NUM; i++)
	{
		out_data_comp_vpos[i] = 0;
		out_data_comp_hpos[i] = 0;
	}


	if (p_jinfo_smp_fact == SF1_1_1)
	{
		printf ("Decode 1:1:1 NumMCU = %d\n", p_jinfo_NumMCU);

		/*
		 * 1_1_1
		 */
		while (CurrentMCU < p_jinfo_NumMCU)
		{

			for (i = 0; i < NUM_COMPONENT; i++)
			{
				decode_block (i, IDCTBuff[i], HuffBuff[i], p_jinfo_quant_tbl_quantval, p_jinfo_comps_info_quant_tbl_no, p_jinfo_comps_info_dc_tbl_no,
						p_jinfo_dc_xhuff_tbl_huffval, p_jinfo_dc_dhuff_tbl_ml, p_jinfo_dc_dhuff_tbl_maxcode, p_jinfo_dc_dhuff_tbl_mincode, p_jinfo_dc_dhuff_tbl_valptr, CurHuffReadBuf,
						p_jinfo_ac_xhuff_tbl_huffval, p_jinfo_ac_dhuff_tbl_ml, p_jinfo_ac_dhuff_tbl_maxcode, p_jinfo_ac_dhuff_tbl_mincode, p_jinfo_ac_dhuff_tbl_valptr);
			}


			YuvToRgb_f2r_YuvToRgb (0, IDCTBuff[0], IDCTBuff[1], IDCTBuff[2], rgb_buf);
			/*
			 * Write
			 */
			for (i = 0; i < RGB_NUM; i++)
			{
				WriteBlock_f2r_WriteBlock (&rgb_buf[0][i][0],
						&out_data_comp_vpos[i],
						&out_data_comp_hpos[i], &OutData_comp_buf[i][0], p_jinfo_image_width, p_jinfo_image_height, p_jinfo_MCUWidth);
			}
			CurrentMCU++;
		}

	}
	else
	{
		printf ("Decode 4:1:1 NumMCU = %d\n", p_jinfo_NumMCU);
		/*
		 * 4_1_1
		 */
		while (CurrentMCU < p_jinfo_NumMCU)
		{
			/*
			 * Decode Y element
			 * Decoding Y, U and V elements should be sequentially conducted for the use of Huffman table
			 */

			for (i = 0; i < 4; i++)
			{
				decode_block (0, IDCTBuff[i], HuffBuff[0], p_jinfo_quant_tbl_quantval, p_jinfo_comps_info_quant_tbl_no, p_jinfo_comps_info_dc_tbl_no,
						p_jinfo_dc_xhuff_tbl_huffval, p_jinfo_dc_dhuff_tbl_ml, p_jinfo_dc_dhuff_tbl_maxcode, p_jinfo_dc_dhuff_tbl_mincode, p_jinfo_dc_dhuff_tbl_valptr, CurHuffReadBuf,
						p_jinfo_ac_xhuff_tbl_huffval, p_jinfo_ac_dhuff_tbl_ml, p_jinfo_ac_dhuff_tbl_maxcode, p_jinfo_ac_dhuff_tbl_mincode, p_jinfo_ac_dhuff_tbl_valptr);
			}

			/* Decode U */
			decode_block (1, IDCTBuff[4], HuffBuff[1], p_jinfo_quant_tbl_quantval, p_jinfo_comps_info_quant_tbl_no, p_jinfo_comps_info_dc_tbl_no,
					p_jinfo_dc_xhuff_tbl_huffval, p_jinfo_dc_dhuff_tbl_ml, p_jinfo_dc_dhuff_tbl_maxcode, p_jinfo_dc_dhuff_tbl_mincode, p_jinfo_dc_dhuff_tbl_valptr, CurHuffReadBuf,
					p_jinfo_ac_xhuff_tbl_huffval, p_jinfo_ac_dhuff_tbl_ml, p_jinfo_ac_dhuff_tbl_maxcode, p_jinfo_ac_dhuff_tbl_mincode, p_jinfo_ac_dhuff_tbl_valptr);

			/* Decode V */
			decode_block (2, IDCTBuff[5], HuffBuff[2], p_jinfo_quant_tbl_quantval, p_jinfo_comps_info_quant_tbl_no, p_jinfo_comps_info_dc_tbl_no,
					p_jinfo_dc_xhuff_tbl_huffval, p_jinfo_dc_dhuff_tbl_ml, p_jinfo_dc_dhuff_tbl_maxcode, p_jinfo_dc_dhuff_tbl_mincode, p_jinfo_dc_dhuff_tbl_valptr, CurHuffReadBuf,
					p_jinfo_ac_xhuff_tbl_huffval, p_jinfo_ac_dhuff_tbl_ml, p_jinfo_ac_dhuff_tbl_maxcode, p_jinfo_ac_dhuff_tbl_mincode, p_jinfo_ac_dhuff_tbl_valptr);


			/* Transform from Yuv into RGB */
		#ifdef REG_8
		  m5_reset_stats(0,0);
					decode_start_f2r_vectorPh_s2e_forBody96Preheader(i, IDCTBuff[i], IDCTBuff[4], IDCTBuff[5], rgb_buf);
		  m5_dumpreset_stats(0,0);
		#else
					decode_start_f2r_vectorPh_s2e_forBody96Preheader(i, IDCTBuff[i], IDCTBuff[4], IDCTBuff[5], rgb_buf);
		#endif
			//decode_start_f2r_vectorPh_s2e_forBody96Preheader(i, IDCTBuff[i], IDCTBuff[4], IDCTBuff[5], rgb_buf);

			//			for (i = 0; i < 4; i++)
			//			{
			//				YuvToRgb_f2r_YuvToRgb (i, IDCTBuff[i], IDCTBuff[4], IDCTBuff[5], rgb_buf);
			//			}


			for (i = 0; i < RGB_NUM; i++)
			{
				Write4Blocks_f2r_Write4Blocks (&rgb_buf[0][i][0],
						&rgb_buf[1][i][0],
						&rgb_buf[2][i][0],
						&rgb_buf[3][i][0],
						&out_data_comp_vpos[i],
						&out_data_comp_hpos[i], &OutData_comp_buf[i][0],
						p_jinfo_image_width, p_jinfo_image_height, p_jinfo_MCUWidth);
			}


			CurrentMCU += 4;
		}
	}
}
