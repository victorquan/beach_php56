
#ifndef PHP_BITCH_PHP56_H
#define PHP_BITCH_PHP56_H

extern zend_module_entry bitch_php56_module_entry;
#define phpext_bitch_php56_ptr &bitch_php56_module_entry

#define PHP_BITCH_PHP56_VERSION "0.1.0" /* Replace with version number for your extension */

#ifdef PHP_WIN32
#	define PHP_BITCH_PHP56_API __declspec(dllexport)
#elif defined(__GNUC__) && __GNUC__ >= 4
#	define PHP_BITCH_PHP56_API __attribute__ ((visibility("default")))
#else
#	define PHP_BITCH_PHP56_API
#endif

#ifdef ZTS
#include "TSRM.h"
#endif

/* 
  	Declare any global variables you may need between the BEGIN
	and END macros here:     
*/
ZEND_BEGIN_MODULE_GLOBALS(bitch_php56)
	long  global_value;
	char *global_string;
	zend_bool global_interceptor_enable;
ZEND_END_MODULE_GLOBALS(bitch_php56)

/* In every utility function you add that needs to use variables 
   in php_bitch_php56_globals, call TSRMLS_FETCH(); after declaring other 
   variables used by that function, or better yet, pass in TSRMLS_CC
   after the last function argument and declare your utility function
   with TSRMLS_DC after the last declared argument.  Always refer to
   the globals in your function as BITCH_PHP56_G(variable).  You are 
   encouraged to rename these macros something shorter, see
   examples in any other php module directory.
*/

#ifdef ZTS
#define BITCH_PHP56_G(v) TSRMG(bitch_php56_globals_id, zend_bitch_php56_globals *, v)
#else
#define BITCH_PHP56_G(v) (bitch_php56_globals.v)
#endif

#endif	/* PHP_BITCH_PHP56_H */

