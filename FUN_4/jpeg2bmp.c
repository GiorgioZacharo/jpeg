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
/*
 * Copyright (C) 2008
 * Y. Hara, H. Tomiyama, S. Honda, H. Takada and K. Ishii
 * Nagoya University, Japan
 * All rights reserved.
 *
 * Disclaimer of Warranty
 *
 * These software programs are available to the user without any license fee or
 * royalty on an "as is" basis. The authors disclaims any and all warranties, 
 * whether express, implied, or statuary, including any implied warranties or 
 * merchantability or of fitness for a particular purpose. In no event shall the
 * copyright-holder be liable for any incidental, punitive, or consequential damages
 * of any kind whatsoever arising from the use of these programs. This disclaimer
 * of warranty extends to the user of these programs and user's customers, employees,
 * agents, transferees, successors, and assigns.
 *
 */
/*
 *  Transformation: JPEG -> BMP
 *  
 *  @(#) $Id: jpeg2bmp.c,v 1.2 2003/07/18 10:19:21 honda Exp $ 
 */

#include "init.h"
#include "global.h"

int
jpeg2bmp_main (unsigned char hana_jpg [JPEGSIZE], unsigned char JpegFileBuf[JPEG_FILE_SIZE], unsigned char OutData_comp_buf[RGB_NUM][BMP_OUT_SIZE], unsigned char hana_bmp [RGB_NUM][BMP_OUT_SIZE],
		int * main_result, int OutData_image_width, int out_width, int OutData_image_height, int out_length)
{
	int ci;
	unsigned char *c;
	int i, j;

	/*
	 * Store input data in buffer
	 */
	c = JpegFileBuf;
	for (i = 0; i < JPEGSIZE; i++)

	{
		ci = hana_jpg[i];
		*c++ = ci;
	}

	jpeg_read (JpegFileBuf, main_result,
			&i_marker,
			&p_jinfo_data_precision,
			&p_jinfo_image_height,
			&p_jinfo_image_width,
			&p_jinfo_num_components,
			out_length_get_sof,
			out_data_precision_get_sof,
			out_p_jinfo_image_height_get_sof,
			out_p_jinfo_image_width_get_sof,
			out_p_jinfo_num_components_get_sof,
			out_index_get_sof,
			out_id_get_sof,
			out_h_samp_factor_get_sof,
			out_v_samp_factor_get_sof,
			out_quant_tbl_no_get_sof,
			&i_get_sos,
			out_length_get_sos,
			out_num_comp_get_sos,
			out_comp_id_get_sos,
			out_dc_tbl_no_get_sos,
			out_ac_tbl_no_get_sos,
			&i_get_dht,
			out_length_get_dht,
			out_index_get_dht,
			out_count_get_dht,
			&i_get_dqt,
			out_length_get_dqt,
			out_prec_get_dht,
			out_num_get_dht,
			&p_jinfo_smp_fact,
			p_jinfo_comps_info_id,
			p_jinfo_comps_info_dc_tbl_no,
			p_jinfo_comps_info_ac_tbl_no,
			p_jinfo_jpeg_data,
			p_jinfo_ac_xhuff_tbl_bits,
			p_jinfo_ac_xhuff_tbl_huffval,
			p_jinfo_dc_xhuff_tbl_bits,
			p_jinfo_dc_xhuff_tbl_huffval,
			p_jinfo_quant_tbl_quantval,
			out_unread_marker,
			p_jinfo_comps_info_index,
			p_jinfo_comps_info_h_samp_factor,
			p_jinfo_comps_info_v_samp_factor,
			p_jinfo_comps_info_quant_tbl_no,
			&p_jinfo_MCUHeight, &p_jinfo_MCUWidth, &p_jinfo_NumMCU,
			p_jinfo_dc_dhuff_tbl_ml, p_jinfo_dc_dhuff_tbl_maxcode, p_jinfo_dc_dhuff_tbl_mincode, p_jinfo_dc_dhuff_tbl_valptr,
			p_jinfo_ac_dhuff_tbl_ml, p_jinfo_ac_dhuff_tbl_maxcode, p_jinfo_ac_dhuff_tbl_mincode, p_jinfo_ac_dhuff_tbl_valptr,
			&OutData_image_width, &OutData_image_height, OutData_comp_vpos, OutData_comp_hpos,
			CurHuffReadBuf, rgb_buf, OutData_comp_buf);

	for (i = 0; i < RGB_NUM; i++)
	{
		for (j = 0; j < BMP_OUT_SIZE; j++)
		{
			if (OutData_comp_buf[i][j] != hana_bmp[i][j])
			{
				main_result++;
			}
		}
	}
	if (OutData_image_width != out_width)
	{
		main_result++;
	}
	if (OutData_image_height != out_length)
	{
		main_result++;
	}
	return (0);
}
