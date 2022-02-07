/*! @file
  @brief
  Class related functions.

  <pre>
  Copyright (C) 2015-2020 Kyushu Institute of Technology.
  Copyright (C) 2015-2020 Shimane IT Open-Innovation Center.

  This file is distributed under BSD 3-Clause License.


  </pre>
*/

/***** Feature test switches ************************************************/
/***** System headers *******************************************************/
#include "vm_config.h"
#include <stdint.h>
#include <string.h>
#include <assert.h>

/***** Local headers ********************************************************/
#include "alloc.h"
#include "value.h"
#include "vm.h"
#include "class.h"
#include "symbol.h"
#include "keyvalue.h"
#include "global.h"
#include "console.h"


/***** Constant values ******************************************************/
/***** Macros ***************************************************************/
/***** Typedefs *************************************************************/
/***** Function prototypes **************************************************/
/***** Local variables ******************************************************/
/***** Global variables *****************************************************/
// Builtin class table.
mrbc_class *mrbc_class_tbl[MRBC_TT_MAXVAL+1];
mrbc_class *mrbc_class_object;
mrbc_class *mrbc_class_math;
mrbc_class *mrbc_class_exception;
mrbc_class *mrbc_class_standarderror;
mrbc_class *mrbc_class_runtimeerror;
mrbc_class *mrbc_class_zerodivisionerror;
mrbc_class *mrbc_class_argumenterror;
mrbc_class *mrbc_class_indexerror;
mrbc_class *mrbc_class_typeerror;


/***** Signal catching functions ********************************************/
/***** Local functions ******************************************************/
/***** Global functions *****************************************************/
//================================================================
/*! define class

  @param  vm		pointer to vm.
  @param  name		class name.
  @param  super		super class.
  @return		pointer to defined class.
*/
mrbc_class * mrbc_define_class(struct VM *vm, const char *name, mrbc_class *super)
{
  mrbc_sym sym_id = str_to_symid(name);
  mrbc_object *obj = mrbc_get_const( sym_id );

  // create a new class?
  if( obj == NULL ) {
    mrbc_class *cls = mrbc_raw_alloc_no_free( sizeof(mrbc_class) );
    if( !cls ) return cls;	// ENOMEM

    cls->sym_id = sym_id;
#ifdef MRBC_DEBUG
    cls->names = name;	// for debug; delete soon.
#endif
    cls->super = (super == NULL) ? mrbc_class_object : super;
    cls->procs = 0;

    // register to global constant.
    mrbc_set_const( sym_id, &(mrb_value){.tt = MRBC_TT_CLASS, .cls = cls} );
    return cls;
  }

  // already
  assert( obj->tt == MRBC_TT_CLASS );
  return obj->cls;
}


//================================================================
/*! define class method or instance method.

  @param  vm		pointer to vm.
  @param  cls		pointer to class.
  @param  name		method name.
  @param  cfunc		pointer to function.
*/
void mrbc_define_method(struct VM *vm, mrbc_class *cls, const char *name, mrbc_func_t cfunc)
{
  if( cls == NULL ) cls = mrbc_class_object;	// set default to Object.

  mrbc_proc *proc = (mrbc_proc *)mrbc_raw_alloc_no_free(sizeof(mrbc_proc));
  if( !proc ) return;	// ENOMEM

  proc->ref_count = 1;
  proc->c_func = 1;
  proc->sym_id = str_to_symid(name);
  proc->next = cls->procs;
  proc->callinfo = 0;
  proc->func = cfunc;

  cls->procs = proc;
}


//================================================================
/*! mrbc_instance constructor

  @param  vm    Pointer to VM.
  @param  cls	Pointer to Class (mrbc_class).
  @param  size	size of additional data.
  @return       mrbc_instance object.
*/
mrbc_value mrbc_instance_new(struct VM *vm, mrbc_class *cls, int size)
{
  mrbc_value v = {.tt = MRBC_TT_OBJECT};
  v.instance = (mrbc_instance *)mrbc_alloc(vm, sizeof(mrbc_instance) + size);
  if( v.instance == NULL ) return v;	// ENOMEM

  if( mrbc_kv_init_handle(vm, &v.instance->ivar, 0) != 0 ) {
    mrbc_raw_free(v.instance);
    v.instance = NULL;
    return v;
  }

  v.instance->ref_count = 1;
  v.instance->cls = cls;

  return v;
}


//================================================================
/*! mrbc_instance destructor

  @param  v	pointer to target value
*/
void mrbc_instance_delete(mrbc_value *v)
{
  mrbc_kv_delete_data( &v->instance->ivar );
  mrbc_raw_free( v->instance );
}


//================================================================
/*! instance variable setter

  @param  obj		pointer to target.
  @param  sym_id	key symbol ID.
  @param  v		pointer to value.
*/
void mrbc_instance_setiv(mrbc_object *obj, mrbc_sym sym_id, mrbc_value *v)
{
  mrbc_incref(v);
  mrbc_kv_set( &obj->instance->ivar, sym_id, v );
}


//================================================================
/*! instance variable getter

  @param  obj		pointer to target.
  @param  sym_id	key symbol ID.
  @return		value.
*/
mrbc_value mrbc_instance_getiv(mrbc_object *obj, mrbc_sym sym_id)
{
  mrbc_value *v = mrbc_kv_get( &obj->instance->ivar, sym_id );
  if( !v ) return mrbc_nil_value();

  mrbc_incref(v);
  return *v;
}


//================================================================
/*! mrbc_proc constructor

  @param  vm		Pointer to VM.
  @param  irep		Pointer to IREP.
  @return		mrbc_value of Proc object.
*/
mrbc_value mrbc_proc_new(struct VM *vm, void *irep)
{
  mrbc_value val = {.tt = MRBC_TT_PROC};

  val.proc = (mrbc_proc *)mrbc_alloc(vm, sizeof(mrbc_proc));
  if( !val.proc ) return val;	// ENOMEM

  val.proc->ref_count = 1;
  val.proc->c_func = 0;
  val.proc->sym_id = -1;
  val.proc->next = 0;
  val.proc->callinfo = vm->callinfo_tail;

  if(vm->current_regs[0].tt == MRBC_TT_PROC) {
    val.proc->callinfo_self = vm->current_regs[0].proc->callinfo_self;
  } else {
    val.proc->callinfo_self = vm->callinfo_tail;
  }

  val.proc->irep = irep;

  return val;
}


//================================================================
/*! mrbc_proc destructor

  @param  val	pointer to target value
*/
void mrbc_proc_delete(mrbc_value *val)
{
  mrbc_raw_free(val->proc);
}


//================================================================
/*! Check the class is the class of object.

  @param  obj	target object
  @param  cls	class
  @return	result
*/
int mrbc_obj_is_kind_of( const mrbc_value *obj, const mrb_class *cls )
{
  const mrbc_class *c = find_class_by_object( obj );
  while( c != NULL ) {
    if( c == cls ) return 1;
    c = c->super;
  }

  return 0;
}


//================================================================
/*! find method from object

  @param  vm		pointer to vm
  @param  recv		pointer to receiver object.
  @param  sym_id	symbol id.
  @return		pointer to proc or NULL.
*/
mrbc_proc *find_method(struct VM *vm, const mrbc_object *recv, mrbc_sym sym_id)
{
  mrbc_class *cls = find_class_by_object(recv);

  return find_method_by_class(NULL, cls, sym_id);
}


//================================================================
/*! find method by class

  @param  r_cls		found class return pointer or NULL
  @param  cls		target class
  @param  sym_id	sym_id of method
  @return		pointer to mrbc_proc or NULL
*/
mrbc_proc *find_method_by_class( mrbc_class **r_cls, mrbc_class *cls, mrbc_sym sym_id )
{
  while( cls != 0 ) {
    mrbc_proc *proc = cls->procs;
    while( proc != 0 ) {
      if( proc->sym_id == sym_id ) {
	if( r_cls ) *r_cls = cls;
        return proc;
      }
      proc = proc->next;
    }
    cls = cls->super;
  }

  return 0;
}


//================================================================
/*! get class by name

  @param  name		class name.
  @return		pointer to class object.
*/
mrbc_class * mrbc_get_class_by_name( const char *name )
{
  mrbc_sym sym_id = str_to_symid(name);
  mrbc_object *obj = mrbc_get_const( sym_id );

  if( obj == NULL ) return NULL;
  return (obj->tt == MRBC_TT_CLASS) ? obj->cls : NULL;
}


//================================================================
/*! (BETA) Call any method of the object, but written by C.

  @param  vm		pointer to vm.
  @param  v		see bellow example.
  @param  reg_ofs	see bellow example.
  @param  recv		pointer to receiver.
  @param  method	method name.
  @param  argc		num of params.

  @example
  // (Fixnum).to_s(16)
  static void c_fixnum_to_s(struct VM *vm, mrbc_value v[], int argc)
  {
    mrbc_value *recv = &v[1];
    mrbc_value arg1 = mrbc_fixnum_value(16);
    mrbc_value ret = mrbc_send( vm, v, argc, recv, "to_s", 1, &arg1 );
    SET_RETURN(ret);
  }
 */
mrbc_value mrbc_send( struct VM *vm, mrbc_value *v, int reg_ofs,
		     mrbc_value *recv, const char *method, int argc, ... )
{
  mrbc_sym sym_id = str_to_symid(method);
  mrbc_proc *m = find_method(vm, recv, sym_id);

  if( m == 0 ) {
    console_printf("No method. vtype=%d method='%s'\n", recv->tt, method );
    goto ERROR;
  }
  if( !m->c_func ) {
    console_printf("Method %s is not C function\n", method );
    goto ERROR;
  }

  // create call stack.
  mrbc_value *regs = v + reg_ofs + 2;
  mrbc_decref( &regs[0] );
  regs[0] = *recv;
  mrbc_incref(recv);

  va_list ap;
  va_start(ap, argc);
  int i;
  for( i = 1; i <= argc; i++ ) {
    mrbc_decref( &regs[i] );
    regs[i] = *va_arg(ap, mrbc_value *);
  }
  mrbc_decref( &regs[i] );
  regs[i] = mrbc_nil_value();
  va_end(ap);

  // call method.
  m->func(vm, regs, argc);
  mrbc_value ret = regs[0];

  for(; i >= 0; i-- ) {
    regs[i].tt = MRBC_TT_EMPTY;
  }

  return ret;

 ERROR:
  return mrbc_nil_value();
}


//================================================================
/*! (method) Ineffect operator / method
*/
void c_ineffect(struct VM *vm, mrbc_value v[], int argc)
{
  // nothing to do.
}
