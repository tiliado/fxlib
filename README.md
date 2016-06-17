FxLib
=====

Fenryxo's utility C library primarily targeted at Pebble apps.

Features
--------

  * [fxlib/typedefs.h](fxlib/typedefs.h): Type definitions such as
    `uint`, `ushort`, `ptr_t`, `fx_*_func`'s, etc.
  * [fxlib/macros.h](fxlib/macros.h): Various utility macros such as
    `*alloc*` wrappers, `fx_return_if_fail(expr)` variants, etc.
  * [fxlib/ref.h](fxlib/ref.h): Reference counting for FxLib objects
    as well as for your objects.
  * [fxlib/ext_ref.h](fxlib/ext_ref.h): Reference counting for
    external objects.
  * [fxlib/ht.h](fxlib/ht.h): Primitive hash table implementation.
  * [fxlib/strbuf.h](fxlib/strbuf.h): String buffer - build a string per partes.
  * [fxlib/strfmt.h](fxlib/strfmt.h): String formatting with double value support.
  
Dependencies
------------

  * Standard C library
  * GNU make
  * Pebble SDK (to build Pebble package)

Documentation
-------------

  * Incomplete!
  * Some functions are documented in header files.

Build
-----

  * Run `make pebble-build` to build Pebble package.
  * Run `make pebble-install` to show a hint how to install the package.
  * Run `make pebble-clean` to clean build directory.
  
Contributing
------------

Pull requests are welcome. All contributors must grant FxLib's author
a permission to relicense their contribution under any of the following
free software licenses at any time:

  * LGPL 3.0 or later
  * GPL 3.0 or later
  * AGPL 3.0 or later
  * 2-Clause BSD license
  * MIT license
  * Apache license

(Lesson learnt from the past - it was a pain to relicense Nuvola Player & in-built
Diorite library under 2-Clause BSD.)

Copyright
---------

  * Copyright 2016 Jiří Janoušek <janousek.jiri@gmail.com>
  * Licensed under [LGPL 3.0](./LICENSE).
