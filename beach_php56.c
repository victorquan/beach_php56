
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "php_beach_php56.h"


#define EX_T(offset) (*EX_TMP_VAR(execute_data_ptr, offset))


/* If you declare any globals in php_beach_php56.h uncomment this:
*/
ZEND_DECLARE_MODULE_GLOBALS(beach_php56)

/* True global resources - no need for thread safety here */
static int le_beach_php56;
static void (*old_execute_internal)(zend_execute_data *execute_data_ptr, zend_fcall_info *fci, int return_value_used TSRMLS_DC);
static void (*old_execute_ex)(zend_execute_data *execute_data TSRMLS_DC);
static int (*old_zend_stream_open)(const char *filename, zend_file_handle *fh TSRMLS_DC);

/**
 * 类全局指针
 */
zend_class_entry *animal_ce;

/**
 * 定义接收的参数
 */
ZEND_BEGIN_ARG_INFO_EX(arg_animal_get_age, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arg_animal_set_age, 0, 0, 1)
	ZEND_ARG_INFO(0, age)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arg_animal_get_name, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arg_animal_set_name, 0, 0, 1)
	ZEND_ARG_INFO(0, name)
ZEND_END_ARG_INFO()

/**
 * 定义类的函数入口结构数组
 */
static zend_function_entry Animal_functions[] = {
		PHP_ME(Animal, __construct, NULL,                ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
		PHP_ME(Animal, __destruct,  NULL,                ZEND_ACC_PUBLIC|ZEND_ACC_DTOR)
		PHP_ME(Animal, getAge,      arg_animal_get_age,  ZEND_ACC_PUBLIC)
		PHP_ME(Animal, setAge,      arg_animal_set_age,  ZEND_ACC_PUBLIC)
		PHP_ME(Animal, getName,     arg_animal_get_name, ZEND_ACC_PUBLIC)
		PHP_ME(Animal, setName,     arg_animal_set_name, ZEND_ACC_PUBLIC)
		PHP_FE_END
};



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
	if(BEACH_PHP56_G(global_interceptor_enable)){
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
    STD_PHP_INI_ENTRY("beach_php56.global_value",      "42", PHP_INI_ALL, OnUpdateLong, global_value, zend_beach_php56_globals, beach_php56_globals)
    STD_PHP_INI_ENTRY("beach_php56.global_string", "foobar", PHP_INI_ALL, OnUpdateString, global_string, zend_beach_php56_globals, beach_php56_globals)
    STD_PHP_INI_ENTRY("beach_php56.global_interceptor_enable", "0", PHP_INI_ALL, OnUpdateBool, global_interceptor_enable, zend_beach_php56_globals, beach_php56_globals)
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

/* {{{ php可以直接调用的函数：testBeach(string)
 */
PHP_FUNCTION(testBeach)
{
	char *arg = NULL;
	int arg_len, len;
	char *strg;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &arg, &arg_len) == FAILURE) {
		return;
	}

	len = spprintf(&strg, 0, "调用方法 testBeach() 成功！入参为：%s", arg);
	RETURN_STRINGL(strg, len, 0);
}
/* }}} */


/* {{{ php_beach_php56_init_globals
 */
static void php_beach_php56_init_globals(zend_beach_php56_globals *beach_php56_globals)
{
	beach_php56_globals->global_value = 0;
	beach_php56_globals->global_string = NULL;
	beach_php56_globals->global_interceptor_enable = 0;
}
/* }}} */

/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(beach_php56)
{
	REGISTER_INI_ENTRIES();

    zend_class_entry animal;
    INIT_CLASS_ENTRY(animal, "Animal", Animal_functions);
    animal_ce = zend_register_internal_class_ex(&animal, NULL, NULL TSRMLS_CC);
	zend_declare_property_long(animal_ce, "age", sizeof("age") - 1, 0, ZEND_ACC_PRIVATE TSRMLS_CC);
    zend_declare_property_null(animal_ce, ZEND_STRL("name"), ZEND_ACC_PRIVATE TSRMLS_CC);

	hook_execute(TSRMLS_C);
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION
 */
PHP_MSHUTDOWN_FUNCTION(beach_php56)
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
PHP_RINIT_FUNCTION(beach_php56)
{
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request end */
/* {{{ PHP_RSHUTDOWN_FUNCTION
 */
PHP_RSHUTDOWN_FUNCTION(beach_php56)
{
	TSRMLS_FETCH();
	unhook_execute();
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(beach_php56)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "beach_php56 support", "enabled");
	php_info_print_table_end();

	/* Remove comments if you have entries in php.ini
	*/
	DISPLAY_INI_ENTRIES();
}
/* }}} */

/* {{{ beach_php56_functions[]
 *
 * Every user visible function must have an entry in beach_php56_functions[].
 */
const zend_function_entry beach_php56_functions[] = {
	PHP_FE(testLittle,	0)
	PHP_FE(testBeach,	NULL)
	PHP_FE_END	/* Must be the last line in beach_php56_functions[] */
};
/* }}} */

/* {{{ beach_php56_module_entry
 */
zend_module_entry beach_php56_module_entry = {
	STANDARD_MODULE_HEADER,
	"beach_php56",
	beach_php56_functions,
	PHP_MINIT(beach_php56),		/* module init. */
	PHP_MSHUTDOWN(beach_php56),	/* module shutdown. */
	PHP_RINIT(beach_php56),		/* request init. Replace with NULL if there's nothing to do at request start */
	PHP_RSHUTDOWN(beach_php56),	/* request shutdown. Replace with NULL if there's nothing to do at request end */
	PHP_MINFO(beach_php56),		/* module info. */
	PHP_BEACH_PHP56_VERSION,
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_BEACH_PHP56
ZEND_GET_MODULE(beach_php56)
#endif



PHP_METHOD(Animal, __construct){

}

PHP_METHOD(Animal, __destruct){

}

PHP_METHOD(Animal, getAge){
	zval *self, *age;
	self = getThis();
	age = zend_read_property(animal_ce, self, "age", sizeof("age") - 1, 1 TSRMLS_CC);
	RETURN_ZVAL(age, 1, 0);
}

PHP_METHOD(Animal, setAge){
	zval *obj, *age;
	obj = getThis();
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &age) == FAILURE) {
		RETURN_NULL();
	}
	zend_update_property_long(animal_ce, obj, "age", sizeof("age") - 1, age);

	RETURN_TRUE;
}

PHP_METHOD(Animal, getName){
	zval *self, *name;
	self = getThis();
	name = zend_read_property(animal_ce, self, ZEND_STRL("name"), 0 TSRMLS_CC);
	RETURN_STRING(Z_STRVAL_P(name), 0);
}

PHP_METHOD(Animal, setName){
	char *arg = NULL;
	int arg_len;
	zval *value, *self;
	if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &arg, &arg_len) == FAILURE){
		WRONG_PARAM_COUNT;
	}
	self = getThis();
	ALLOC_INIT_ZVAL(value);
	//MAKE_STD_ZVAL(value);
	ZVAL_STRINGL(value, arg, arg_len, 0);
	SEPARATE_ZVAL_TO_MAKE_IS_REF(&value);
	zend_update_property(animal_ce, self, ZEND_STRL("name"), value TSRMLS_CC);

	RETURN_TRUE;
}




/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
