/*
 * Copyright (c) 2004, Yannick Verschueren
 * Copyright (c) 2004,  Communications and remote sensing Laboratory, Universite catholique de Louvain, Belgium
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS `AS IS'
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

/*
 * Message Header JPT_stream Structure 
 *
 */
typedef struct {
  unsigned int Id;		/* In-class Identifier    */
  unsigned int last_byte;	/* Last byte information  */
  unsigned int Class_Id;	/* Class Identifier       */
  unsigned int CSn_Id;		/* CSn : index identifier */
  unsigned int Msg_offset;	/* Message offset         */
  unsigned int Msg_length;	/* Message length         */
  unsigned int Layer_nb;	/* Auxiliary for JPP case */
} jpt_msg_header_struct_t;

/*
 * Initialize the value of the message header structure 
 *
 * header : Message header structure
 *
 */
void jpt_init_Msg_Header(jpt_msg_header_struct_t * header);

/*
 * Read the message header for a JPP/JPT - stream
 *
 * header : Message header structure
 *
 */
void jpt_read_Msg_Header(jpt_msg_header_struct_t * header);