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
 * Read the header information from buffer in JFIF format and begin decoding
 *
 *  @(#) $Id: jfif_read.c,v 1.2 2003/07/18 10:19:21 honda Exp $ 
 */

#include "decode.h"
#include "init.h"

/*
 * Initialize after reading markers
 */
void
jpeg_init_decompress (int * main_result, int * p_jinfo_MCUHeight, int * p_jinfo_MCUWidth, int * p_jinfo_NumMCU, short p_jinfo_image_height, short p_jinfo_image_width,
		int p_jinfo_dc_xhuff_tbl_bits[NUM_HUFF_TBLS][36], int p_jinfo_dc_dhuff_tbl_ml[NUM_HUFF_TBLS], int p_jinfo_dc_dhuff_tbl_maxcode[NUM_HUFF_TBLS][36], int p_jinfo_dc_dhuff_tbl_mincode[NUM_HUFF_TBLS][36], int p_jinfo_dc_dhuff_tbl_valptr[NUM_HUFF_TBLS][36],
		int p_jinfo_ac_xhuff_tbl_bits[NUM_HUFF_TBLS][36], int p_jinfo_ac_dhuff_tbl_ml[NUM_HUFF_TBLS], int p_jinfo_ac_dhuff_tbl_maxcode[NUM_HUFF_TBLS][36], int p_jinfo_ac_dhuff_tbl_mincode[NUM_HUFF_TBLS][36], int p_jinfo_ac_dhuff_tbl_valptr[NUM_HUFF_TBLS][36])
{
	int tmp;
	/*
	 * Get MCU number
	 */
	*p_jinfo_MCUHeight = (p_jinfo_image_height - 1) / 8 + 1;
	*p_jinfo_MCUWidth = (p_jinfo_image_width - 1) / 8 + 1;
	*p_jinfo_NumMCU = *p_jinfo_MCUHeight * *p_jinfo_MCUWidth;

	/*
	 * Create Huffman Table for decoding
	 */
	tmp = huff_make_dhuff_tb (&p_jinfo_dc_xhuff_tbl_bits[0][0],
			p_jinfo_dc_dhuff_tbl_ml[0],
			&p_jinfo_dc_dhuff_tbl_maxcode[0][0],
			&p_jinfo_dc_dhuff_tbl_mincode[0][0],
			&p_jinfo_dc_dhuff_tbl_valptr[0][0],
			main_result);
	p_jinfo_dc_dhuff_tbl_ml[0] = tmp;
	tmp = huff_make_dhuff_tb (&p_jinfo_dc_xhuff_tbl_bits[1][0],
			p_jinfo_dc_dhuff_tbl_ml[1],
			&p_jinfo_dc_dhuff_tbl_maxcode[1][0],
			&p_jinfo_dc_dhuff_tbl_mincode[1][0],
			&p_jinfo_dc_dhuff_tbl_valptr[1][0],
			main_result);
	p_jinfo_dc_dhuff_tbl_ml[1] = tmp;
	tmp = huff_make_dhuff_tb (&p_jinfo_ac_xhuff_tbl_bits[0][0],
			p_jinfo_ac_dhuff_tbl_ml[0],
			&p_jinfo_ac_dhuff_tbl_maxcode[0][0],
			&p_jinfo_ac_dhuff_tbl_mincode[0][0],
			&p_jinfo_ac_dhuff_tbl_valptr[0][0],
			main_result);
	p_jinfo_ac_dhuff_tbl_ml[0] = tmp;
	tmp = huff_make_dhuff_tb (&p_jinfo_ac_xhuff_tbl_bits[1][0],
			p_jinfo_ac_dhuff_tbl_ml[1],
			&p_jinfo_ac_dhuff_tbl_maxcode[1][0],
			&p_jinfo_ac_dhuff_tbl_mincode[1][0],
			&p_jinfo_ac_dhuff_tbl_valptr[1][0],
			main_result);
	p_jinfo_ac_dhuff_tbl_ml[1] = tmp;
}



void
jpeg_read (unsigned char read_buf[JPEG_FILE_SIZE], int * main_result,
		int * i_marker,
		char * p_jinfo_data_precision,
		short * p_jinfo_image_height,
		short * p_jinfo_image_width,
		char * p_jinfo_num_components,
		int out_length_get_sof,
		int out_data_precision_get_sof,
		int out_p_jinfo_image_height_get_sof,
		int out_p_jinfo_image_width_get_sof,
		int out_p_jinfo_num_components_get_sof,
		int out_index_get_sof[GET_SOF_REP],
		int out_id_get_sof[GET_SOF_REP],
		int out_h_samp_factor_get_sof[GET_SOF_REP],
		int out_v_samp_factor_get_sof[GET_SOF_REP],
		int out_quant_tbl_no_get_sof[GET_SOF_REP],
		int * i_get_sos,
		int out_length_get_sos,
		int out_num_comp_get_sos,
		int out_comp_id_get_sos[GET_SOS_REP],
		int out_dc_tbl_no_get_sos[GET_SOS_REP],
		int out_ac_tbl_no_get_sos[GET_SOS_REP],
		int * i_get_dht,
		int out_length_get_dht[GET_DHT_REP],
		int out_index_get_dht[GET_DHT_REP],
		int out_count_get_dht[GET_DHT_REP],
		int * i_get_dqt,
		int out_length_get_dqt[GET_DQT_REP],
		int out_prec_get_dht[GET_DQT_REP],
		int out_num_get_dht[GET_DQT_REP],
		int * p_jinfo_smp_fact,
		char p_jinfo_comps_info_id[NUM_COMPONENT],
		char p_jinfo_comps_info_dc_tbl_no[NUM_COMPONENT],
		char p_jinfo_comps_info_ac_tbl_no[NUM_COMPONENT],
		unsigned char p_jinfo_jpeg_data[JPEG_FILE_SIZE],
		int p_jinfo_ac_xhuff_tbl_bits[NUM_HUFF_TBLS][36],
		int p_jinfo_ac_xhuff_tbl_huffval[NUM_HUFF_TBLS][257],
		int p_jinfo_dc_xhuff_tbl_bits[NUM_HUFF_TBLS][36],
		int p_jinfo_dc_xhuff_tbl_huffval[NUM_HUFF_TBLS][257],
		unsigned int p_jinfo_quant_tbl_quantval[NUM_QUANT_TBLS][DCTSIZE2],
		int out_unread_marker[READ_MARKERS_REP],
		char p_jinfo_comps_info_index[NUM_COMPONENT],
		char p_jinfo_comps_info_h_samp_factor[NUM_COMPONENT],
		char p_jinfo_comps_info_v_samp_factor[NUM_COMPONENT],
		char p_jinfo_comps_info_quant_tbl_no[NUM_COMPONENT],
		int * p_jinfo_MCUHeight, int * p_jinfo_MCUWidth, int * p_jinfo_NumMCU,
		int p_jinfo_dc_dhuff_tbl_ml[NUM_HUFF_TBLS], int p_jinfo_dc_dhuff_tbl_maxcode[NUM_HUFF_TBLS][36], int p_jinfo_dc_dhuff_tbl_mincode[NUM_HUFF_TBLS][36], int p_jinfo_dc_dhuff_tbl_valptr[NUM_HUFF_TBLS][36],
		int p_jinfo_ac_dhuff_tbl_ml[NUM_HUFF_TBLS], int p_jinfo_ac_dhuff_tbl_maxcode[NUM_HUFF_TBLS][36], int p_jinfo_ac_dhuff_tbl_mincode[NUM_HUFF_TBLS][36], int p_jinfo_ac_dhuff_tbl_valptr[NUM_HUFF_TBLS][36],
		int * OutData_image_width, int * OutData_image_height, int OutData_comp_vpos[RGB_NUM], int OutData_comp_hpos[RGB_NUM],
		unsigned char CurHuffReadBuf[JPEG_FILE_SIZE], int rgb_buf[4][RGB_NUM][DCTSIZE2], unsigned char OutData_comp_buf[RGB_NUM][BMP_OUT_SIZE]){

	/*
	 * Read markers
	 */
	read_markers (read_buf, main_result,
			i_marker,
			p_jinfo_data_precision,
			p_jinfo_image_height,
			p_jinfo_image_width,
			p_jinfo_num_components,
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
			i_get_sos,
			out_length_get_sos,
			out_num_comp_get_sos,
			out_comp_id_get_sos,
			out_dc_tbl_no_get_sos,
			out_ac_tbl_no_get_sos,
			i_get_dht,
			out_length_get_dht,
			out_index_get_dht,
			out_count_get_dht,
			i_get_dqt,
			out_length_get_dqt,
			out_prec_get_dht,
			out_num_get_dht,
			p_jinfo_smp_fact,
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
			p_jinfo_comps_info_quant_tbl_no);


	/*
	 * Initialize the information used for decoding
	 */
	jpeg_init_decompress (main_result, p_jinfo_MCUHeight, p_jinfo_MCUWidth, p_jinfo_NumMCU, *p_jinfo_image_height, *p_jinfo_image_width,
			p_jinfo_dc_xhuff_tbl_bits, p_jinfo_dc_dhuff_tbl_ml, p_jinfo_dc_dhuff_tbl_maxcode, p_jinfo_dc_dhuff_tbl_mincode, p_jinfo_dc_dhuff_tbl_valptr,
			p_jinfo_ac_xhuff_tbl_bits, p_jinfo_ac_dhuff_tbl_ml, p_jinfo_ac_dhuff_tbl_maxcode, p_jinfo_ac_dhuff_tbl_mincode, p_jinfo_ac_dhuff_tbl_valptr);

	/*
	 * Start decoding
	 */
	//	decode_start (&OutData_image_width, &OutData_image_height,
	//			&OutData_comp_vpos[0], &OutData_comp_hpos[0], p_jinfo_quant_tbl_quantval, p_jinfo_comps_info_quant_tbl_no);
	decode_start(OutData_image_width, OutData_image_height,
			&OutData_comp_vpos[0], &OutData_comp_hpos[0],
			p_jinfo_quant_tbl_quantval, p_jinfo_comps_info_quant_tbl_no,
			CurHuffReadBuf, p_jinfo_jpeg_data, *p_jinfo_image_width, *p_jinfo_image_height, *p_jinfo_MCUWidth,
			*p_jinfo_smp_fact, *p_jinfo_NumMCU,
			p_jinfo_comps_info_dc_tbl_no, p_jinfo_dc_xhuff_tbl_huffval, p_jinfo_dc_dhuff_tbl_ml,
			p_jinfo_dc_dhuff_tbl_maxcode, p_jinfo_dc_dhuff_tbl_mincode, p_jinfo_dc_dhuff_tbl_valptr,
			rgb_buf, OutData_comp_buf, p_jinfo_ac_xhuff_tbl_huffval, p_jinfo_ac_dhuff_tbl_ml, p_jinfo_ac_dhuff_tbl_maxcode, p_jinfo_ac_dhuff_tbl_mincode, p_jinfo_ac_dhuff_tbl_valptr);
}
