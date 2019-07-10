
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "php_bitch_php56.h"


#define EX_T(offset) (*EX_TMP_VAR(execute_data_ptr, offset))


/* If you declare any globals in php_bitch_php56.h uncomment this:
*/
ZEND_DECLARE_MODULE_GLOBALS(bitch_php56)

/* True global resources - no need for thread safety here */
static int le_bitch_php56;
static void (*old_execute_internal)(zend_execute_data *execute_data_ptr, zend_fcall_info *fci, int return_value_used TSRMLS_DC);
static void (*old_execute_ex)(zend_execute_data *execute_data TSRMLS_DC);
static int (*old_zend_stream_open)(const char *filename, zend_file_handle *fh TSRMLS_DC);


/** 声明函数 */
/* 启动钩子 */
void hook_execute(TSRMLS_D);
/* 卸载钩子 */
void unhook_execute();
/* 方法调用拦截器 */
static void execute_function_interceptor(zend_execute_data *execute_data_ptr, zend_fcall_info *fci, int return_value_used TSRMLS_DC);



/* {{{ execute_function_interceptor() 方法拦截器
 */
static void execute_function_interceptor(zend_execute_data *execute_data_ptr, zend_fcall_info *fci, int return_value_used TSRMLS_DC)
{
	zval *return_value;
	zval **return_value_ptr;
	zval *this_ptr;
	int ht;

	if (fci) {
		return_value = *fci->retval_ptr_ptr;
		return_value_ptr = fci->retval_ptr_ptr;
		this_ptr = fci->object_ptr;
		ht = fci->param_count;
	} else {
		temp_variable *ret = &EX_T(execute_data_ptr->opline->result.var);
		zend_function *fbc = execute_data_ptr->function_state.function;
		return_value = ret->var.ptr;
		return_value_ptr = (fbc->common.fn_flags & ZEND_ACC_RETURN_REFERENCE) ? &ret->var.ptr : NULL;
		this_ptr = execute_data_ptr->object;
		ht = execute_data_ptr->opline->extended_value;
	}

	char *lcname;
	int function_name_strlen, free_lcname = 0;
	zend_class_entry *ce = NULL;
	zval *arg1;
	char *find_func_name = "json_encode";
	char *arg_class_prefix = "proto\\";

	ce = ((zend_internal_function *) execute_data_ptr->function_state.function)->scope;
	lcname = (char *)((zend_internal_function *) execute_data_ptr->function_state.function)->function_name;
	function_name_strlen = strlen(lcname);

	zend_op_array *op_array = execute_data_ptr->op_array;
	zend_arg_info *arg_info = ((zend_internal_function *) execute_data_ptr->function_state.function)->arg_info;
	zend_class_entry *scope = ((zend_internal_function *) execute_data_ptr->function_state.function)->scope;

	if(lcname && strstr(lcname, find_func_name) != NULL){
		if(zend_get_parameters(ZEND_NUM_ARGS(), 1, &arg1) == FAILURE){
			zend_error(E_ERROR, "cannot get arg1");
		}else{
			if(Z_TYPE_P(arg1) == IS_OBJECT){
				zend_class_entry *entry;
				entry = Z_OBJCE_P(arg1);
				if(entry->name && strstr(entry->name, arg_class_prefix) != NULL){
					zend_error(E_ERROR, "\nError Message：%s(line %d)", op_array->filename, execute_data_ptr->opline->lineno);
				}
			}
		}
	}

	old_execute_internal(execute_data_ptr, fci, return_value_used TSRMLS_CC);
	return;
}
/* }}} */

/* {{{ void hook_execute() 挂载钩子
 */
void hook_execute(TSRMLS_D)
{
	//根据php.in设置判断是否启用拦截器
	if(BITCH_PHP56_G(global_interceptor_enable)){
		old_execute_internal = zend_execute_internal;
		if (old_execute_internal == NULL) {
			old_execute_internal = execute_internal;
		}
		zend_execute_internal = execute_function_interceptor;
	}
}
/* }}} */

/* {{{ void unhook_execute() 解除钩子
 */
void unhook_execute()
{
//	if (old_execute_internal == execute_internal) {
//		old_execute_internal = NULL;
//	}
//	zend_execute_internal = old_execute_internal;
}
/* }}} */

/* {{{ 将php.ini设置绑定到全局变量
 */
PHP_INI_BEGIN()
/**
 * PHP_INI_PERDIR  指令可以在php.ini、httpd.conf或.htaccess文件中修改
 * PHP_INI_SYSTEM  指令可以在php.ini 和 httpd.conf 文件中修改
 * PHP_INI_USER    指令可以在用户脚本中修改
 * PHP_INI_ALL     指令可以在任何地方修改
 */
    STD_PHP_INI_ENTRY("bitch_php56.global_value",      "42", PHP_INI_ALL, OnUpdateLong, global_value, zend_bitch_php56_globals, bitch_php56_globals)
    STD_PHP_INI_ENTRY("bitch_php56.global_string", "foobar", PHP_INI_ALL, OnUpdateString, global_string, zend_bitch_php56_globals, bitch_php56_globals)
    STD_PHP_INI_ENTRY("bitch_php56.global_interceptor_enable", "0", PHP_INI_ALL, OnUpdateBool, global_interceptor_enable, zend_bitch_php56_globals, bitch_php56_globals)
PHP_INI_END()
/* }}} */

/* {{{ php可以直接调用的函数：testLittle(int)
 */
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
/* }}} */

/* {{{ php可以直接调用的函数：testBitch(string)
 */
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


/* {{{ php_bitch_php56_init_globals
 */
static void php_bitch_php56_init_globals(zend_bitch_php56_globals *bitch_php56_globals)
{
	bitch_php56_globals->global_value = 0;
	bitch_php56_globals->global_string = NULL;
	bitch_php56_globals->global_interceptor_enable = 0;
}
/* }}} */

/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(bitch_php56)
{
	REGISTER_INI_ENTRIES();
	hook_execute(TSRMLS_C);
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
	TSRMLS_FETCH();
	unhook_execute();
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
