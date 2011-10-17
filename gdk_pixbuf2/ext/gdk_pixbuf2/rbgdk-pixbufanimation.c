/* -*- c-file-style: "ruby"; indent-tabs-mode: nil -*- */
/************************************************

  rbgdk-pixbufanimation.c -

  $Author: mutoh $
  $Date: 2004/11/30 16:23:13 $

  Copyright (C) 2002,2003 Masao Mutoh
************************************************/
#include "rbgdk-pixbuf.h"

#define _SELF(s) (GDK_PIXBUF_ANIMATION(RVAL2GOBJ(s)))
#define RVAL2ITR(i) (GDK_PIXBUF_ANIMATION_ITER(RVAL2GOBJ(i)))

static VALUE
animation_initialize(VALUE self, VALUE filename)
{
    GdkPixbufAnimation* ret;
    GError* error = NULL;

    ret = gdk_pixbuf_animation_new_from_file(RVAL2CSTR(filename), &error);
    if (ret == NULL)
        RAISE_GERROR(error);

    G_INITIALIZE(self, ret);
    return Qnil;
}

static VALUE
animation_get_width(VALUE self)
{
    return INT2NUM(gdk_pixbuf_animation_get_width(_SELF(self)));
}

static VALUE
animation_get_height(VALUE self)
{
    return INT2NUM(gdk_pixbuf_animation_get_height(_SELF(self)));
}

static VALUE
animation_get_iter(int argc, VALUE *argv, VALUE self)
{
    VALUE start_time_sec, start_time_usec;
    GTimeVal start_time;

    rb_scan_args(argc, argv, "02", &start_time_sec, &start_time_usec);

    if (NIL_P(start_time_sec))
        return GOBJ2RVAL(gdk_pixbuf_animation_get_iter(_SELF(self), NULL));

    start_time.tv_sec = NUM2LONG(start_time_sec);
    start_time.tv_usec = NIL_P(start_time_usec) ? 0 : NUM2LONG(start_time_usec);

    return GOBJ2RVAL(gdk_pixbuf_animation_get_iter(_SELF(self), &start_time));
}

static VALUE
animation_is_static_image(VALUE self)
{
    return CBOOL2RVAL(gdk_pixbuf_animation_is_static_image(_SELF(self)));
}

static VALUE
animation_get_static_image(VALUE self)
{
    return GOBJ2RVAL(gdk_pixbuf_animation_get_static_image(_SELF(self)));
}

static VALUE
animation_iter_advance(int argc, VALUE *argv, VALUE self)
{
    VALUE current_time_sec, current_time_usec;
    GTimeVal current_time;

    rb_scan_args(argc, argv, "02", &current_time_sec, &current_time_usec);

    if (NIL_P(current_time_sec))
        return CBOOL2RVAL(gdk_pixbuf_animation_iter_advance(RVAL2ITR(self), NULL));

    current_time.tv_sec = NUM2LONG(current_time_sec);
    current_time.tv_usec = NIL_P(current_time_usec) ? 0 : NUM2LONG(current_time_usec);

    return CBOOL2RVAL(gdk_pixbuf_animation_iter_advance(RVAL2ITR(self), &current_time));
}

static VALUE
animation_iter_get_delay_time(VALUE self)
{
    return INT2NUM(gdk_pixbuf_animation_iter_get_delay_time(RVAL2ITR(self)));
}

static VALUE
animation_iter_on_currently_loading_frame(VALUE self)
{
    return CBOOL2RVAL(gdk_pixbuf_animation_iter_on_currently_loading_frame(RVAL2ITR(self)));
}

static VALUE
animation_iter_get_pixbuf(VALUE self)
{
    return GOBJ2RVAL(gdk_pixbuf_animation_iter_get_pixbuf(RVAL2ITR(self)));
}

void
Init_gdk_pixbuf_animation(VALUE mGdk)
{
    VALUE anim = G_DEF_CLASS(GDK_TYPE_PIXBUF_ANIMATION, "PixbufAnimation", mGdk);    
    VALUE animiter = G_DEF_CLASS(GDK_TYPE_PIXBUF_ANIMATION_ITER, "PixbufAnimationIter", mGdk);    

    rb_define_method(anim, "initialize", animation_initialize, 1);
    rb_define_method(anim, "width", animation_get_width, 0);
    rb_define_method(anim, "height", animation_get_height, 0);
    rb_define_method(anim, "get_iter", animation_get_iter, -1);
    rb_define_method(anim, "static_image?", animation_is_static_image, 0);
    rb_define_method(anim, "static_image", animation_get_static_image, 0);
    rb_define_method(animiter, "advance", animation_iter_advance, -1);
    rb_define_method(animiter, "delay_time", animation_iter_get_delay_time, 0);
    rb_define_method(animiter, "on_currently_loading_frame?", animation_iter_on_currently_loading_frame, 0);
    rb_define_method(animiter, "pixbuf", animation_iter_get_pixbuf, 0);

}
