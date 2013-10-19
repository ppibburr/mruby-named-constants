#include "mruby.h"
#include "mruby/value.h"
#include <mruby.h>
#include <stdio.h>
#include <mruby/class.h>


mrb_value
nc_define_module(mrb_state *mrb, mrb_value mod)
{
  mrb_value klass;
  mrb_sym sym;

  mrb_check_type(mrb, mod, MRB_TT_MODULE);
  mrb_get_args(mrb, "on", &klass,&sym);
  struct RClass *kls = mrb_class_ptr(klass);
  const char* name = mrb_sym2name(mrb,sym);
  struct RClass *where = mrb_define_module_under(mrb, kls, name);  
  mrb_value obj;
  obj = mrb_obj_value(where);
  return obj;

}

mrb_value
nc_define_class(mrb_state *mrb, mrb_value mod)
{
  mrb_value klass;
  mrb_sym sym;
  mrb_value sc;
  mrb_check_type(mrb, mod, MRB_TT_MODULE);
  mrb_get_args(mrb, "ono", &klass,&sym,&sc);
  struct RClass *kls = mrb_class_ptr(klass);
  const char* name = mrb_sym2name(mrb,sym);
  struct RClass *where = mrb_define_class_under(mrb, kls, name,mrb_class_ptr(sc));  

  mrb_value obj;
  obj = mrb_obj_value(where);
  return obj;
}

/* ruby calls this to load the extension */
void mrb_mruby_named_constants_gem_init(mrb_state *mrb)
{
  struct RClass *mod = mrb_define_module(mrb, "NC");
  int ai = mrb_gc_arena_save(mrb);
  struct RClass *obj = mrb_class_get(mrb,"Object");
  struct RClass *cls = mrb_class_get(mrb,"Class");
  struct RClass *gb = mrb_define_module_under(mrb, obj, "NC");  
  mrb_define_class_method(mrb, gb, "define_module", nc_define_module, ARGS_REQ(2)); 
  mrb_define_class_method(mrb, gb, "define_class", nc_define_class, ARGS_REQ(2));
  mrb_gc_arena_restore(mrb,ai);  
}

void mrb_mruby_named_constants_gem_final(mrb_state *mrb)
{
  
}
