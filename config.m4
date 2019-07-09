dnl $Id$
dnl config.m4 for extension bitch_php56

dnl Comments in this file start with the string 'dnl'.
dnl Remove where necessary. This file will not work
dnl without editing.

dnl If your extension references something external, use with:

dnl PHP_ARG_WITH(bitch_php56, for bitch_php56 support,
dnl Make sure that the comment is aligned:
dnl [  --with-bitch_php56             Include bitch_php56 support])

dnl Otherwise use enable:

PHP_ARG_ENABLE(bitch_php56, whether to enable bitch_php56 support,
[  --enable-bitch_php56           Enable bitch_php56 support])

if test "$PHP_BITCH_PHP56" != "no"; then
  dnl Write more examples of tests here...

  dnl # --with-bitch_php56 -> check with-path
  dnl SEARCH_PATH="/usr/local /usr"     # you might want to change this
  dnl SEARCH_FOR="/include/bitch_php56.h"  # you most likely want to change this
  dnl if test -r $PHP_BITCH_PHP56/$SEARCH_FOR; then # path given as parameter
  dnl   BITCH_PHP56_DIR=$PHP_BITCH_PHP56
  dnl else # search default path list
  dnl   AC_MSG_CHECKING([for bitch_php56 files in default path])
  dnl   for i in $SEARCH_PATH ; do
  dnl     if test -r $i/$SEARCH_FOR; then
  dnl       BITCH_PHP56_DIR=$i
  dnl       AC_MSG_RESULT(found in $i)
  dnl     fi
  dnl   done
  dnl fi
  dnl
  dnl if test -z "$BITCH_PHP56_DIR"; then
  dnl   AC_MSG_RESULT([not found])
  dnl   AC_MSG_ERROR([Please reinstall the bitch_php56 distribution])
  dnl fi

  dnl # --with-bitch_php56 -> add include path
  dnl PHP_ADD_INCLUDE($BITCH_PHP56_DIR/include)

  dnl # --with-bitch_php56 -> check for lib and symbol presence
  dnl LIBNAME=bitch_php56 # you may want to change this
  dnl LIBSYMBOL=bitch_php56 # you most likely want to change this 

  dnl PHP_CHECK_LIBRARY($LIBNAME,$LIBSYMBOL,
  dnl [
  dnl   PHP_ADD_LIBRARY_WITH_PATH($LIBNAME, $BITCH_PHP56_DIR/$PHP_LIBDIR, BITCH_PHP56_SHARED_LIBADD)
  dnl   AC_DEFINE(HAVE_BITCH_PHP56LIB,1,[ ])
  dnl ],[
  dnl   AC_MSG_ERROR([wrong bitch_php56 lib version or lib not found])
  dnl ],[
  dnl   -L$BITCH_PHP56_DIR/$PHP_LIBDIR -lm
  dnl ])
  dnl
  dnl PHP_SUBST(BITCH_PHP56_SHARED_LIBADD)

  PHP_NEW_EXTENSION(bitch_php56, bitch_php56.c, $ext_shared)
fi
