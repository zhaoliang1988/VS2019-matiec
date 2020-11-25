/*
 *  matiec - a compiler for the programming languages defined in IEC 61131-3
 *
 *  Copyright (C) 2003-2011  Mario de Sousa (msousa@fe.up.pt)
 *  Copyright (C) 2007-2011  Laurent Bessard and Edouard Tisserant
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 *
 * This code is made available on the understanding that it will not be
 * used in safety-critical situations without a full and competent review.
 */

/*
 * An IEC 61131-3 compiler.
 *
 * Based on the
 * FINAL DRAFT - IEC 61131-3, 2nd Ed. (2001-12-10)
 *
 */


/*
 * This is one of the versions available for the 4th stage.
 *
 * This 4th stage generates a c source program equivalent
 * to the IL, ST and SFC code.
 */


/*
 * generate_c.HH
 */


#ifndef _generate_c_HH
#define _generate_c_HH



#include <string>
#include "../../absyntax/absyntax.hh"
#include "../../absyntax/visitor.hh"
#include "get_datatype_info.hh"
#include "search_var_instance_decl.hh"

 /***********************************************************************/
 /***********************************************************************/
 /***********************************************************************/
 /***********************************************************************/

 /* A helper class that analyses if the datatype of a variable is 'complex'. */
 /* 'complex' means that it is either a strcuture or an array!               */
class analyse_variable_c : public search_visitor_c {
private:
    static analyse_variable_c* singleton_;

public:
    analyse_variable_c(void) {};

    static bool is_complex_type(symbol_c* symbol) {
        if (NULL == symbol) ERROR;
        if (!get_datatype_info_c::is_type_valid(symbol->datatype)) return false;
        return (get_datatype_info_c::is_structure(symbol->datatype)
            || get_datatype_info_c::is_array(symbol->datatype)
            );
    }


private:
    symbol_c* last_fb, * first_non_fb_identifier;

public:
    /* returns the first element (from left to right) in a structured variable that is not a FB, i.e. is either a structure or an array! */
    /* eg:
     *      fb1.fb2.fb3.real       returns ??????
     *      fb1.fb2.struct1.real   returns struct1
     *      struct1.real           returns struct1
     */
    static symbol_c* find_first_nonfb(symbol_c* symbol) {
        if (NULL == singleton_)       singleton_ = new analyse_variable_c();
        if (NULL == singleton_)       ERROR;
        if (NULL == symbol)           ERROR;

        singleton_->last_fb = NULL;
        singleton_->first_non_fb_identifier = NULL;
        return (symbol_c*)symbol->accept(*singleton_);
    }

    /* returns true if a strcutured variable (e.g. fb1.fb2.strcut1.real) contains a structure or array */
    /* eg:
     *      fb1.fb2.fb3.real       returns FALSE
     *      fb1.fb2.struct1.real   returns TRUE
     *      struct1.real           returns TRUE
     */
    static bool contains_complex_type(symbol_c* symbol) {
        if (NULL == symbol) ERROR;
        if (!get_datatype_info_c::is_type_valid(symbol->datatype)) ERROR;

        symbol_c* first_non_fb = (symbol_c*)find_first_nonfb(symbol);
        return is_complex_type(first_non_fb->datatype);
    }


    /* returns the datatype of the variable returned by find_first_nonfb() */
    /* eg:
     *      fb1.fb2.fb3.real       returns ??????
     *      fb1.fb2.struct1.real   returns datatype of struct1
     *      struct1.real           returns datatype of struct1
     */
    static search_var_instance_decl_c::vt_t first_nonfb_vardecltype(symbol_c* symbol, symbol_c* scope) {
        if (NULL == symbol) ERROR;
        if (!get_datatype_info_c::is_type_valid(symbol->datatype)) ERROR;

        symbol_c* first_non_fb = (symbol_c*)find_first_nonfb(symbol);
        if (NULL != singleton_->last_fb) {
            scope = singleton_->last_fb->datatype;
            symbol = singleton_->first_non_fb_identifier;
        }

        search_var_instance_decl_c search_var_instance_decl(scope);

        return search_var_instance_decl.get_vartype(symbol);
    }


    /*********************/
    /* B 1.4 - Variables */
    /*********************/
    void* visit(symbolic_variable_c* symbol) {
        if (!get_datatype_info_c::is_type_valid(symbol->datatype)) ERROR;
        if (!get_datatype_info_c::is_function_block(symbol->datatype)) {
            first_non_fb_identifier = symbol;
            return (void*)symbol;
        }
        last_fb = symbol;
        return NULL;
    }

    /*************************************/
    /* B.1.4.2   Multi-element Variables */
    /*************************************/

    // SYM_REF2(structured_variable_c, record_variable, field_selector)
    void* visit(structured_variable_c* symbol) {
        symbol_c* res = (symbol_c*)symbol->record_variable->accept(*this);
        if (NULL != res) return res;

        if (!get_datatype_info_c::is_type_valid(symbol->datatype)) ERROR;
        if (!get_datatype_info_c::is_function_block(symbol->datatype)) {
            first_non_fb_identifier = symbol->field_selector;
            return (void*)symbol;
        }

        last_fb = symbol;
        return NULL;
    }

    /*  subscripted_variable '[' subscript_list ']' */
    //SYM_REF2(array_variable_c, subscripted_variable, subscript_list)
    void* visit(array_variable_c* symbol) {
        void* res = symbol->subscripted_variable->accept(*this);
        if (NULL != res) return res;
        return (void*)symbol;
    }


};

analyse_variable_c* analyse_variable_c::singleton_ = NULL;

/***********************************************************************/
/***********************************************************************/
/***********************************************************************/
/***********************************************************************/



 //#define DEBUG
#ifdef DEBUG
#define TRACE(classname) printf("\n____%s____\n",classname);
#else
#define TRACE(classname)
#endif



#define STAGE4_ERROR(symbol1, symbol2, ...) {stage4err("while generating C code", symbol1, symbol2, __VA_ARGS__); exit(EXIT_FAILURE);}


/* Macros to access the constant value of each expression (if it exists) from the annotation introduced to the symbol_c object by constant_folding_c in stage3! */
#define VALID_CVALUE(dtype, symbol)           ((symbol)->const_value._##dtype.is_valid())
#define GET_CVALUE(dtype, symbol)             ((symbol)->const_value._##dtype.get()) 



/***********************************************************************/

/* Unlike Programs and Configurations which get mapped onto C++ classes,
 * Function Blocks are mapped onto a C structure containing the variables, and
 * a C function containing the code in the FB's body. This is to allow direct allocation
 * of a FB variable (which is really an instance of the C data structure) to
 * a member of a union variable (note that classes with constructors cannot
 * be mebers of a union), which is done in IL when loading a FB onto IL's
 * default variable.
 *
 * So as not to clash the names of the C data structure and the C function,
 * the C structure is given a name identical to that of the FB name, whereas
 * the name of the function is the FB name with a constant string appended.
 * The value of that constant string which is appended is defined in the following
 * constant.
 * In order not to clash with any variable in the IL and ST source codem the
 * following constant should contain a double underscore, which is not allowed
 * in IL and ST.
 *
 * e.g.:  FUNTION_BLOCK TEST
 * is mapped onto a TEST data structure, and a TEST_body__ function.
 */

#define FB_FUNCTION_SUFFIX "_body__"

 /* Idem as body, but for initializer FB function */
#define FB_INIT_SUFFIX "_init__"

/* Idem as body, but for run CONFIG and RESOURCE function */
#define FB_RUN_SUFFIX "_run__"

/* The FB body function is passed as the only parameter a pointer to the FB data
 * structure instance. The name of this parameter is given by the following constant.
 * In order not to clash with any variable in the IL and ST source codem the
 * following constant should contain a double underscore, which is not allowed
 * in IL and ST.
 *
 * e.g.: the body of FUNTION_BLOCK TEST
 * is mapped onto the C function
 *  TEST_body__(TEST *data__)
 */

#define FB_FUNCTION_PARAM "data__"


#define SFC_STEP_ACTION_PREFIX "__SFC_"


 /* Variable declaration symbol for accessor macros */
#define DECLARE_VAR "__DECLARE_VAR"
#define DECLARE_GLOBAL "__DECLARE_GLOBAL"
#define DECLARE_GLOBAL_FB "__DECLARE_GLOBAL_FB"
#define DECLARE_GLOBAL_LOCATION "__DECLARE_GLOBAL_LOCATION"
#define DECLARE_GLOBAL_LOCATED "__DECLARE_GLOBAL_LOCATED"
#define DECLARE_EXTERNAL "__DECLARE_EXTERNAL"
#define DECLARE_EXTERNAL_FB "__DECLARE_EXTERNAL_FB"
#define DECLARE_LOCATED "__DECLARE_LOCATED"
#define DECLARE_GLOBAL_PROTOTYPE "__DECLARE_GLOBAL_PROTOTYPE"

/* Variable declaration symbol for accessor macros */
#define INIT_VAR "__INIT_VAR"
#define INIT_GLOBAL "__INIT_GLOBAL"
#define INIT_GLOBAL_FB "__INIT_GLOBAL_FB"
#define INIT_GLOBAL_LOCATED "__INIT_GLOBAL_LOCATED"
#define INIT_EXTERNAL "__INIT_EXTERNAL"
#define INIT_EXTERNAL_FB "__INIT_EXTERNAL_FB"
#define INIT_LOCATED "__INIT_LOCATED"
#define INIT_LOCATED_VALUE "__INIT_LOCATED_VALUE"

/* Variable getter symbol for accessor macros */
#define GET_VAR "__GET_VAR"
#define GET_EXTERNAL "__GET_EXTERNAL"
#define GET_EXTERNAL_FB "__GET_EXTERNAL_FB"
#define GET_LOCATED "__GET_LOCATED"

#define GET_VAR_REF "__GET_VAR_REF"
#define GET_EXTERNAL_REF "__GET_EXTERNAL_REF"
#define GET_EXTERNAL_FB_REF "__GET_EXTERNAL_FB_REF"
#define GET_LOCATED_REF "__GET_LOCATED_REF"

#define GET_VAR_DREF "__GET_VAR_DREF"
#define GET_EXTERNAL_DREF "__GET_EXTERNAL_DREF"
#define GET_EXTERNAL_FB_DREF "__GET_EXTERNAL_FB_DREF"
#define GET_LOCATED_DREF "__GET_LOCATED_DREF"

#define GET_VAR_BY_REF "__GET_VAR_BY_REF"
#define GET_EXTERNAL_BY_REF "__GET_EXTERNAL_BY_REF"
#define GET_EXTERNAL_FB_BY_REF "__GET_EXTERNAL_FB_BY_REF"
#define GET_LOCATED_BY_REF "__GET_LOCATED_BY_REF"

/* Variable setter symbol for accessor macros */
#define SET_VAR "__SET_VAR"
#define SET_EXTERNAL "__SET_EXTERNAL"
#define SET_EXTERNAL_FB "__SET_EXTERNAL_FB"
#define SET_LOCATED "__SET_LOCATED"

/* Variable initial value symbol for accessor macros */
#define INITIAL_VALUE "__INITIAL_VALUE"

/* Generate a name for a temporary variable.
 * Each new name generated is appended a different number,
 * starting off from 0.
 * After calling reset(), the names will start off again from 0.
 */
#define VAR_LEADER "__"
#define TEMP_VAR VAR_LEADER "TMP_"
#define SOURCE_VAR VAR_LEADER "SRC_"

 /* please see the comment before the RET_operator_c visitor for details... */
#define END_LABEL VAR_LEADER "end"


/***********************************************************************/
/***********************************************************************/
/***********************************************************************/
/***********************************************************************/


static int generate_line_directives__ = 0;
static int generate_pou_filepairs__ = 0;
static int generate_plc_state_backup_fuctions__ = 0;





#endif /*  _generate_c_H */

