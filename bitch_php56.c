
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "php_bitch_php56.h"

/* If you declare any globals in php_bitch_php56.h uncomment this:
*/
ZEND_DECLARE_MODULE_GLOBALS(bitch_php56)

/* True global resources - no need for thread safety here */
static int le_bitch_php56;

/* {{{ PHP_INI
 */
/* Remove comments and fill if you need to have entries in php.ini
 */
PHP_INI_BEGIN()
    STD_PHP_INI_ENTRY("bitch_php56.global_value",      "42", PHP_INI_ALL, OnUpdateLong, global_value, zend_bitch_php56_globals, bitch_php56_globals)
    STD_PHP_INI_ENTRY("bitch_php56.global_string", "foobar", PHP_INI_ALL, OnUpdateString, global_string, zend_bitch_php56_globals, bitch_php56_globals)
PHP_INI_END()
/* }}} */

/* Remove the following function when you have successfully modified config.m4
   so that your module can be compiled into PHP, it exists only for testing
   purposes. */

PHP_FUNCTION(testLittle)
{
    long arg = 0;
    int arg_len, len;
    char *strg;
    zval *input_num;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &arg, &arg_len) == FAILURE) {
        return;
    }

    len = spprintf(&strg, 0, "调用方法 testLittle() 成功！入参为：%d", arg);
    RETURN_STRINGL(strg, len, 0);
}

/* Every user-visible function in PHP should document itself in the source */
/* {{{ proto string testBitch(string arg)
   Return a string to confirm that the module is compiled in */
PHP_FUNCTION(testBitch)
{
	char *arg = NULL;
	int arg_len, len;
	char *strg;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &arg, &arg_len) == FAILURE) {
		return;
	}

	len = spprintf(&strg, 0, "调用方法 testBitch() 成功！入参为：%s", arg);
	RETURN_STRINGL(strg, len, 0);
}
/* }}} */
/* The previous line is meant for vim and emacs, so it can correctly fold and
   unfold functions in source code. See the corresponding marks just before
   function definition, where the functions purpose is also documented. Please
   follow this convention for the convenience of others editing your code.
*/


/* {{{ php_bitch_php56_init_globals
 */
/* Uncomment this function if you have INI entries
 */
static void php_bitch_php56_init_globals(zend_bitch_php56_globals *bitch_php56_globals)
{
	bitch_php56_globals->global_value = 0;
	bitch_php56_globals->global_string = NULL;
}
/* }}} */

/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(bitch_php56)
{
	/* If you have INI entries, uncomment these lines 
	*/
	REGISTER_INI_ENTRIES();
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION
 */
PHP_MSHUTDOWN_FUNCTION(bitch_php56)
{
	/* uncomment this line if you have INI entries
	*/
	UNREGISTER_INI_ENTRIES();
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request start */
/* {{{ PHP_RINIT_FUNCTION
 */
PHP_RINIT_FUNCTION(bitch_php56)
{
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request end */
/* {{{ PHP_RSHUTDOWN_FUNCTION
 */
PHP_RSHUTDOWN_FUNCTION(bitch_php56)
{
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(bitch_php56)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "bitch_php56 support", "enabled");
	php_info_print_table_end();

	/* Remove comments if you have entries in php.ini
	*/
	DISPLAY_INI_ENTRIES();
}
/* }}} */

/* {{{ bitch_php56_functions[]
 *
 * Every user visible function must have an entry in bitch_php56_functions[].
 */
const zend_function_entry bitch_php56_functions[] = {
	PHP_FE(testLittle,	0)
	PHP_FE(testBitch,	NULL)
	PHP_FE_END	/* Must be the last line in bitch_php56_functions[] */
};
/* }}} */

/* {{{ bitch_php56_module_entry
 */
zend_module_entry bitch_php56_module_entry = {
	STANDARD_MODULE_HEADER,
	"bitch_php56",
	bitch_php56_functions,
	PHP_MINIT(bitch_php56),
	PHP_MSHUTDOWN(bitch_php56),
	PHP_RINIT(bitch_php56),		/* Replace with NULL if there's nothing to do at request start */
	PHP_RSHUTDOWN(bitch_php56),	/* Replace with NULL if there's nothing to do at request end */
	PHP_MINFO(bitch_php56),
	PHP_BITCH_PHP56_VERSION,
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_BITCH_PHP56
ZEND_GET_MODULE(bitch_php56)
#endif

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
