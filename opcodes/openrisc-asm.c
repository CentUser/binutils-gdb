/* Assembler interface for targets using CGEN. -*- C -*-
   CGEN: Cpu tools GENerator

THIS FILE IS MACHINE GENERATED WITH CGEN.
- the resultant file is machine generated, cgen-asm.in isn't

Copyright 1996, 1997, 1998, 1999, 2000, 2001 Free Software Foundation, Inc.

This file is part of the GNU Binutils and GDB, the GNU debugger.

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2, or (at your option)
any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software Foundation, Inc.,
59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */

/* ??? Eventually more and more of this stuff can go to cpu-independent files.
   Keep that in mind.  */

#include "sysdep.h"
#include <stdio.h>
#include "ansidecl.h"
#include "safe-ctype.h"
#include "bfd.h"
#include "symcat.h"
#include "openrisc-desc.h"
#include "openrisc-opc.h"
#include "opintl.h"
#include "xregex.h"
#include "libiberty.h"

#undef min
#define min(a,b) ((a) < (b) ? (a) : (b))
#undef max
#define max(a,b) ((a) > (b) ? (a) : (b))

static const char * parse_insn_normal
     PARAMS ((CGEN_CPU_DESC, const CGEN_INSN *, const char **, CGEN_FIELDS *));
long openrisc_sign_extend_16bit
     PARAMS ((long));
static const char * parse_hi16
     PARAMS ((CGEN_CPU_DESC, const char **, int, unsigned long *));
static const char * parse_lo16
     PARAMS ((CGEN_CPU_DESC, const char **, int, unsigned long *));
const char * openrisc_cgen_parse_operand
     PARAMS ((CGEN_CPU_DESC, int, const char **, CGEN_FIELDS *));

/* -- assembler routines inserted here */

/* -- asm.c */

#define CGEN_VERBOSE_ASSEMBLER_ERRORS

long
openrisc_sign_extend_16bit (value)
     long value;
{
  return (long) (short) value;
}


/* Handle hi().  */

static const char *
parse_hi16 (cd, strp, opindex, valuep)
     CGEN_CPU_DESC cd;
     const char **strp;
     int opindex;
     unsigned long *valuep;
{
  const char *errmsg;
  enum cgen_parse_operand_result result_type;
  bfd_vma value;

  if (**strp == '#')
    ++*strp;

  if (strncasecmp (*strp, "hi(", 3) == 0)
    {
      *strp += 3;

#if 0
      errmsg = cgen_parse_signed_integer (cd, strp, opindex, valuep);
      if (errmsg != NULL)
        fprintf (stderr, "parse_hi: %s\n", errmsg);
      if (errmsg != NULL)
#endif
        errmsg = cgen_parse_address (cd, strp, opindex, BFD_RELOC_HI16,
                                     &result_type, &value);
      if (**strp != ')')
        return "missing `)'";
      ++*strp;
      if (errmsg == NULL
          && result_type == CGEN_PARSE_OPERAND_RESULT_NUMBER)
        value >>= 16;
      *valuep = (long) (short) value;

      return errmsg;
    }
  else
    {
      if (**strp == '-')
        errmsg = cgen_parse_signed_integer (cd, strp, opindex, (long *) &value);
      else
        errmsg = cgen_parse_unsigned_integer (cd, strp, opindex, &value);
    }
  *valuep = (long) (short) (value & 0xffff);
  return errmsg;
}


/* Handle lo() */

static const char *
parse_lo16 (cd, strp, opindex, valuep)
     CGEN_CPU_DESC cd;
     const char **strp;
     int opindex;
     unsigned long *valuep;
{
  const char *errmsg;
  enum cgen_parse_operand_result result_type;
  bfd_vma value;

  if (**strp == '#')
    ++*strp;

  if (strncasecmp (*strp, "lo(", 3) == 0)
    {
      *strp += 3;

#if 0 
      errmsg = cgen_parse_signed_integer (cd, strp, opindex, valuep);
      if (errmsg != NULL)
        fprintf (stderr, "parse_lo: %s\n", errmsg);

      if (errmsg != NULL)
#endif
        errmsg = cgen_parse_address (cd, strp, opindex, BFD_RELOC_LO16,
                                     &result_type, &value);
      if (**strp != ')')
        return "missing `)'";
      ++*strp;
      if (errmsg == NULL
          && result_type == CGEN_PARSE_OPERAND_RESULT_NUMBER)
        value &= 0xffff;
      *valuep = (long) (short) value;

      return errmsg;
    }

  if (**strp == '-')
    errmsg = cgen_parse_signed_integer (cd, strp, opindex, (long *) &value);
  else
    errmsg = cgen_parse_unsigned_integer (cd, strp, opindex, &value);
  *valuep = (long) (short) (value & 0xffff);
  return errmsg;
}

/* -- */

/* Main entry point for operand parsing.

   This function is basically just a big switch statement.  Earlier versions
   used tables to look up the function to use, but
   - if the table contains both assembler and disassembler functions then
     the disassembler contains much of the assembler and vice-versa,
   - there's a lot of inlining possibilities as things grow,
   - using a switch statement avoids the function call overhead.

   This function could be moved into `parse_insn_normal', but keeping it
   separate makes clear the interface between `parse_insn_normal' and each of
   the handlers.
*/

const char *
openrisc_cgen_parse_operand (cd, opindex, strp, fields)
     CGEN_CPU_DESC cd;
     int opindex;
     const char ** strp;
     CGEN_FIELDS * fields;
{
  const char * errmsg = NULL;
  /* Used by scalar operands that still need to be parsed.  */
  long junk ATTRIBUTE_UNUSED;

  switch (opindex)
    {
    case OPENRISC_OPERAND_ABS_26 :
      {
        bfd_vma value;
        errmsg = cgen_parse_address (cd, strp, OPENRISC_OPERAND_ABS_26, 0, NULL,  & value);
        fields->f_abs26 = value;
      }
      break;
    case OPENRISC_OPERAND_DISP_26 :
      {
        bfd_vma value;
        errmsg = cgen_parse_address (cd, strp, OPENRISC_OPERAND_DISP_26, 0, NULL,  & value);
        fields->f_disp26 = value;
      }
      break;
    case OPENRISC_OPERAND_HI16 :
      errmsg = parse_hi16 (cd, strp, OPENRISC_OPERAND_HI16, &fields->f_simm16);
      break;
    case OPENRISC_OPERAND_LO16 :
      errmsg = parse_lo16 (cd, strp, OPENRISC_OPERAND_LO16, &fields->f_lo16);
      break;
    case OPENRISC_OPERAND_OP_F_23 :
      errmsg = cgen_parse_unsigned_integer (cd, strp, OPENRISC_OPERAND_OP_F_23, &fields->f_op4);
      break;
    case OPENRISC_OPERAND_OP_F_3 :
      errmsg = cgen_parse_unsigned_integer (cd, strp, OPENRISC_OPERAND_OP_F_3, &fields->f_op5);
      break;
    case OPENRISC_OPERAND_RA :
      errmsg = cgen_parse_keyword (cd, strp, & openrisc_cgen_opval_h_gr, & fields->f_r2);
      break;
    case OPENRISC_OPERAND_RB :
      errmsg = cgen_parse_keyword (cd, strp, & openrisc_cgen_opval_h_gr, & fields->f_r3);
      break;
    case OPENRISC_OPERAND_RD :
      errmsg = cgen_parse_keyword (cd, strp, & openrisc_cgen_opval_h_gr, & fields->f_r1);
      break;
    case OPENRISC_OPERAND_SIMM_16 :
      errmsg = cgen_parse_signed_integer (cd, strp, OPENRISC_OPERAND_SIMM_16, &fields->f_simm16);
      break;
    case OPENRISC_OPERAND_UI16NC :
      errmsg = parse_lo16 (cd, strp, OPENRISC_OPERAND_UI16NC, &fields->f_i16nc);
      break;
    case OPENRISC_OPERAND_UIMM_16 :
      errmsg = cgen_parse_unsigned_integer (cd, strp, OPENRISC_OPERAND_UIMM_16, &fields->f_uimm16);
      break;
    case OPENRISC_OPERAND_UIMM_5 :
      errmsg = cgen_parse_unsigned_integer (cd, strp, OPENRISC_OPERAND_UIMM_5, &fields->f_uimm5);
      break;

    default :
      /* xgettext:c-format */
      fprintf (stderr, _("Unrecognized field %d while parsing.\n"), opindex);
      abort ();
  }

  return errmsg;
}

cgen_parse_fn * const openrisc_cgen_parse_handlers[] = 
{
  parse_insn_normal,
};

void
openrisc_cgen_init_asm (cd)
     CGEN_CPU_DESC cd;
{
  openrisc_cgen_init_opcode_table (cd);
  openrisc_cgen_init_ibld_table (cd);
  cd->parse_handlers = & openrisc_cgen_parse_handlers[0];
  cd->parse_operand = openrisc_cgen_parse_operand;
}



/*
  Regex construction routine.

  This translates an opcode syntax string into a regex string,
  by replacing any non-character syntax element (such as an
  opcode) with the pattern '.*'

  It then compiles the regex and stores it in the opcode, for
  later use by openrisc_cgen_assemble_insn

  returns NULL for success, an error message for failure 
*/

char * 
openrisc_cgen_build_insn_regex (insn)
     CGEN_INSN *insn;
{  
  CGEN_OPCODE *opc = (CGEN_OPCODE *) CGEN_INSN_OPCODE (insn);
  const char *mnem = CGEN_INSN_MNEMONIC (insn);
  int mnem_len;
  char rxbuf[CGEN_MAX_RX_ELEMENTS];
  char *rx = rxbuf;
  const CGEN_SYNTAX_CHAR_TYPE *syn;
  int reg_err;

  syn = CGEN_SYNTAX_STRING (CGEN_OPCODE_SYNTAX (opc));

  /* Mnemonics come first in the syntax string  */
  if (! CGEN_SYNTAX_MNEMONIC_P (* syn)) return "missing mnemonic in syntax string";
  ++syn;

  /* copy the literal mnemonic out of the insn */
  memset (rx, 0, CGEN_MAX_RX_ELEMENTS);
  mnem_len = strlen(mnem);
  memcpy (rx, mnem, mnem_len);
  rx += mnem_len;

  /* copy any remaining literals from the syntax string into the rx */
  for(; * syn != 0 && rx < rxbuf + (CGEN_MAX_RX_ELEMENTS - 9); ++syn, ++rx) 
    {
      if (CGEN_SYNTAX_CHAR_P (* syn)) 
	{
	 char tmp = CGEN_SYNTAX_CHAR (* syn);
	 switch (tmp) 
           {
	     /* escape any regex metacharacters in the syntax */
	   case '.': case '[': case '\\': 
	   case '*': case '^': case '$': 

#ifdef CGEN_ESCAPE_EXTENDED_REGEX
	   case '?': case '{': case '}': 
	   case '(': case ')': case '*':
	   case '|': case '+': case ']':
#endif

	     * rx++ = '\\';
	     break;  
	   }
	 /* insert syntax char into rx */
	* rx = tmp;
	}
      else
	{
	  /* replace non-syntax fields with globs */
	  * rx = '.';
	  * ++rx = '*';
	}
    }

  /* trailing whitespace ok */
  * rx++ = '['; 
  * rx++ = ' '; 
  * rx++ = '\t'; 
  * rx++ = ']'; 
  * rx++ = '*'; 

  /* but anchor it after that */
  * rx++ = '$'; 
  * rx = '\0';

  CGEN_INSN_RX (insn) = xmalloc (sizeof (regex_t));
  reg_err = regcomp ((regex_t *) CGEN_INSN_RX (insn), rxbuf, REG_NOSUB|REG_ICASE);

  if (reg_err == 0) 
    return NULL;
  else
    {
      static char msg[80];
      regerror (reg_err, (regex_t *) CGEN_INSN_RX (insn), msg, 80);
      regfree ((regex_t *) CGEN_INSN_RX (insn));
      free (CGEN_INSN_RX (insn));
      (CGEN_INSN_RX (insn)) = NULL;
    return msg;
    }
}


/* Default insn parser.

   The syntax string is scanned and operands are parsed and stored in FIELDS.
   Relocs are queued as we go via other callbacks.

   ??? Note that this is currently an all-or-nothing parser.  If we fail to
   parse the instruction, we return 0 and the caller will start over from
   the beginning.  Backtracking will be necessary in parsing subexpressions,
   but that can be handled there.  Not handling backtracking here may get
   expensive in the case of the m68k.  Deal with later.

   Returns NULL for success, an error message for failure.
*/

static const char *
parse_insn_normal (cd, insn, strp, fields)
     CGEN_CPU_DESC cd;
     const CGEN_INSN *insn;
     const char **strp;
     CGEN_FIELDS *fields;
{
  /* ??? Runtime added insns not handled yet.  */
  const CGEN_SYNTAX *syntax = CGEN_INSN_SYNTAX (insn);
  const char *str = *strp;
  const char *errmsg;
  const char *p;
  const CGEN_SYNTAX_CHAR_TYPE * syn;
#ifdef CGEN_MNEMONIC_OPERANDS
  /* FIXME: wip */
  int past_opcode_p;
#endif

  /* For now we assume the mnemonic is first (there are no leading operands).
     We can parse it without needing to set up operand parsing.
     GAS's input scrubber will ensure mnemonics are lowercase, but we may
     not be called from GAS.  */
  p = CGEN_INSN_MNEMONIC (insn);
  while (*p && TOLOWER (*p) == TOLOWER (*str))
    ++p, ++str;

  if (* p)
    return _("unrecognized instruction");

#ifndef CGEN_MNEMONIC_OPERANDS
  if (* str && !ISSPACE (* str))
    return _("unrecognized instruction");
#endif

  CGEN_INIT_PARSE (cd);
  cgen_init_parse_operand (cd);
#ifdef CGEN_MNEMONIC_OPERANDS
  past_opcode_p = 0;
#endif

  /* We don't check for (*str != '\0') here because we want to parse
     any trailing fake arguments in the syntax string.  */
  syn = CGEN_SYNTAX_STRING (syntax);

  /* Mnemonics come first for now, ensure valid string.  */
  if (! CGEN_SYNTAX_MNEMONIC_P (* syn))
    abort ();

  ++syn;

  while (* syn != 0)
    {
      /* Non operand chars must match exactly.  */
      if (CGEN_SYNTAX_CHAR_P (* syn))
	{
	  /* FIXME: While we allow for non-GAS callers above, we assume the
	     first char after the mnemonic part is a space.  */
	  /* FIXME: We also take inappropriate advantage of the fact that
	     GAS's input scrubber will remove extraneous blanks.  */
	  if (TOLOWER (*str) == TOLOWER (CGEN_SYNTAX_CHAR (* syn)))
	    {
#ifdef CGEN_MNEMONIC_OPERANDS
	      if (CGEN_SYNTAX_CHAR(* syn) == ' ')
		past_opcode_p = 1;
#endif
	      ++ syn;
	      ++ str;
	    }
	  else if (*str)
	    {
	      /* Syntax char didn't match.  Can't be this insn.  */
	      static char msg [80];
	      /* xgettext:c-format */
	      sprintf (msg, _("syntax error (expected char `%c', found `%c')"),
		       CGEN_SYNTAX_CHAR(*syn), *str);
	      return msg;
	    }
	  else
	    {
	      /* Ran out of input.  */
	      static char msg [80];
	      /* xgettext:c-format */
	      sprintf (msg, _("syntax error (expected char `%c', found end of instruction)"),
		       CGEN_SYNTAX_CHAR(*syn));
	      return msg;
	    }
	  continue;
	}

      /* We have an operand of some sort.  */
      errmsg = openrisc_cgen_parse_operand (cd, CGEN_SYNTAX_FIELD (*syn),
					  &str, fields);
      if (errmsg)
	return errmsg;

      /* Done with this operand, continue with next one.  */
      ++ syn;
    }

  /* If we're at the end of the syntax string, we're done.  */
  if (* syn == 0)
    {
      /* FIXME: For the moment we assume a valid `str' can only contain
	 blanks now.  IE: We needn't try again with a longer version of
	 the insn and it is assumed that longer versions of insns appear
	 before shorter ones (eg: lsr r2,r3,1 vs lsr r2,r3).  */
      while (ISSPACE (* str))
	++ str;

      if (* str != '\0')
	return _("junk at end of line"); /* FIXME: would like to include `str' */

      return NULL;
    }

  /* We couldn't parse it.  */
  return _("unrecognized instruction");
}

/* Main entry point.
   This routine is called for each instruction to be assembled.
   STR points to the insn to be assembled.
   We assume all necessary tables have been initialized.
   The assembled instruction, less any fixups, is stored in BUF.
   Remember that if CGEN_INT_INSN_P then BUF is an int and thus the value
   still needs to be converted to target byte order, otherwise BUF is an array
   of bytes in target byte order.
   The result is a pointer to the insn's entry in the opcode table,
   or NULL if an error occured (an error message will have already been
   printed).

   Note that when processing (non-alias) macro-insns,
   this function recurses.

   ??? It's possible to make this cpu-independent.
   One would have to deal with a few minor things.
   At this point in time doing so would be more of a curiosity than useful
   [for example this file isn't _that_ big], but keeping the possibility in
   mind helps keep the design clean.  */

const CGEN_INSN *
openrisc_cgen_assemble_insn (cd, str, fields, buf, errmsg)
     CGEN_CPU_DESC cd;
     const char *str;
     CGEN_FIELDS *fields;
     CGEN_INSN_BYTES_PTR buf;
     char **errmsg;
{
  const char *start;
  CGEN_INSN_LIST *ilist;
  const char *parse_errmsg = NULL;
  const char *insert_errmsg = NULL;
  int recognized_mnemonic = 0;

  /* Skip leading white space.  */
  while (ISSPACE (* str))
    ++ str;

  /* The instructions are stored in hashed lists.
     Get the first in the list.  */
  ilist = CGEN_ASM_LOOKUP_INSN (cd, str);

  /* Keep looking until we find a match.  */

  start = str;
  for ( ; ilist != NULL ; ilist = CGEN_ASM_NEXT_INSN (ilist))
    {
      const CGEN_INSN *insn = ilist->insn;
      recognized_mnemonic = 1;

#ifdef CGEN_VALIDATE_INSN_SUPPORTED 
      /* not usually needed as unsupported opcodes shouldn't be in the hash lists */
      /* Is this insn supported by the selected cpu?  */
      if (! openrisc_cgen_insn_supported (cd, insn))
	continue;
#endif

      /* If the RELAX attribute is set, this is an insn that shouldn't be
	 chosen immediately.  Instead, it is used during assembler/linker
	 relaxation if possible.  */
      if (CGEN_INSN_ATTR_VALUE (insn, CGEN_INSN_RELAX) != 0)
	continue;

      str = start;

      /* skip this insn if str doesn't look right lexically */
      if (CGEN_INSN_RX (insn) != NULL &&
	  regexec ((regex_t *) CGEN_INSN_RX (insn), str, 0, NULL, 0) == REG_NOMATCH)
	continue;

      /* Allow parse/insert handlers to obtain length of insn.  */
      CGEN_FIELDS_BITSIZE (fields) = CGEN_INSN_BITSIZE (insn);

      parse_errmsg = CGEN_PARSE_FN (cd, insn) (cd, insn, & str, fields);
      if (parse_errmsg != NULL)
	continue;

      /* ??? 0 is passed for `pc' */
      insert_errmsg = CGEN_INSERT_FN (cd, insn) (cd, insn, fields, buf,
						 (bfd_vma) 0);
      if (insert_errmsg != NULL)
        continue;

      /* It is up to the caller to actually output the insn and any
         queued relocs.  */
      return insn;
    }

  {
    static char errbuf[150];
#ifdef CGEN_VERBOSE_ASSEMBLER_ERRORS
    const char *tmp_errmsg;

    /* If requesting verbose error messages, use insert_errmsg.
       Failing that, use parse_errmsg */
    tmp_errmsg = (insert_errmsg ? insert_errmsg :
		  parse_errmsg ? parse_errmsg :
		  recognized_mnemonic ? _("unrecognized form of instruction") :
		  _("unrecognized instruction"));

    if (strlen (start) > 50)
      /* xgettext:c-format */
      sprintf (errbuf, "%s `%.50s...'", tmp_errmsg, start);
    else 
      /* xgettext:c-format */
      sprintf (errbuf, "%s `%.50s'", tmp_errmsg, start);
#else
    if (strlen (start) > 50)
      /* xgettext:c-format */
      sprintf (errbuf, _("bad instruction `%.50s...'"), start);
    else 
      /* xgettext:c-format */
      sprintf (errbuf, _("bad instruction `%.50s'"), start);
#endif
      
    *errmsg = errbuf;
    return NULL;
  }
}

#if 0 /* This calls back to GAS which we can't do without care.  */

/* Record each member of OPVALS in the assembler's symbol table.
   This lets GAS parse registers for us.
   ??? Interesting idea but not currently used.  */

/* Record each member of OPVALS in the assembler's symbol table.
   FIXME: Not currently used.  */

void
openrisc_cgen_asm_hash_keywords (cd, opvals)
     CGEN_CPU_DESC cd;
     CGEN_KEYWORD *opvals;
{
  CGEN_KEYWORD_SEARCH search = cgen_keyword_search_init (opvals, NULL);
  const CGEN_KEYWORD_ENTRY * ke;

  while ((ke = cgen_keyword_search_next (& search)) != NULL)
    {
#if 0 /* Unnecessary, should be done in the search routine.  */
      if (! openrisc_cgen_opval_supported (ke))
	continue;
#endif
      cgen_asm_record_register (cd, ke->name, ke->value);
    }
}

#endif /* 0 */
