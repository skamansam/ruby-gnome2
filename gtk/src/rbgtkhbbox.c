/* -*- c-file-style: "ruby" -*- */
/************************************************

  rbgtkhbbox.c -

  $Author: mutoh $
  $Date: 2002/07/31 17:23:54 $

  Copyright (C) 1998-2000 Yukihiro Matsumoto,
                          Daisuke Kanda,
                          Hiroshi Igarashi
************************************************/

#include "global.h"

static VALUE
hbbox_initialize(self)
    VALUE self;
{
    RBGTK_INITIALIZE(self, gtk_hbutton_box_new());
    return Qnil;
}

static VALUE
hbbox_get_spacing_default(self)
    VALUE self;
{
    int i = gtk_hbutton_box_get_spacing_default();
    
    return INT2FIX(i);
}

static VALUE
hbbox_get_layout_default(self)
    VALUE self;
{
    int i = gtk_hbutton_box_get_layout_default();
    
    return INT2FIX(i);
}

static VALUE
hbbox_set_spacing_default(self, spacing)
    VALUE self, spacing;
{
    gtk_hbutton_box_set_spacing_default(NUM2INT(spacing));
    return Qnil;
}

static VALUE
hbbox_set_layout_default(self, layout)
    VALUE self, layout;
{
    gtk_hbutton_box_set_layout_default(NUM2INT(layout));
    return Qnil;
}

void 
Init_gtk_hbutton_box()
{
    VALUE gHBBox = G_DEF_CLASS(GTK_TYPE_HBUTTON_BOX, "HButtonBox", mGtk);

    rb_define_method(gHBBox, "initialize", hbbox_initialize, 0);
    rb_define_singleton_method(gHBBox, "get_spacing_default",
			       hbbox_get_spacing_default, 0);
    rb_define_singleton_method(gHBBox, "get_layout_default",
			       hbbox_get_layout_default, 0);
    rb_define_singleton_method(gHBBox, "set_spacing_default",
			       hbbox_set_spacing_default, 1);
    rb_define_singleton_method(gHBBox, "set_layout_default",
			       hbbox_set_layout_default, 1);
}
